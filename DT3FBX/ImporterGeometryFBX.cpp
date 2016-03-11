//==============================================================================
///	
///	File: ImporterGeometryFBX.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3FBX/ImporterGeometryFBX.hpp"
#include "DT3Core/Resources/ResourceTypes/GeometryResource.hpp"
#include "DT3Core/Types/FileBuffer/BinaryFileStream.hpp"
#include "DT3Core/Types/Utility/ConsoleStream.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/FileManager.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_IMPORTER(ImporterGeometryFBX,fbx)

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ImporterGeometryFBX::ImporterGeometryFBX (void)		
{    

}
			
ImporterGeometryFBX::~ImporterGeometryFBX (void)
{ 

}

//==============================================================================
//==============================================================================

void ImporterGeometryFBX::parse_mesh (GeometryResource *target, FbxScene* scene, FbxNode *node, FbxNodeAttribute *attr)
{
    // Evaluator
    FbxAnimEvaluator* scene_evaluator = scene->GetAnimationEvaluator();
    double *matrix = (double*) (scene_evaluator->GetNodeGlobalTransform(node));
    Matrix4 transform(  matrix[0],  matrix[1],  matrix[2],  matrix[3],
                        matrix[4],  matrix[5],  matrix[6],  matrix[7],
                        matrix[8],  matrix[9],  matrix[10], matrix[11],
                        matrix[12], matrix[13], matrix[14], matrix[15]  );
    transform.transpose();

    // We know that attr is a mesh at this point
    FbxMesh* mesh = node->GetMesh();
    
    // Create our mesh
    std::shared_ptr<Mesh> new_mesh = Mesh::create();
    target->add_mesh(new_mesh);
    
    // Set name and material
    new_mesh->set_name(node->GetName());
    
    if (node->GetMaterialCount() > 0)
        new_mesh->set_material(node->GetMaterial(0)->GetName());
    
    std::vector<Vector3> vertices_stream;
    std::vector<Vector3> normals_stream;
    std::vector<Vector2> uvs_stream_0;
    std::vector<Vector2> uvs_stream_1;
    std::vector<Vector4> weights_strength;
    std::vector<WeightsIndex> weights_index;
    std::vector<Triangle> index_stream;
    
    std::vector<DTuint> smoothing_group;
    
    //
    // Count vertices because control points are not 1:1 with texcoords
    //
    
    DTint num_verts = 0;
    
    for(DTint polygon_index = 0; polygon_index < mesh->GetPolygonCount(); polygon_index++) {
        DTint polygon_size = mesh->GetPolygonSize(polygon_index);
        ASSERT(polygon_size == 3);
        num_verts += polygon_size;
    }
        
    //
    // Vertices
    //
    
    std::map<DTint,DTint> cp_to_vert;
    
    vertices_stream.resize(num_verts);
    DTint ii = 0;
    
    // Let's get normals of each polygon, since the mapping mode of normal element is by polygon-vertex.
    for(DTint polygon_index = 0; polygon_index < mesh->GetPolygonCount(); polygon_index++) {
    
        // Get polygon size, you know how many vertices in current polygon.
        DTint polygon_size = mesh->GetPolygonSize(polygon_index);
        
        // Retrieve each vertex of current polygon.
        for(DTint i = 0; i < polygon_size; i++) {
            DTint cp_index = mesh->GetPolygonVertex(polygon_index, i);
            FbxVector4 vert = mesh->GetControlPointAt(cp_index);
            
            ASSERT(ii < vertices_stream.size());
            vertices_stream[ii].x = (DTfloat)vert.mData[0];
            vertices_stream[ii].y = (DTfloat)vert.mData[1];
            vertices_stream[ii].z = (DTfloat)vert.mData[2];
            
            // Apply transform
            vertices_stream[ii] = transform * vertices_stream[ii];
            
            // Remember mapping to control point
            cp_to_vert[cp_index] = ii;
            
            ++ii;
        }

    }
    
    //
    // Connectivity
    //
    
    DTint num_polys = mesh->GetPolygonCount();
    index_stream.resize(num_polys);
   
    // Let's get normals of each polygon, since the mapping mode of normal element is by polygon-vertex.
    for(DTint polygon_index = 0; polygon_index < num_polys; polygon_index++) {
    
        // Get polygon size, you know how many vertices in current polygon.
        ASSERT(mesh->GetPolygonSize(polygon_index) == 3);
        
        index_stream[polygon_index].v[0] = cp_to_vert[mesh->GetPolygonVertex(polygon_index, 0)];
        index_stream[polygon_index].v[1] = cp_to_vert[mesh->GetPolygonVertex(polygon_index, 1)];
        index_stream[polygon_index].v[2] = cp_to_vert[mesh->GetPolygonVertex(polygon_index, 2)];
        
        ASSERT(index_stream[polygon_index].v[0] >= 0 && index_stream[polygon_index].v[0] <= vertices_stream.size());
        ASSERT(index_stream[polygon_index].v[1] >= 0 && index_stream[polygon_index].v[1] <= vertices_stream.size());
        ASSERT(index_stream[polygon_index].v[2] >= 0 && index_stream[polygon_index].v[2] <= vertices_stream.size());
    }


    //
    // UV's
    //

    // Get all UV set names
    FbxStringList uv_set_nameList;
    mesh->GetUVSetNames(uv_set_nameList);

    //iterating over all uv sets
    for (DTint uv_set_index = 0; uv_set_index < uv_set_nameList.GetCount(); uv_set_index++) {
    
        // Pick output stream
        DTint output_stream;
        if (uvs_stream_0.size() == 0) {
            output_stream = 0;
            uvs_stream_0.resize(num_verts);
        } else if (uvs_stream_1.size() == 0) {
            output_stream = 1;
            uvs_stream_1.resize(num_verts);
        } else {
            break;
        }
        
        // Get uv_set_index-th uv set
        const char* uv_set_name = uv_set_nameList.GetStringAt(uv_set_index);
        const FbxGeometryElementUV* uv_element = mesh->GetElementUV(uv_set_name);

        if(!uv_element)
            continue;

        // Only support mapping mode eByPolygonVertex and eByControlPoint
        if( uv_element->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
            uv_element->GetMappingMode() != FbxGeometryElement::eByControlPoint )
            continue;   // TODO: Should we abort?

        if( uv_element->GetMappingMode() == FbxGeometryElement::eByControlPoint) {
        
            ASSERT(0);  // TODO
            
            //Let's get normals of each vertex, since the mapping mode of normal element is by control point
            for(DTint vertex_index = 0; vertex_index < mesh->GetControlPointsCount(); vertex_index++) {
                
                DTint uv_index = 0;
                
                //reference mode is direct, the normal index is same as vertex index.
                //get normals by the index of control vertex
                if(uv_element->GetReferenceMode() == FbxGeometryElement::eDirect )
                    uv_index = vertex_index;

                //reference mode is index-to-direct, get normals by the index-to-direct
                if(uv_element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                    uv_index = uv_element->GetIndexArray().GetAt(vertex_index);

                //Got normals of each vertex.
                FbxVector2 uv = uv_element->GetDirectArray().GetAt(uv_index);

                DTint index_by_polygon_index = cp_to_vert[mesh->GetPolygonVertex(vertex_index, 0)];
                
                if (output_stream == 0)
                    uvs_stream_0[index_by_polygon_index] = Vector2( (DTfloat) uv[0], (DTfloat) uv[1]);
                else if (output_stream == 1)
                    uvs_stream_1[index_by_polygon_index] = Vector2( (DTfloat) uv[0], (DTfloat) uv[1]);
                
            }// End for vertex_index

        } else if (uv_element->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) {
        
            DTint index_by_polygon_index = 0;
           
            // Let's get normals of each polygon, since the mapping mode of normal element is by polygon-vertex.
            for(DTint polygon_index = 0; polygon_index < mesh->GetPolygonCount(); polygon_index++) {
            
                // Get polygon size, you know how many vertices in current polygon.
                DTint polygon_size = mesh->GetPolygonSize(polygon_index);
                
                //retrieve each vertex of current polygon.
                for(DTint i = 0; i < polygon_size; i++) {
                
                    DTint uv_index = 0;
                    
                    // Reference mode is direct, the normal index is same as index_by_polygon_index.
                    if( uv_element->GetReferenceMode() == FbxGeometryElement::eDirect )
                        uv_index = index_by_polygon_index;

                    // Reference mode is index-to-direct, get normals by the index-to-direct
                    if(uv_element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                        uv_index = uv_element->GetIndexArray().GetAt(index_by_polygon_index);

                    // Got normals of each polygon-vertex.
                    FbxVector2 uv = uv_element->GetDirectArray().GetAt(uv_index);

//                    if( gVerbose ) FBXSDK_printf("normals for polygon[%d]vertex[%d]: %f %f %f %f \n",
//                        polygon_index, i, normal[0], normal[1], normal[2], normal[3]);

                    ASSERT(index_by_polygon_index <= vertices_stream.size());

                    if (output_stream == 0)
                        uvs_stream_0[index_by_polygon_index] = Vector2( (DTfloat) uv[0], (DTfloat) uv[1]);
                    else if (output_stream == 1)
                        uvs_stream_1[index_by_polygon_index] = Vector2( (DTfloat) uv[0], (DTfloat) uv[1]);

                    index_by_polygon_index++;
                }
            }

        }
    }
    
    
//    //
//    // Normals
//    //
//    
//    //get the normal element
//    FbxGeometryElementNormal* normal_element = mesh->GetElementNormal();
//    if(normal_element) {
//    
//        normals_stream.resize(num_verts);
//    
//        // Mapping mode is by control points. The mesh should be smooth and soft.
//        // we can get normals by retrieving each control point
//        if( normal_element->GetMappingMode() == FbxGeometryElement::eByControlPoint ) {
//        
//            ASSERT(0);  // TODO
//            
//            //Let's get normals of each vertex, since the mapping mode of normal element is by control point
//            for(DTint vertex_index = 0; vertex_index < mesh->GetControlPointsCount(); vertex_index++) {
//                
//                DTint normal_index = 0;
//                
//                //reference mode is direct, the normal index is same as vertex index.
//                //get normals by the index of control vertex
//                if(normal_element->GetReferenceMode() == FbxGeometryElement::eDirect )
//                    normal_index = vertex_index;
//
//                //reference mode is index-to-direct, get normals by the index-to-direct
//                if(normal_element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//                    normal_index = normal_element->GetIndexArray().GetAt(vertex_index);
//
//                //Got normals of each vertex.
//                FbxVector4 normal = normal_element->GetDirectArray().GetAt(normal_index);
//
////                if( gVerbose )
////                    FBXSDK_printf("normals for vertex[%d]: %f %f %f %f \n", vertex_index, normal[0], normal[1], normal[2], normal[3]);
//
//                DTint index_by_polygon_index = cp_to_vert[mesh->GetPolygonVertex(vertex_index, 0)];
//
//                normals_stream[index_by_polygon_index] = Vector3((DTfloat) normal[0], (DTfloat) normal[1], (DTfloat) normal[2]);
//
//            }// End for vertex_index
//            
//        } else if(normal_element->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) {
//        
//            DTint index_by_polygon_index = 0;
//           
//            // Let's get normals of each polygon, since the mapping mode of normal element is by polygon-vertex.
//            for(DTint polygon_index = 0; polygon_index < mesh->GetPolygonCount(); polygon_index++) {
//            
//                // Get polygon size, you know how many vertices in current polygon.
//                DTint polygon_size = mesh->GetPolygonSize(polygon_index);
//                
//                //retrieve each vertex of current polygon.
//                for(DTint i = 0; i < polygon_size; i++) {
//                
//                    DTint normal_index = 0;
//                    
//                    // Reference mode is direct, the normal index is same as index_by_polygon_index.
//                    if( normal_element->GetReferenceMode() == FbxGeometryElement::eDirect )
//                        normal_index = index_by_polygon_index;
//
//                    // Reference mode is index-to-direct, get normals by the index-to-direct
//                    if(normal_element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//                        normal_index = normal_element->GetIndexArray().GetAt(index_by_polygon_index);
//
//                    // Got normals of each polygon-vertex.
//                    FbxVector4 normal = normal_element->GetDirectArray().GetAt(normal_index);
//                    
////                    if( gVerbose ) FBXSDK_printf("normals for polygon[%d]vertex[%d]: %f %f %f %f \n",
////                        polygon_index, i, normal[0], normal[1], normal[2], normal[3]);
//                    
//                    ASSERT(index_by_polygon_index <= vertices_stream.size());
//
//                    normals_stream[index_by_polygon_index] = Vector3((DTfloat) normal[0], (DTfloat) normal[1], (DTfloat) normal[2]);
//
//                    index_by_polygon_index++;
//                }
//            }
//
//        }//end eByPolygonVertex
//    }//end if normal_element
    
    //
    // Smoothing groups
    //
    
    //get smoothing info
    FbxGeometryElementSmoothing* smoothing_element = mesh->GetElementSmoothing();
    if(smoothing_element) {
     
        smoothing_group.resize(num_verts);

        // Mapping mode is by edge. The mesh usually come from Maya, because Maya can set hard/soft edges.
        // We can get smoothing info(which edges are soft, which edges are hard) by retrieving each edge.
        if( smoothing_element->GetMappingMode() == FbxGeometryElement::eByEdge ) {
        
            LOG_MESSAGE << "Edge based smoothing groups not supported";
        
//            //Let's get smoothing of each edge, since the mapping mode of smoothing element is by edge
//            for(int edge_index = 0; edge_index < mesh->GetMeshEdgeCount(); edge_index++) {
//                int smoothing_index = 0;
//                //reference mode is direct, the smoothing index is same as edge index.
//                //get smoothing by the index of edge
//                if( smoothing_element->GetReferenceMode() == FbxGeometryElement::eDirect )
//                    smoothing_index = edge_index;
//
//                //reference mode is index-to-direct, get smoothing by the index-to-direct
//                if(smoothing_element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//                    smoothing_index = smoothing_element->GetIndexArray().GetAt(edge_index);
//
//                //Got smoothing of each vertex.
//                int smoothing_flag = smoothing_element->GetDirectArray().GetAt(smoothing_index);
//
//                //add your custom code here, to output smoothing or get them into a list, such as KArrayTemplate<int>
//                //. . .
//                
//            }//end for edge_index
          
        // Mapping mode is by polygon. The mesh usually come from 3ds Max, because 3ds Max can set smoothing groups for polygon.
        // We can get smoothing info(smoothing group ID for each polygon) by retrieving each polygon.
        } else if (smoothing_element->GetMappingMode() == FbxGeometryElement::eByPolygon) {
        
            DTint index_by_polygon_index = 0;

            // Let's get smoothing of each polygon, since the mapping mode of smoothing element is by polygon.
            for (int polygon_index = 0; polygon_index < mesh->GetPolygonCount(); polygon_index++) {
            
                int smoothing_index = 0;
                
                // Reference mode is direct, the smoothing index is same as polygon index.
                if( smoothing_element->GetReferenceMode() == FbxGeometryElement::eDirect )
                    smoothing_index = polygon_index;

                // Reference mode is index-to-direct, get smoothing by the index-to-direct
                if(smoothing_element->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                    smoothing_index = smoothing_element->GetIndexArray().GetAt(polygon_index);

                // Got smoothing of each polygon.
                int smoothing_flag = smoothing_element->GetDirectArray().GetAt(smoothing_index);


                // Get polygon size, you know how many vertices in current polygon.
                DTint polygon_size = mesh->GetPolygonSize(polygon_index);
                
                //retrieve each vertex of current polygon.
                for(DTint i = 0; i < polygon_size; i++) {
                    smoothing_group[index_by_polygon_index] = smoothing_flag;
                    index_by_polygon_index++;
                }

            }//end for polygon_index //PolygonCount

        }//end eByPolygonVertex
    }//end if smoothing_element


	new_mesh->set_vertex_stream(vertices_stream);
//	new_mesh->set_normals_stream(normals_stream);
	new_mesh->set_uv_stream0(uvs_stream_0);
	new_mesh->set_uv_stream1(uvs_stream_1);
	new_mesh->set_index_stream(index_stream);
	new_mesh->set_smoothing_groups(smoothing_group);

    // Some stuff we can generate
    new_mesh->collapse_verts();
    new_mesh->generate_normals();
    new_mesh->generate_tangents();
}

//==============================================================================
//==============================================================================

void ImporterGeometryFBX::parse_skeleton (GeometryResource *target, FbxScene* scene, FbxNode *node, FbxNodeAttribute *attr)
{



}

//==============================================================================
//==============================================================================

void ImporterGeometryFBX::iterate_nodes (GeometryResource *target, FbxScene* scene, FbxNode* parent)
{
    if (!parent)
        return;
    
    //const char* nodeName = parent->GetName();
    FbxDouble3 translation = parent->LclTranslation.Get();
    FbxDouble3 rotation = parent->LclRotation.Get();
    FbxDouble3 scaling = parent->LclScaling.Get();
    
    // Iterate attributes
    for(int i = 0; i < parent->GetNodeAttributeCount(); i++) {
        FbxNodeAttribute *attr = parent->GetNodeAttributeByIndex(i);
        FbxNodeAttribute::EType attr_type = attr->GetAttributeType();
    
        switch(attr_type) {
                
            case FbxNodeAttribute::eMesh:
                parse_mesh(target, scene, parent, attr);
                break;
                
            case FbxNodeAttribute::eSkeleton:
                parse_skeleton(target, scene, parent, attr);
                break;

            case FbxNodeAttribute::eUnknown:
            case FbxNodeAttribute::eNull:
            case FbxNodeAttribute::eMarker:
            case FbxNodeAttribute::eNurbs:
            case FbxNodeAttribute::ePatch:
            case FbxNodeAttribute::eCamera:
            case FbxNodeAttribute::eCameraStereo:
            case FbxNodeAttribute::eCameraSwitcher:
            case FbxNodeAttribute::eLight:
            case FbxNodeAttribute::eOpticalReference:
            case FbxNodeAttribute::eOpticalMarker:
            case FbxNodeAttribute::eNurbsCurve:
            case FbxNodeAttribute::eTrimNurbsSurface:
            case FbxNodeAttribute::eBoundary:
            case FbxNodeAttribute::eNurbsSurface:
            case FbxNodeAttribute::eShape:
            case FbxNodeAttribute::eLODGroup:
            case FbxNodeAttribute::eSubDiv:
            default:
                break;
        }

    }
    
    // Iterate children
    for(int i = 0; i < parent->GetChildCount(); ++i) {
        iterate_nodes(target, scene, parent->GetChild(i));
    }
    
}

//==============================================================================
//==============================================================================

DTerr ImporterGeometryFBX::import(GeometryResource *target, std::string args)
{
	FilePath pathname(target->path());
	
    _manager = FbxManager::Create();

    // Create the IO settings object.
    FbxIOSettings *ios = FbxIOSettings::Create(_manager, IOSROOT);
    _manager->SetIOSettings(ios);

    // Create an importer using the SDK manager.
    _importer = FbxImporter::Create(_manager,"");
    
    // Use the first argument as the filename for the importer.
    if(!_importer->Initialize(pathname.full_path().c_str(), -1, _manager->GetIOSettings())) {
        return DT3_ERR_FILE_OPEN_FAILED;
    }
        
    
    // Create a new scene so that it can be populated by the imported file.
    FbxScene* scene = FbxScene::Create(_manager,"myScene");

    // Import the contents of the file into the scene.
    _importer->Import(scene);
    
    // Triangulate everything
    FbxGeometryConverter clsConverter( _manager );
    clsConverter.Triangulate(scene, true);
    clsConverter.SplitMeshesPerMaterial(scene, true);

    // Go through all of the nodes in the scene
    // Print the nodes of the scene and their attributes recursively.
    // Note that we are not printing the root node because it should
    // not contain any attributes.
    
    FbxNode* root_node = scene->GetRootNode();
    iterate_nodes(target, scene, root_node);

    // The file is imported, so get rid of the importer.
    _importer->Destroy();
    
    // Destroy the SDK manager and all the other objects it was handling.
    _manager->Destroy();
    
	return DT3_ERR_NONE;
}

//==============================================================================
//==============================================================================

} // DT3

