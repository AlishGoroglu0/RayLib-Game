#include "math_utils.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Clamp is now in the header file (template)

float MathUtils::Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

float MathUtils::Distance(Vector2 a, Vector2 b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

float MathUtils::DistanceSquared(Vector2 a, Vector2 b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return dx * dx + dy * dy;
}

bool MathUtils::IsWithinRadius(Vector2 point, Vector2 center, float radius) {
    return DistanceSquared(point, center) <= radius * radius;
}

bool MathUtils::IsBetween(float value, float min, float max) {
    return value >= min && value <= max;
}

int MathUtils::RoundToInt(float value) {
    return static_cast<int>(round(value));
}

float MathUtils::RandomFloat(float min, float max) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }
    float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    return min + random * (max - min);
}

int MathUtils::RandomInt(int min, int max) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }
    return min + (rand() % (max - min + 1));
}