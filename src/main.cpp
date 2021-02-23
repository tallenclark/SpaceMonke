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
    
    // setting it to 40
    CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "jumpMultiplier", 40.0f));
    CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "velocityLimit", 0.01f));
    CRASH_UNLESS(il2cpp_utils::SetFieldValue(self, "maxJumpSpeed", 40.0f));

    // reading the value again to show it was actually changed
    jumpMultiplier = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(self, "jumpMultiplier"));
    velocityLimit = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(self, "velocityLimit"));
    maxJumpSpeed = CRASH_UNLESS(il2cpp_utils::GetFieldValue<float>(self, "maxJumpSpeed"));

    // logging again
    getLogger().info("jumpMultiplier is now: %.2f\nVelocityLimit is now: %.2f\nMaxJumpSpeed is now: %.2f", jumpMultiplier, velocityLimit, maxJumpSpeed);

    // run the original code, because otherwise the player awake code will never be ran and this could cause issues, tthis can be done at anytime during the hook
    Player_Awake(self);
}

MAKE_HOOK_OFFSETLESS(VRRig_SetJumpMultiplier, void, Il2CppObject* self, float jumpMultiplier)
{
    INFO("VRRig Jump Multiplier set to: %.2f, multiplying by 20 to: %.2f", jumpMultiplier, jumpMultiplier * 20.0f);
    VRRig_SetJumpMultiplier(self, jumpMultiplier * 20.0f);
}

MAKE_HOOK_OFFSETLESS(VRRig_SetJumpLimit, void, Il2CppObject* self, float jumpLimit)
{
    INFO("VRRig Jump Limit set to: %.2f, multiplying by 20 to: %.2f", jumpLimit, jumpLimit * 20.0f);
    VRRig_SetJumpLimit(self, jumpLimit * 20.0f);
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
    INSTALL_HOOK_OFFSETLESS(logger, VRRig_SetJumpMultiplier, il2cpp_utils::FindMethodUnsafe("", "VRRig", "SetJumpMultiplier", 1));
    INSTALL_HOOK_OFFSETLESS(logger, VRRig_SetJumpLimit, il2cpp_utils::FindMethodUnsafe("", "VRRig", "SetJumpLimit", 1));

    INFO("Installed hooks!");
}