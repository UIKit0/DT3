//==============================================================================
///	
///	File: ModelTools_cmd.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/System/Command.hpp"

#ifdef DT3_COMMANDS

#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/FileManager.hpp"
#include "DT3Core/Types/Utility/CommandRegistry.hpp"
#include "DT3Core/Types/Utility/CommandResult.hpp"
#include "DT3Core/Types/Media/TWMWriter.hpp"
#include "DT3Core/Resources/ResourceTypes/GeometryResource.hpp"
#include <algorithm>
#include <map>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

class ModelTools_cmd: public Command {
    public:
        DEFINE_TYPE(ModelTools_cmd,Command);
        DEFINE_CREATE
        
        void register_commands (void) {
            CommandRegistry::register_command("TestLoadMesh", &ModelTools_cmd::do_test_load_mesh);
            CommandRegistry::register_command("SplitMesh", &ModelTools_cmd::do_split_mesh);
        }

        static CommandResult do_test_load_mesh (CommandContext &ctx, const CommandParams &p);
        static CommandResult do_split_mesh (CommandContext &ctx, const CommandParams &p);
};

//==============================================================================
//==============================================================================

IMPLEMENT_FACTORY_COMMAND(ModelTools_cmd)

//==============================================================================
//==============================================================================

CommandResult ModelTools_cmd::do_test_load_mesh (CommandContext &ctx, const CommandParams &p)
{
    if (p.count() != 2) {
        return CommandResult(false, "Usage: TestLoadMesh [file]", CommandResult::UPDATE_NONE);
    }
    
    std::shared_ptr<GeometryResource> geom = GeometryResource::import_resource(FilePath(p[1]));
    if (!geom)
        return CommandResult(false, "Failed to load geometry", CommandResult::UPDATE_NONE);
    else
        return CommandResult(true, "Successfully loaded geometry", CommandResult::UPDATE_NONE);
}

CommandResult ModelTools_cmd::do_split_mesh (CommandContext &ctx, const CommandParams &p)
{
    if (p.count() != 2) {
        return CommandResult(false, "Usage: SplitMesh [file]", CommandResult::UPDATE_NONE);
    }
    
    std::shared_ptr<GeometryResource> geom = GeometryResource::import_resource(FilePath(p[1]));
    if (!geom)
        return CommandResult(false, "Failed to load geometry", CommandResult::UPDATE_NONE);


    std::map<std::string, std::list<std::shared_ptr<Mesh>>> split_meshes;
    const std::vector<std::shared_ptr<Mesh>> &meshes = geom->meshes();
    
    // Sort meshes into buckets
    for (auto i : meshes) {
        split_meshes[i->material()].push_back(i);
    }
    
    // Iterate through lists of meshes
    for (auto i : split_meshes) {
        std::string name;
        
        if (i.first.size() > 0)
            name = i.first + ".twm";
        else
            name = "Unknown.twm";

        // Write list of meshes
        TWMWriter::write(FilePath(name), i.second);
    }
    
    return CommandResult(true, "Split geometry success", CommandResult::UPDATE_NONE);
}

//==============================================================================
//==============================================================================

} // DT3

#endif // DT3_COMMANDS

