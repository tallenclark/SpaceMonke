#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include <string>

#include "beatsaber-hook/shared/utils/typedefs.h"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

ModInfo modInfo;

#define INFO(value...) getLogger().info(value)
#define ERROR(value...) getLogger().error(value)

Logger& getLogger()
{
    static Logger* logger = new Logger(modInfo, LoggerOptions(false, true));
    return *logger;
}

bool allowSpaceMonke = true;
bool resetSpeed = false;

// this is how to make a method hook, it follows the convention hookname, returntype, if an instance method, a reference to self, and then the args
MAKE_HOOK_OFFSETLESS(Player_Awake, void, Il2CppObject* self)
{
    // telling us in the log that this method was called
    INFO("Player Awake Hook Called!");

    // getting the field value of jump multiplier on the player
    //                                                    return type V     V the object we want to check
    //                                                                V     V          V the field name
    float jumpMultiplier = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(self, "jumpMultiplier"));
    float velocityLimit = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(self, "velocityLimit"));
    float maxJumpSpeed = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(self, "maxJumpSpeed"));
    
    // logging it so we know what it was
    getLogger().info("jumpMultiplier was: %.2f\nVelocityLimit was: %.2f\nMaxJumpSpeed was: %.2f", jumpMultiplier, velocityLimit, maxJumpSpeed);

    // run the original code, because otherwise the player awake code will never be ran and this could cause issues, tthis can be done at anytime during the hook
    Player_Awake(self);
}

MAKE_HOOK_OFFSETLESS(Player_Update, void, Il2CppObject* self)
{
    // if allowed, set these values
    if (allowSpaceMonke)
    {
        resetSpeed = true;
        CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "jumpMultiplier", 40.0f));
        CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "velocityLimit", 0.01f));
        CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "maxJumpSpeed", 40.0f));
    } 
    else // if not allowed
    {
        // speed will be reset
        if (resetSpeed)
        {
            resetSpeed = false;
            CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "jumpMultiplier", 1.1f));
            CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "velocityLimit", 0.3f));
            CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "maxJumpSpeed", 6.5f));
        }
    }
    Player_Update(self);
}

MAKE_HOOK_OFFSETLESS(PhotonNetworkController_OnJoinedRoom, void, Il2CppObject* self)
{
    PhotonNetworkController_OnJoinedRoom(self);
    INFO("Room Joined!");
    // get wether or not this is a private room
    allowSpaceMonke = CRASH_UNLESS(il2cpp_utils::GetFieldValue<bool>(self, "isPrivate"));
}

// setup lets the modloader know the mod ID and version as defined in android.mk
extern "C" void setup(ModInfo& info)
{
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
    INFO("Hellowo World from setup!");
}

// load needs to be declared like this so the modloader can call it
extern "C" void load()
{
    INFO("Hello World From Load!");
 
    Logger& logger = getLogger();
    il2cpp_functions::Init();
    INFO("Installing hooks...");

    // installing a hook follows the principle of logger, hookname, findmethod, where findmethod takes args namespace, class, method, argcount
    INSTALL_HOOK_OFFSETLESS(logger, Player_Awake, il2cpp_utils::FindMethodUnsafe("GorillaLocomotion", "Player", "Awake", 0));
    INSTALL_HOOK_OFFSETLESS(logger, Player_Update, il2cpp_utils::FindMethodUnsafe("GorillaLocomotion", "Player", "Update", 0));
    INSTALL_HOOK_OFFSETLESS(logger, PhotonNetworkController_OnJoinedRoom, il2cpp_utils::FindMethodUnsafe("", "PhotonNetworkController", "OnJoinedRoom", 0));

    INFO("Installed hooks!");
}