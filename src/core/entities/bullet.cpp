#include "bullet.hpp"
#include <cmath>

// Constructor
Bullet::Bullet(Vector2 spawnPos, float angle, bool turbo) {
    position = spawnPos;
    speed = 600.0f;
    radius = 5.0f;
    isActive = true;
    isTurbo = turbo;
    
    float radians = angle * (PI / 180.0f);
    velocity.x = speed * sin(radians);
    velocity.y = -speed * cos(radians);
}

void Bullet::Update(float deltaTime) {
    if (!isActive) return;
    
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    
    if (position.x < -radius || position.x > WIDTH + radius ||
        position.y < -radius || position.y > HEIGHT + radius) {
        isActive = false;
    }
}

void Bullet::Draw() {
    if (!isActive) return;
    
    if (isTurbo) {
        // TURBO BULLET - Green with glow
        DrawCircle(position.x, position.y, radius * 2.5f, { 255, 200, 0, 60 });  // Glow
        DrawCircle(position.x, position.y, radius, { 255, 200, 0, 255 });        // Solid core
        DrawCircle(position.x, position.y, radius * 0.5f, { 255, 255, 255, 255 }); // Bright center
        DrawCircleLines(position.x, position.y, radius, WHITE);                  // Border
       
    } else {
        // NORMAL BULLET - Yellow/White
         DrawCircle(position.x, position.y, radius, { 255, 255, 255, 255 });    // Outer glow

    }
}