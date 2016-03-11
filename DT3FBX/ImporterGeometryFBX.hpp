#ifndef DT3_IMPORTERGEOMETRYFBX
#define DT3_IMPORTERGEOMETRYFBX
//==============================================================================
///	
///	File: ImporterGeometryFBX.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Resources/Importers/ImporterGeometry.hpp"
#include "DT3Core/Types/Math/Vector2.hpp"
#include "DT3Core/Types/Math/Vector3.hpp"
#include "DT3Core/Types/Math/Weights.hpp"
#include "DT3Core/Types/Math/Triangle.hpp"
#include "DT3Core/Types/Math/Matrix4.hpp"
#include "DT3Core/Types/Animation/SkeletonJoint.hpp"
#include <vector>

#include <fbxsdk.h>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class BinaryFileStream;

//==============================================================================
/// Class
//==============================================================================

class ImporterGeometryFBX: public ImporterGeometry {
    public:
        DEFINE_TYPE(ImporterGeometryFBX,ImporterGeometry)
		DEFINE_CREATE
         
										ImporterGeometryFBX	(void);	
    
	private:
										ImporterGeometryFBX	(const ImporterGeometryFBX &rhs);
        ImporterGeometryFBX &			operator =			(const ImporterGeometryFBX &rhs);
    
    public:
        virtual							~ImporterGeometryFBX(void);
                
    public:        	
		/// Imports a fbx file into an GeometryResource
		/// \param target object to import geometry into
		/// \param args arguments to importer
        /// \retrun error code
		virtual DTerr					import				(GeometryResource *target, std::string args);


    private:
        void                            parse_mesh          (GeometryResource *target, FbxScene* scene, FbxNode *node, FbxNodeAttribute *attr);
        void                            parse_skeleton      (GeometryResource *target, FbxScene* scene, FbxNode *node, FbxNodeAttribute *attr);
        void                            iterate_nodes       (GeometryResource *target, FbxScene* scene, FbxNode* parent);

        FbxManager                      *_manager;
        FbxImporter                     *_importer;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
