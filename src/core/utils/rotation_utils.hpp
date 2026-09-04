#pragma once

#include "../constants/common.hpp"

class RotationUtils {
public:
    // Wrap angle to keep it between 0-360 degrees
    static float WrapAngle(float angle);
    
    // Rotate left by given amount (wraps automatically)
    static float RotateLeft(float currentAngle, float amount);
    
    // Rotate right by given amount (wraps automatically)
    static float RotateRight(float currentAngle, float amount);
    
    // Convert rotation to direction vector
    static Vector2 GetDirection(float angle);
    
    // Convert degrees to radians
    static float DegToRad(float degrees);
    
    // Convert radians to degrees
    static float RadToDeg(float radians);
};