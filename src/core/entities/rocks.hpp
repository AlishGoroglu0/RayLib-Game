#pragma once

#include "../constants/theme.hpp"
#include "raylib.h"
#include <cmath>
#include <random>

class Rock {
private:
    Vector2 position;
    Vector2 velocity;
    float radius;
    int health;
    bool isActive;
    float spawnDelay;
    float spawnTimer;
    bool hasStartedMoving;

public:
    Rock(Vector2 playerPosition);
    ~Rock() = default;
    
    void Update(float deltaTime, Vector2 playerPosition);
    void Draw() const;
    
    // Getters
    bool IsActive() const { return isActive; }
    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
    int GetHealth() const { return health; }
    
    // Methods
    void TakeDamage(int damage = 1);
    void Deactivate();
    bool CheckCollisionWithPlayer(Vector2 playerPos, float playerRadius) const;
    bool CheckCollisionWithBullet(Vector2 bulletPos, float bulletRadius) const;
    
private:
    Vector2 GetRandomSpawnPosition();
    Vector2 CalculateDirection(Vector2 target);
    
    // Static random generator (shared across all Rock instances)
    static std::mt19937& GetRandomGenerator();
    static std::uniform_real_distribution<float>& GetRandomDistribution();
};