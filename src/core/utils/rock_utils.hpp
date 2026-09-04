#pragma once

#include "raylib.h"
#include <vector>

class RockUtils {
public:
    // Check if two rocks are overlapping
    static bool CheckRockOverlap(const Vector2& pos1, float radius1, 
                                 const Vector2& pos2, float radius2);
    
    // Calculate distance between two points
    static float CalculateDistance(const Vector2& p1, const Vector2& p2);
    
    // Generate random position within spawn boundaries
    static Vector2 GenerateRandomSpawnPosition(float radius, int buffer = 50);
    
    // Calculate direction vector from one point to another
    static Vector2 CalculateDirection(const Vector2& from, const Vector2& to);
    
    // Normalize a vector
    static Vector2 NormalizeVector(const Vector2& vec);
    
    // Get a vector's length
    static float VectorLength(const Vector2& vec);
    
    // Clamp health value between min and max
    static int ClampHealth(int health, int min = 0, int max = 5);
    
    // Get color based on health ratio
    static Color GetHealthColor(float healthRatio);
    
    // Check if rock is within screen bounds (for cleanup)
    static bool IsOffScreen(const Vector2& position, float radius, 
                            int screenWidth, int screenHeight, int buffer = 100);
    
    // Generate random rock with different sizes
    static float GetRandomRockRadius(float minRadius = 15.0f, float maxRadius = 35.0f);
    
    // Get health based on radius (larger rocks have more health)
    static int GetHealthFromRadius(float radius, float baseHealth = 5.0f, float baseRadius = 25.0f);
    
    // Calculate knockback direction
    static Vector2 CalculateKnockback(const Vector2& rockPos, const Vector2& impactPos, float strength = 1.0f);
};

// Helper struct for rock spawn configuration
struct RockSpawnConfig {
    int minHealth = 3;
    int maxHealth = 7;
    float minRadius = 15.0f;
    float maxRadius = 35.0f;
    float speed = 120.0f;
    float spawnDelay = 0.5f;
};