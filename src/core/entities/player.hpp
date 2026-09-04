#pragma once

#include "../constants/common.hpp"
#include "../constants/theme.hpp"
#include "bullet.hpp"
#include "../utils/turbo_utils.hpp"
#include <vector>

class Player {
private:
    uint8_t health = 5;
    uint8_t turboLimit = 25;
    uint8_t turboPoint = 0;
    bool isTurboMode = false;
    float turboTimer = 0.0f;
    float turboDuration = 5.0f;
    
    Vector2 position;
    float rotation;
    float size;

    std::vector<Bullet> bullets;
    float fireCooldown = 0.2f;
    float fireTimer = 0.0f;

public:
    Player();
    ~Player() = default;
    
    void Fire();
    void GetDamage();
    void Update(float deltaTime);
    void Draw();
    
    void ActivateTurbo();
    void DeactivateTurbo();
    void AddTurboPoint();
    
    // Getters
    uint8_t GetHealth() const { return health; }
    bool IsTurboMode() const { return isTurboMode; }
    uint8_t GetTurboPoints() const { return turboPoint; }
    float GetRotation() const { return rotation; }
    float GetTurboTimer() const { return turboTimer; }
    const std::vector<Bullet>& GetBullets() const { return bullets; }
    
    // NEW: Getters for collision detection
    Vector2 GetPosition() const { return position; }
    float GetSize() const { return size; }
    
    // NEW: Mutable bullets access for modifying bullets
    std::vector<Bullet>& GetBulletsMutable() { return bullets; }
};