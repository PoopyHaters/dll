#pragma once

#include "../Module.hpp"

// TODO: combine into 1

struct HUDElement {
    std::string mcName;
    Vec2<float> currentPos{};
    bool* enabled{};
    static inline Vec2<float> originalPos = Vec2<float>{0.0f, 0.0f};
    Vec2<float> currentSize = Vec2<float>{0.0f, 0.0f};
};

class MovableHUD : public Module {
private:
    std::array<HUDElement, 6> elements{};
    Vec2<float> currentPos{};
    bool enabled = false;
    static inline Vec2<float> originalPos = Vec2<float>{0.0f, 0.0f};
    Vec2<float> currentSize = Vec2<float>{0.0f, 0.0f};
public:
    MovableHUD() : Module("Movable HUD", "Makes everything on screen movable!", IDR_MOVABLE_PNG, "") {
        Module::setup();
    };

    void onEnable() override {
    }

    void onDisable() override {
    }

    void defaultConfig() override {
        if (settings.getSettingByName<float>("percentageX") == nullptr) {
            settings.addSetting("percentageX", 0.0f);
        }
        if (settings.getSettingByName<float>("percentageY") == nullptr) {
            settings.addSetting("percentageY", 0.0f);
        }
    }

    void settingsRender(float settingsOffset) override {}
};