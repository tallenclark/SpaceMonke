#pragma once

#include "custom-types/shared/macros.hpp"
#include "monkecomputer/shared/ViewLib/View.hpp"

DECLARE_CLASS_CODEGEN(SpaceMonke, SpaceMonkeSettingsView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawNumber);
    DECLARE_METHOD(void, EnterNumber, int number);
    DECLARE_METHOD(void, ToggleActive, bool value);
    DECLARE_METHOD(void, OnKeyPressed, int key);
    
    DECLARE_INSTANCE_FIELD(void*, numberInputHandler);
    DECLARE_INSTANCE_FIELD(void*, toggleInputHandler);

    REGISTER_FUNCTION(SpaceMonkeSettingsView,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawNumber);
        REGISTER_METHOD(EnterNumber);
        REGISTER_METHOD(ToggleActive);
        REGISTER_METHOD(OnKeyPressed);
        REGISTER_FIELD(numberInputHandler);
        REGISTER_FIELD(toggleInputHandler);
    )
)