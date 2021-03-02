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

    getConfig().config.AddMember("multiplier", config.multiplier, allocator);
    getConfig().Write();
    INFO("Saved Configuration!");
}

bool LoadConfig()
{
    INFO("Loading config...");
    bool foundEverything = true;
    rapidjson::Document& doc = getConfig().config;
    if(doc.HasMember("multiplier") && doc["multiplier"].IsDouble()) {
        config.multiplier = doc["multiplier"].GetDouble();
    }else if (doc.HasMember("multiplier") && doc["multiplier"].IsInt()) {
        config.multiplier = (double)doc["multiplier"].GetInt();
    } else {
        foundEverything = false;
    }
    if (foundEverything) INFO("Config Loaded Succesfully!");
    return foundEverything;
}