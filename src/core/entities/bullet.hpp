#pragma once

#include "../constants/theme.hpp"
#include "raylib.h"

class Bullet {
private:
    Vector2 position;
    Vector2 velocity;
    float speed;
    float radius;
    bool isActive;
    bool isTurbo;

public:
    Bullet(Vector2 spawnPos, float angle, bool turbo = false);
    ~Bullet() = default;
    
    void Update(float deltaTime);
    void Draw();

    // Getters
    bool IsActive() const { return isActive; }
    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
    bool IsTurbo() const { return isTurbo; }
    
    // Deactivate method
    void Deactivate() { isActive = false; }
};