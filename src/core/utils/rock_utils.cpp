#include "rock_utils.hpp"
#include "../constants/theme.hpp"
#include <random>
#include <cmath>

bool RockUtils::CheckRockOverlap(const Vector2& pos1, float radius1, 
                                 const Vector2& pos2, float radius2) {
    float distance = CalculateDistance(pos1, pos2);
    return distance < (radius1 + radius2);
}

float RockUtils::CalculateDistance(const Vector2& p1, const Vector2& p2) {
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    return sqrtf(dx * dx + dy * dy);
}

Vector2 RockUtils::GenerateRandomSpawnPosition(float radius, int buffer) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    static std::uniform_int_distribution<int> edgeDis(0, 3);
    
    int edge = edgeDis(gen);
    float x, y;
    
    switch (edge) {
        case 0: // Top
            x = dis(gen) * WIDTH;
            y = -buffer - radius;
            break;
        case 1: // Right
            x = WIDTH + buffer + radius;
            y = dis(gen) * HEIGHT;
            break;
        case 2: // Bottom
            x = dis(gen) * WIDTH;
            y = HEIGHT + buffer + radius;
            break;
        case 3: // Left
            x = -buffer - radius;
            y = dis(gen) * HEIGHT;
            break;
        default:
            x = 0;
            y = 0;
            break;
    }
    
    return {x, y};
}

Vector2 RockUtils::CalculateDirection(const Vector2& from, const Vector2& to) {
    Vector2 direction;
    direction.x = to.x - from.x;
    direction.y = to.y - from.y;
    return NormalizeVector(direction);
}

Vector2 RockUtils::NormalizeVector(const Vector2& vec) {
    float length = VectorLength(vec);
    if (length > 0) {
        return {vec.x / length, vec.y / length};
    }
    return {0.0f, 0.0f};
}

float RockUtils::VectorLength(const Vector2& vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

int RockUtils::ClampHealth(int health, int min, int max) {
    if (health < min) return min;
    if (health > max) return max;
    return health;
}

Color RockUtils::GetHealthColor(float healthRatio) {
    if (healthRatio > 0.6f) return GREEN;
    if (healthRatio > 0.3f) return YELLOW;
    return RED;
}

bool RockUtils::IsOffScreen(const Vector2& position, float radius, 
                            int screenWidth, int screenHeight, int buffer) {
    return (position.x < -buffer - radius || 
            position.x > screenWidth + buffer + radius ||
            position.y < -buffer - radius || 
            position.y > screenHeight + buffer + radius);
}

float RockUtils::GetRandomRockRadius(float minRadius, float maxRadius) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(minRadius, maxRadius);
    return dis(gen);
}

int RockUtils::GetHealthFromRadius(float radius, float baseHealth, float baseRadius) {
    // Larger rocks have proportionally more health
    float ratio = radius / baseRadius;
    return static_cast<int>(baseHealth * ratio + 0.5f);
}

Vector2 RockUtils::CalculateKnockback(const Vector2& rockPos, const Vector2& impactPos, float strength) {
    Vector2 knockback = CalculateDirection(impactPos, rockPos);
    knockback.x *= strength;
    knockback.y *= strength;
    return knockback;
}