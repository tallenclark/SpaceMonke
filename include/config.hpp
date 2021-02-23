// only ever include this header once in a compilation unit
#pragma once

// config struct for easy access to values, and also defaults
struct config_t {
    double jumpMultiplier = 1.1;
    double velocityLimit = 0.3;
    double maxJumpSpeed = 6.5;
};

// all files that include this header now have access to the config variable in the config.cpp file
extern config_t config;

void SaveConfig();
bool LoadConfig();