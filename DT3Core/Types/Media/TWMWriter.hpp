#ifndef DT3_TWMWRITER
#define DT3_TWMWRITER
//==============================================================================
///	
///	File: TWMWriter.hpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/Graphics/Mesh.hpp"
#include <list>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class FilePath;
class BinaryFileStream;

//==============================================================================
/// Class
//==============================================================================

class TWMWriter {
    private:
								TWMWriter			(void);	
								TWMWriter			(const TWMWriter &rhs);
        TWMWriter &             operator =			(const TWMWriter &rhs);
								~TWMWriter			(void);

	public:
		/// Exports list of meshes to a twm file
		/// \param pathname output file path
		/// \param meshes meshes to write
        /// \retrun error code
        static void             write               (const FilePath &pathname, const std::list<std::shared_ptr<Mesh>> &meshes);

    private:
    
		enum {
			MAGIC = 0x5E11E70D,
			
			FILE = 0,
				MESHES = 1,
					MESHES_MESH = 2,
						MESHES_MESH_NAME = 3,
						MESHES_MESH_POSITIONS = 4,
						MESHES_MESH_NORMALS = 5,
						MESHES_MESH_UV_SETS = 6,
							MESHES_MESH_UVS = 7,
						MESHES_MESH_SKINNING = 8,
							MESHES_MESH_SKINNING_JOINTS = 9,
							MESHES_MESH_SKINNING_INFLUENCES = 10,
						MESHES_MESH_INDICES = 12,
				SKELETON = 13
		};

        // Exporting
        static DTsize   begin_export_section        (BinaryFileStream &file, DTint section);
        static void     end_export_section          (BinaryFileStream &file, DTsize size_location);


};

//==============================================================================
//==============================================================================

} // DT3

#endif
