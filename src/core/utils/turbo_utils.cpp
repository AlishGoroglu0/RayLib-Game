#include "turbo_utils.hpp"

bool TurboUtils::ShouldActivateTurbo(uint8_t turboPoint, uint8_t turboLimit) {
    return turboPoint >= turboLimit;
}

void TurboUtils::ActivateTurbo(bool& isTurboMode, float& turboTimer, float turboDuration, uint8_t& turboPoint) {
    isTurboMode = true;
    turboTimer = turboDuration;
    turboPoint = 0;
}

bool TurboUtils::UpdateTurboTimer(bool& isTurboMode, float& turboTimer, float deltaTime) {
    if (!isTurboMode) return false;
    
    turboTimer -= deltaTime;
    if (turboTimer <= 0.0f) {
        isTurboMode = false;
        turboTimer = 0.0f;
        return false;
    }
    return true;
}

float TurboUtils::ApplyFireRateBonus(float fireTimer, float fireCooldown, bool isTurboMode) {
    if (isTurboMode) {
        return fireCooldown * 0.05f;  // Faster rate of fire
    } else {
        return fireCooldown;          // Normal speed
    }
}

void TurboUtils::DeactivateTurbo(bool& isTurboMode, float& turboTimer) {
    isTurboMode = false;
    turboTimer = 0.0f;
}

bool TurboUtils::AddTurboPoint(uint8_t& turboPoint, uint8_t turboLimit) {
    if (turboPoint < turboLimit) {
        turboPoint += 1;
        return ShouldActivateTurbo(turboPoint, turboLimit);
    }
    return false;
}