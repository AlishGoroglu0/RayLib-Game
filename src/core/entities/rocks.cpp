#include "rocks.hpp"
#include "../utils/rock_utils.hpp"  // Added this include
#include "raylib.h"
#include "../constants/theme.hpp"
#include <random>
#include <cmath>

// Static random generator implementation - These are the class static methods
std::mt19937& Rock::GetRandomGenerator() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

std::uniform_real_distribution<float>& Rock::GetRandomDistribution() {
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis;
}

Rock::Rock(Vector2 playerPosition) 
    : radius(RockUtils::GetRandomRockRadius(15.0f, 35.0f)),  // Use RockUtils
      health(RockUtils::GetHealthFromRadius(radius)),        // Use RockUtils
      isActive(true),
      spawnDelay(0.5f),
      spawnTimer(0.0f),
      hasStartedMoving(false) {
    
    position = RockUtils::GenerateRandomSpawnPosition(radius);  // Use RockUtils
    velocity = RockUtils::CalculateDirection(position, playerPosition);  // Use RockUtils
}

void Rock::Update(float deltaTime, Vector2 playerPosition) {
    if (!isActive) return;
    
    // Handle spawn delay
    if (!hasStartedMoving) {
        spawnTimer += deltaTime;
        if (spawnTimer >= spawnDelay) {
            hasStartedMoving = true;
            // Recalculate direction in case player moved
            velocity = RockUtils::CalculateDirection(position, playerPosition);  // Use RockUtils
        }
        return;
    }
    
    // Move toward player
    float speed = 120.0f; // Pixels per second
    position.x += velocity.x * speed * deltaTime;
    position.y += velocity.y * speed * deltaTime;
}

void Rock::Draw() const {
    if (!isActive) return;
    
    // Draw the rock as a circle with a rough texture look
    DrawCircleV(position, radius, DARKGRAY);
    DrawCircleLines(position.x, position.y, radius, LIGHTGRAY);
    
    // Draw some "cracks" for visual effect
    DrawLine(position.x - radius * 0.5f, position.y - radius * 0.3f,
             position.x + radius * 0.3f, position.y + radius * 0.4f, GRAY);
    DrawLine(position.x + radius * 0.2f, position.y - radius * 0.5f,
             position.x - radius * 0.4f, position.y + radius * 0.2f, GRAY);
    
    // Draw health indicator (small colored circle inside)
    float healthRatio = static_cast<float>(health) / 5.0f;
    Color healthColor = RockUtils::GetHealthColor(healthRatio);  // Use RockUtils
    DrawCircle(position.x, position.y, radius * 0.3f, healthColor);
    
    // Draw health bar above rock
    if (health > 0 && health < 5) {
        float barWidth = radius * 1.5f;
        float barHeight = 4.0f;
        float barX = position.x - barWidth / 2.0f;
        float barY = position.y - radius - 10.0f;
        
        // Background
        DrawRectangle(barX, barY, barWidth, barHeight, DARKGRAY);
        // Health
        float healthWidth = (barWidth * health) / 5.0f;
        Color healthColor2 = health > 3 ? GREEN : (health > 1 ? YELLOW : RED);
        DrawRectangle(barX, barY, healthWidth, barHeight, healthColor2);
    }
}

void Rock::TakeDamage(int damage) {
    if (!isActive) return;
    health -= damage;
    health = RockUtils::ClampHealth(health);  // Use RockUtils
    if (health <= 0) {
        isActive = false;
    }
}

void Rock::Deactivate() {
    isActive = false;
}

bool Rock::CheckCollisionWithPlayer(Vector2 playerPos, float playerRadius) const {
    if (!isActive) return false;
    return RockUtils::CheckRockOverlap(position, radius, playerPos, playerRadius);  // Use RockUtils
}

bool Rock::CheckCollisionWithBullet(Vector2 bulletPos, float bulletRadius) const {
    if (!isActive) return false;
    return RockUtils::CheckRockOverlap(position, radius, bulletPos, bulletRadius);  // Use RockUtils
}

Vector2 Rock::GetRandomSpawnPosition() {
    // This method is now deprecated - use RockUtils::GenerateRandomSpawnPosition instead
    // Keeping for backward compatibility if needed
    return RockUtils::GenerateRandomSpawnPosition(radius);
}

Vector2 Rock::CalculateDirection(Vector2 target) {
    // This method is now deprecated - use RockUtils::CalculateDirection instead
    // Keeping for backward compatibility if needed
    return RockUtils::CalculateDirection(position, target);
}