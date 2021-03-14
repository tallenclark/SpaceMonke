#include "SpaceMonkeSettingsView.hpp"
#include "config.hpp"
#include "monkecomputer/shared/ViewLib/CustomComputer.hpp"

DEFINE_CLASS(SpaceMonke::SpaceMonkeSettingsView);

using namespace GorillaUI;

namespace SpaceMonke
{
    void SpaceMonkeSettingsView::Awake()
    {
        if (!numberInputHandler) numberInputHandler = new UINumberInputHandler(EKeyboardKey::Enter, true);
        numberInputHandler->number = config.multiplier * 100;
        numberInputHandler->max = 100000;
    }

    void SpaceMonkeSettingsView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&SpaceMonkeSettingsView::EnterNumber, this, std::placeholders::_1);
        numberInputHandler->numberCallback = fun;
        Redraw();
    }

    void SpaceMonkeSettingsView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawNumber();

        CustomComputer::Redraw();
    }

    void SpaceMonkeSettingsView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Space Monke/Group</color> ==</color>\n";
    }

    void SpaceMonkeSettingsView::DrawNumber()
    {
        text += "\n  Configure the jump multiplier:\n";
        text += string_format("  Multiplier: %d", numberInputHandler->number);
    }

    void SpaceMonkeSettingsView::EnterNumber(int number)
    {
        config.multiplier = (float)number / 100.0f;
    }

    void SpaceMonkeSettingsView::OnKeyPressed(int key)
    {
        numberInputHandler->HandleKey((EKeyboardKey)key);
        Redraw();
    }
}