#include "SpaceMonkeSettingsView.hpp"
#include "config.hpp"
#include "monkecomputer/shared/ViewLib/CustomComputer.hpp"
#include "monkecomputer/shared/InputHandlers/UINumberInputHandler.hpp"
#include "monkecomputer/shared/InputHandlers/UIToggleInputHandler.hpp"

DEFINE_CLASS(SpaceMonke::SpaceMonkeSettingsView);

using namespace GorillaUI;

namespace SpaceMonke
{
    void SpaceMonkeSettingsView::Awake()
    {
        numberInputHandler = new UINumberInputHandler(EKeyboardKey::Enter, true);
        toggleInputHandler = new UIToggleInputHandler(EKeyboardKey::Option1, EKeyboardKey::Option1, true);

        ((UINumberInputHandler*)numberInputHandler)->number = config.multiplier * 100;
        ((UINumberInputHandler*)numberInputHandler)->max = 1000;
        ((UIToggleInputHandler*)toggleInputHandler)->state = config.enabled;
    }

    void SpaceMonkeSettingsView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&SpaceMonkeSettingsView::EnterNumber, this, std::placeholders::_1);
        ((UINumberInputHandler*)numberInputHandler)->numberCallback = fun;

        std::function<void(bool)> fun2 = std::bind(&SpaceMonkeSettingsView::ToggleActive, this, std::placeholders::_1);
        ((UIToggleInputHandler*)toggleInputHandler)->toggleCallback = fun2;
        Redraw();
    }

    void SpaceMonkeSettingsView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawNumber();

        text += "\n  Space Monke is: ";
        text += config.enabled ? "<color=#00ff00>enabled</color>" : "<color=#ff0000>disabled</color>";
        text += "<size=40>\n    Press Option1 to toggle enabled state\n</size>";

        CustomComputer::Redraw();
    }

    void SpaceMonkeSettingsView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Space Monke/Group</color> ==</color>\n";
    }

    void SpaceMonkeSettingsView::DrawNumber()
    {
        text += "\n  Configure the jump multiplier:\n";
        text += string_format("  Multiplier: %d", ((UINumberInputHandler*)numberInputHandler)->number);
    }

    void SpaceMonkeSettingsView::EnterNumber(int number)
    {
        config.multiplier = (float)number / 100.0f;
        SaveConfig();
    }

    void SpaceMonkeSettingsView::ToggleActive(bool value)
    {
        config.enabled = value;
        SaveConfig();
    }

    void SpaceMonkeSettingsView::OnKeyPressed(int key)
    {
        ((UINumberInputHandler*)numberInputHandler)->HandleKey((EKeyboardKey)key);
        ((UIToggleInputHandler*)toggleInputHandler)->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}