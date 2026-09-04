#include "rotation_utils.hpp"
#include <cmath>

float RotationUtils::WrapAngle(float angle) {
    // Keep angle in range [0, 360)
    angle = fmod(angle, 360.0f);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

float RotationUtils::RotateLeft(float currentAngle, float amount) {
    currentAngle -= amount;
    return WrapAngle(currentAngle);
}

float RotationUtils::RotateRight(float currentAngle, float amount) {
    currentAngle += amount;
    return WrapAngle(currentAngle);
}

Vector2 RotationUtils::GetDirection(float angle) {
    float radians = DegToRad(angle);
    return {
        sin(radians),
        -cos(radians)  // Negative because Y is down in screen coords
    };
}

float RotationUtils::DegToRad(float degrees) {
    return degrees * (PI / 180.0f);
}

float RotationUtils::RadToDeg(float radians) {
    return radians * (180.0f / PI);
}