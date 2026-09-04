#pragma once

#include "../constants/common.hpp"

class MathUtils {
public:
    // Clamp value between min and max (template - inline in header)
    template<typename T>
    static T Clamp(T value, T min, T max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
    
    // Linear interpolation
    static float Lerp(float a, float b, float t);
    
    // Distance between two points
    static float Distance(Vector2 a, Vector2 b);
    
    // Distance squared (faster, no sqrt)
    static float DistanceSquared(Vector2 a, Vector2 b);
    
    // Check if point is within radius of another point
    static bool IsWithinRadius(Vector2 point, Vector2 center, float radius);
    
    // Check if value is between min and max (inclusive)
    static bool IsBetween(float value, float min, float max);
    
    // Convert float to int with rounding
    static int RoundToInt(float value);
    
    // Random float between min and max
    static float RandomFloat(float min, float max);
    
    // Random int between min and max (inclusive)
    static int RandomInt(int min, int max);
};