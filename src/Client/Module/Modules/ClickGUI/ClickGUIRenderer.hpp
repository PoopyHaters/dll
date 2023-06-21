#pragma once
#include <format>
#include <Windows.h>
#include "../../../Events/Listener.hpp"
#include "../../../Events/Input/MouseEvent.hpp"
#include "../../../../Utils/Logger/Logger.hpp"
#include "../../../GUI/D2D.hpp"
#include "../Module.hpp"
#include "../../../GUI/Engine/Engine.hpp"
#include "../../../GUI/Engine/Constraints.hpp"
#include "Elements/ClickGUIElements.hpp"
#include "../../../Hook/Hooks/Render/SwapchainHook.hpp"
#include "../../Manager.hpp"
#include "../../../GUI/Engine/animations/fadeinout.hpp"

struct PageType {
    std::string type = "normal";
    std::string module;
};

class ClickGUIRenderer : public Listener {

    template <typename T>
    void lerp(T& a, const T& b, float t)
    {
        // Perform linear interpolation between a and b based on t
        a = a + (b - a) * t;
    }

    Module* module;
    std::string curr;
    bool TestToggle = false;
    float baseHeightReal = 0.64f;

    void onRender(RenderEvent &event) override {



        if(module->enabled && SwapchainHook::init) {

            /* Base Rectangle Start */
            FlarialGUI::ApplyGaussianBlur(6.0);

            float baseWidth = Constraints::RelativeConstraint(0.85);

            if(ClickGUIRenderer::page.type == "settings") {
                lerp(baseHeightReal, 0.35f, 0.1f);
                //FadeEffect::ApplyFadeOutEffect(0.015f * FlarialGUI::frameFactor, baseHeightReal, 0.35f);
            } else {
                lerp(baseHeightReal, 0.64f, 0.1f);
                //FadeEffect::ApplyFadeInEffect(0.015f * FlarialGUI::frameFactor, 0.64f, baseHeightReal);
            }

            float baseHeight = Constraints::RelativeConstraint(baseHeightReal);

            Vec2<float> center = Constraints::CenterConstraint(baseWidth, baseHeight, "r", 1, 1);
            Vec2<float> round = Constraints::RoundingConstraint(50, 50);

            FlarialGUI::RoundedRect(center.x, center.y, D2D1::ColorF(18.0f / 255.0f, 14.0f / 255.0f, 15.0f / 255.0f), baseWidth, baseHeight, round.x, round.x);
            FlarialGUI::PushSize(center.x, center.y, baseWidth, Constraints::RelativeConstraint(0.64f));

            /* Base Rectangle End */


            /* Nav Bar Start */

            float navigationBarWidth = Constraints::RelativeConstraint(1.309f);
            float navigationBarHeight = Constraints::RelativeConstraint(0.14f);
            float navx = Constraints::PercentageConstraint(0.008f, "left");
            float navy = Constraints::PercentageConstraint(0.009f, "top");
            round = Constraints::RoundingConstraint(50, 50);

            FlarialGUI::RoundedRect(navx, navy, D2D1::ColorF(32.0f/255.0f, 26.0f/255.0f, 27.0f/255.0f), navigationBarWidth, navigationBarHeight, round.x ,round.x);


            FlarialGUI::PushSize(navx, navy, navigationBarWidth, navigationBarHeight);

            /* Nav Bar End */

            /* Logo Start */


            float logoWidth = Constraints::RelativeConstraint(1.21);

            float logoX = navx - Constraints::SpacingConstraint(0.05, logoWidth);
            float logoY = (navy + navigationBarHeight / 2.0f - logoWidth / 2.0f);

            FlarialGUI::Image("\\Flarial\\assets\\logo.png", D2D1::RectF(logoX, logoY, logoX + logoWidth, logoY + logoWidth));

            /* Logo End */

            /* tab buttons start */


            float RadioButtonWidth = Constraints::RelativeConstraint(0.24, "width");
            float RadioButtonHeight = Constraints::RelativeConstraint(0.5);

            float radioX = navx - Constraints::SpacingConstraint(-0.85, logoWidth);
            float radioY (navy + navigationBarHeight / 2.0f - RadioButtonHeight / 2.0f);

            round = Constraints::RoundingConstraint(30, 30);

            if(FlarialGUI::RoundedRadioButton(1, radioX, radioY, D2D1::ColorF(255.0f/255.0f, 36.0f/255.0f, 56.0f/255.0f), D2D1::ColorF(D2D1::ColorF::White), L"Modules", RadioButtonWidth, RadioButtonHeight, round.x, round.x, "modules", curr))
            {
                this->curr = "modules";
                ClickGUIRenderer::page.type = "normal";
            }



            logoWidth = Constraints::RelativeConstraint(0.21f);

            radioX -= Constraints::SpacingConstraint(-0.53f, logoWidth);
            radioY -= Constraints::SpacingConstraint(-0.53f, logoWidth);

            float shit = Constraints::RelativeConstraint(0.33f);
            round = Constraints::RoundingConstraint(15, 15);

            FlarialGUI::RoundedRect(radioX + Constraints::SpacingConstraint(-0.15f, logoWidth), radioY + Constraints::SpacingConstraint(-0.12f, logoWidth), D2D1::ColorF(139.0f / 255.0f, 27.0f / 255.0f, 37.0f / 255.0f), shit, shit, round.x, round.x);

            radioX -= Constraints::SpacingConstraint(-0.125f, logoWidth);
            radioY -= Constraints::SpacingConstraint(-0.15f, logoWidth);
            FlarialGUI::Image("\\Flarial\\assets\\modules.png", D2D1::RectF(radioX , radioY, radioX + logoWidth, radioY + logoWidth));



            radioX = navx - Constraints::SpacingConstraint(-0.85f, logoWidth);
            radioY = (navy + navigationBarHeight / 2.0f - RadioButtonHeight / 2.0f);

            round = Constraints::RoundingConstraint(30, 30);
            radioX += Constraints::SpacingConstraint(15.f, logoWidth);
            if(FlarialGUI::RoundedRadioButton(0, radioX, radioY, D2D1::ColorF(255.0f/255.0f, 36.0f/255.0f, 56.0f/255.0f), D2D1::ColorF(D2D1::ColorF::White), L"Settings", RadioButtonWidth, RadioButtonHeight, round.x, round.x, "settings", this->curr)) this->curr = "settings";;

            radioX -= Constraints::SpacingConstraint(-0.53f, logoWidth);
            radioY -= Constraints::SpacingConstraint(-0.53f, logoWidth);

            round = Constraints::RoundingConstraint(15, 15);

            FlarialGUI::RoundedRect(radioX + Constraints::SpacingConstraint(-0.15f, logoWidth), radioY + Constraints::SpacingConstraint(-0.12f, logoWidth), D2D1::ColorF(139.0f / 255.0f, 27.0f / 255.0f, 37.0f / 255.0f), shit, shit, round.x, round.x);

            radioX -= Constraints::SpacingConstraint(-0.125f, logoWidth);
            radioY -= Constraints::SpacingConstraint(-0.15f, logoWidth);
            FlarialGUI::Image("\\Flarial\\assets\\gear.png", D2D1::RectF(radioX , radioY, radioX + logoWidth, radioY + logoWidth));

            /* tab buttons end */

            FlarialGUI::PopSize(); // Pops nav bar
                /* Mod Card Start */

                std::string e = this->curr;

                if(ClickGUIRenderer::page.type == "normal") {

                    if (e == "modules") {

                        float modWidth = Constraints::RelativeConstraint(0.19f, "height", true);
                        float modHeight = Constraints::RelativeConstraint(0.1369f, "height", true);

                        Vec2<float> modcenter = Constraints::CenterConstraint(modWidth, modHeight, "both", -0.60,-0.52);

                        FlarialGUI::PushSize(center.x, center.y, baseWidth, baseHeight);

                        float scrollWidth = Constraints::RelativeConstraint(1.12);
                        float scrollHeight = Constraints::RelativeConstraint(0.84);
                        Vec2<float> scrollcenter = Constraints::CenterConstraint(scrollWidth, scrollHeight, "y", 0.0, 1);

                        FlarialGUI::PopSize();

                        FlarialGUI::ScrollBar(120, 120, 10, 160, 2);

                        FlarialGUI::SetScrollView(scrollcenter.x, scrollcenter.y, scrollWidth, scrollHeight);

                        float xModifier = 0.0f;
                        float yModifier = 0.0f;

                        int i = 0;
                        for (Module *real: ModuleManager::modules) {
                            ClickGUIElements::ModCard(modcenter.x + xModifier, modcenter.y + yModifier, real,
                                                      real->icon, i);

                            xModifier += Constraints::SpacingConstraint(1.09, modWidth);
                            if ((++i % 3) == 0) {
                                yModifier += Constraints::SpacingConstraint(0.8, modWidth);
                                xModifier = 0.0f;
                            }
                        }

                        FlarialGUI::UnsetScrollView();
                    } else if (e == "settings") {

                        D2D1_COLOR_F color = D2D1::ColorF(255.0f / 255.0f, 35.0f / 255.0f, 58.0f / 255.0f);

                        if (!this->TestToggle) {
                            color = D2D1::ColorF(112.0f / 255.0f, 75.0f / 255.0f, 82.0f / 255.0f);
                        }

                        if (FlarialGUI::Toggle(1, Constraints::PercentageConstraint(0.2, "left"),
                                               Constraints::PercentageConstraint(0.3, "top"), color,
                                               D2D1::ColorF(D2D1::ColorF::White), this->TestToggle))
                            this->TestToggle = !this->TestToggle;


                        FlarialGUI::Slider(0, Constraints::PercentageConstraint(0.5, "left"),
                                           Constraints::PercentageConstraint(0.5, "top"),
                                           D2D1::ColorF(255.0f / 255.0f, 36.0f / 255.0f, 56.0f / 255.0f),
                                           D2D1::ColorF(154.0f / 255.0f, 107.0f / 255.0f, 114.0f / 255.0f),
                                           D2D1::ColorF(D2D1::ColorF::White));


                        //FlarialGUI::TextBox(0, 150, 150, 150, 150);

                        //FlarialGUI::ColorWheel(300, 300, 100);
                    }

                    /* Mod Card End */
                } else if (ClickGUIRenderer::page.type == "settings") {

                    this->curr = "settings";

                    FlarialGUI::PushSize(center.x, center.y, baseWidth, baseHeight);

                    float rectX = Constraints::PercentageConstraint(0.01, "left");
                    float rectY = Constraints::PercentageConstraint(0.32, "top");
                    float rectWidth = Constraints::RelativeConstraint(0.965, "width");
                    float rectHeight = Constraints::RelativeConstraint(0.55);
                    round = Constraints::RoundingConstraint(50, 50);

                    float anotherRectHeight = Constraints::RelativeConstraint(0.60);
                    float anotherRectWidth = Constraints::RelativeConstraint(0.981, "width");

                    FlarialGUI::RoundedRect(rectX, rectY, D2D1::ColorF(32.0f/255.0f, 26.0f/255.0f, 27.0f/255.0f), anotherRectWidth, anotherRectHeight, round.x, round.x);

                    round = Constraints::RoundingConstraint(45, 45);
                    FlarialGUI::RoundedRect(rectX + Constraints::SpacingConstraint(0.0085, rectWidth), rectY + Constraints::SpacingConstraint(0.01, rectWidth), D2D1::ColorF(63.0f / 255.0f, 42.0f / 255.0f, 45.0f / 255.0f), rectWidth, rectHeight, round.x, round.x);

                    FlarialGUI::PopSize();

                    FlarialGUI::PushSize(rectX + Constraints::SpacingConstraint(0.0085, rectWidth), rectY + Constraints::SpacingConstraint(0.01, rectWidth), rectWidth, rectHeight);

                    ModuleManager::getModule(ClickGUIRenderer::page.module)->SettingsRender();

                    FlarialGUI::PopSize();

                }

            FlarialGUI::PopSize(); // Pops base rect


        }
    }

    void onKey(KeyEvent &event) override {

        if(event.GetKey() == module->keybind && static_cast<ActionType>(event.GetAction()) == ActionType::PRESSED) module->enabled = !module->enabled;
    }

public:
    explicit ClickGUIRenderer(const char string[5], Module *emodule) {
        this->name = string;
        this->module = emodule;
        this->curr = "modules";
    }

    static inline PageType page;
};
