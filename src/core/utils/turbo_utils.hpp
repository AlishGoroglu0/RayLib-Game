#pragma once

#include "../constants/common.hpp"  // This gives us uint8_t
#include "../constants/theme.hpp"

class TurboUtils {
public:
    static bool ShouldActivateTurbo(uint8_t turboPoint, uint8_t turboLimit);
    static void ActivateTurbo(bool& isTurboMode, float& turboTimer, float turboDuration, uint8_t& turboPoint);
    static bool UpdateTurboTimer(bool& isTurboMode, float& turboTimer, float deltaTime);
    static float ApplyFireRateBonus(float fireTimer, float fireCooldown, bool isTurboMode);
    static void DeactivateTurbo(bool& isTurboMode, float& turboTimer);
    static bool AddTurboPoint(uint8_t& turboPoint, uint8_t turboLimit);
};