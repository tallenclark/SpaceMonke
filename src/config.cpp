#include "config.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "modloader/shared/modloader.hpp"

static ModInfo modInfo = {ID, VERSION};
extern Logger& getLogger();

#define INFO(value...) getLogger().info(value)
#define ERROR(value...) getLogger().error(value)

Configuration& getConfig()
{
    static Configuration config(modInfo);
    config.Load();
    return config;
}

config_t config;

void SaveConfig()
{
    INFO("Saving Configuration...");
    getConfig().config.RemoveAllMembers();
    getConfig().config.SetObject();
    rapidjson::Document::AllocatorType& allocator = getConfig().config.GetAllocator();

    getConfig().config.AddMember("jumpMultiplier", config.jumpMultiplier, allocator);
    getConfig().config.AddMember("velocityLimit", config.velocityLimit, allocator);
    getConfig().config.AddMember("maxJumpSpeed", config.maxJumpSpeed, allocator);
    getConfig().Write();
    INFO("Saved Configuration!");
}

bool LoadConfig()
{
    INFO("Loading config...");
    bool foundEverything = true;
    rapidjson::Document& doc = getConfig().config;
    if(doc.HasMember("jumpMultiplier") && doc["jumpMultiplier"].IsDouble()){
        config.jumpMultiplier = doc["jumpMultiplier"].GetDouble();
    }else{
        foundEverything = false;
    }
    if(doc.HasMember("velocityLimit") && doc["velocityLimit"].IsDouble()){
        config.velocityLimit = doc["velocityLimit"].GetDouble();
    }else{
        foundEverything = false;
    }
    if(doc.HasMember("maxJumpSpeed") && doc["maxJumpSpeed"].IsDouble()){
        config.maxJumpSpeed = doc["maxJumpSpeed"].GetDouble();
    }else{
        foundEverything = false;
    }
    if (foundEverything) INFO("Config Loaded Succesfully!");
    return foundEverything;
}