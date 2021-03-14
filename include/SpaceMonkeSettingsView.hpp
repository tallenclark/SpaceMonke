#pragma once

#include "custom-types/shared/macros.hpp"
#include "monkecomputer/shared/ViewLib/View.hpp"
#include "monkecomputer/shared/InputHandlers/UINumberInputHandler.hpp"

DECLARE_CLASS_CODEGEN(SpaceMonke, SpaceMonkeSettingsView, GorillaUI::Components::View, 
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, DidActivate, bool firstActivation);
    DECLARE_METHOD(void, Redraw);
    DECLARE_METHOD(void, DrawHeader);
    DECLARE_METHOD(void, DrawNumber);
    DECLARE_METHOD(void, EnterNumber, int number);
    DECLARE_METHOD(void, OnKeyPressed, int key);

    public:
        GorillaUI::UINumberInputHandler* numberInputHandler = nullptr;

    REGISTER_FUNCTION(SpaceMonkeSettingsView,
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(DidActivate);
        REGISTER_METHOD(Redraw);
        REGISTER_METHOD(DrawHeader);
        REGISTER_METHOD(DrawNumber);
        REGISTER_METHOD(EnterNumber);
        REGISTER_METHOD(OnKeyPressed);
    )
)