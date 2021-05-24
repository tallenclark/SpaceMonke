#include "SpaceMonkeWatchView.hpp"
#include "config.hpp"
#include "monkecomputer/shared/ViewLib/MonkeWatch.hpp"

DEFINE_TYPE(SpaceMonke::SpaceMonkeWatchView);

using namespace GorillaUI;

namespace SpaceMonke
{
    void SpaceMonkeWatchView::Awake()
    {
        numberSelectionHandler = new UISelectionHandler(EKeyboardKey::Left, EKeyboardKey::Right, EKeyboardKey::Enter, true, false);
        numberSelectionHandler->max = 21;
        numberSelectionHandler->currentSelectionIndex = (int)(config.multiplier * 2.0f);

        optionSelectionHandler = new UISelectionHandler(EKeyboardKey::Up, EKeyboardKey::Down, EKeyboardKey::Enter, true, false);
        optionSelectionHandler->max = 2;

    }

    void SpaceMonkeWatchView::DidActivate(bool firstActivation)
    {
        std::function<void(int)> fun = std::bind(&SpaceMonkeWatchView::OnSelect, this, std::placeholders::_1);
        numberSelectionHandler->selectionCallback = fun;
        optionSelectionHandler->selectionCallback = fun;
        Redraw();
    }

    void SpaceMonkeWatchView::Redraw()
    {
        text = "";

        DrawHeader();
        DrawBody();

        watch->Redraw();
    }

    void SpaceMonkeWatchView::DrawHeader()
    {
        text += "<color=#ffff00>== <color=#fdfdfd>Space Monke/Group</color> ==</color>\n";
    }

    void SpaceMonkeWatchView::DrawBody()
    {
        text += "\nSpace Monke is:\n";
        text += optionSelectionHandler->currentSelectionIndex == 0 ? "<color=#ed6540>></color> " : "  ";
        text += config.enabled ? "<color=#00ff00>enabled</color>" : "<color=#ff0000>disabled</color>";

        text += "\n\nConfigure the jump multiplier:\n";
        text += string_format("%sMultiplier: < %d >", (optionSelectionHandler->currentSelectionIndex == 1) ? "<color=#ed6540>></color> " : "  ", numberSelectionHandler->currentSelectionIndex * 50);
    }

    void SpaceMonkeWatchView::OnSelect(int number)
    {
        switch (optionSelectionHandler->currentSelectionIndex)
        {
            case 0:
                config.enabled ^= 1;
                break;
            case 1:
                config.multiplier = (float)numberSelectionHandler->currentSelectionIndex / 2.0f;
                break;
            default:
                break;
        }

        SaveConfig();
    }

    void SpaceMonkeWatchView::OnKeyPressed(int key)
    {
        optionSelectionHandler->HandleKey((EKeyboardKey)key);

        if (optionSelectionHandler->currentSelectionIndex == 1)
        {
            numberSelectionHandler->HandleKey((EKeyboardKey)key);
        }
        Redraw();
    }
}