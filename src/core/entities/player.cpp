#include "player.hpp"
#include "bullet.hpp"  // ← ADD THIS explicit include
#include "../constants/theme.hpp"
#include "../utils/turbo_utils.hpp"
#include "../utils/rotation_utils.hpp"
#include "../utils/math_utils.hpp"
#include <algorithm>

// Constructor implementation
Player::Player() {
    position = { WIDTH / 2.0f, HEIGHT / 2.0f };
    rotation = 0.0f;
    size = 15.0f;
    fireTimer = 0.0f;
    turboTimer = 0.0f;
}

// Debug methods
void Player::ActivateTurbo() {
    TurboUtils::ActivateTurbo(isTurboMode, turboTimer, turboDuration, turboPoint);
}

void Player::DeactivateTurbo() {
    TurboUtils::DeactivateTurbo(isTurboMode, turboTimer);
}

void Player::AddTurboPoint() {
    if (TurboUtils::AddTurboPoint(turboPoint, turboLimit)) {
        TurboUtils::ActivateTurbo(isTurboMode, turboTimer, turboDuration, turboPoint);
    }
}

// Fire implementation
void Player::Fire() {
    if (fireTimer <= 0.0f) {
        bullets.emplace_back(position, rotation , isTurboMode);
        fireTimer = TurboUtils::ApplyFireRateBonus(fireTimer, fireCooldown, isTurboMode);
    }
}

// GetDamage implementation - USING MATHUTILS
void Player::GetDamage() {
    health--;
    health = MathUtils::Clamp<uint8_t>(health, 0, 5);  // Keep health between 0-5
    
    if (isTurboMode) {
        TurboUtils::DeactivateTurbo(isTurboMode, turboTimer);
    }
    
    if (health <= 0) {
        position = { WIDTH / 2.0f, HEIGHT / 2.0f };
        rotation = 0.0f;
    }
}

// Update implementation
void Player::Update(float deltaTime) {
    const float rotationAmount = 350.0f;
    
    // Rotation movement
    if (IsKeyDown(KEY_A)) {
        rotation = RotationUtils::RotateLeft(rotation, rotationAmount);
    }
    
    if (IsKeyDown(KEY_D)) {
        rotation = RotationUtils::RotateRight(rotation, rotationAmount);
    }
    
    // Handle SPACE key for firing
    if (IsKeyDown(KEY_SPACE)) {
        Fire();
    }
    
    // Check if turbo should activate
    if (TurboUtils::ShouldActivateTurbo(turboPoint, turboLimit)) {
        TurboUtils::ActivateTurbo(isTurboMode, turboTimer, turboDuration, turboPoint);
    }
    
    // Update turbo timer
    if (isTurboMode) {
        TurboUtils::UpdateTurboTimer(isTurboMode, turboTimer, deltaTime);
    }
    
    // Update fire timer
    if (fireTimer > 0.0f) {
        fireTimer -= deltaTime;
        if (fireTimer < 0.0f) fireTimer = 0.0f;
    }
    
    // Update bullets
    for (auto& bullet : bullets) {
        bullet.Update(deltaTime);
    }
    
    // Remove inactive bullets
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const Bullet& bullet) { return !bullet.IsActive(); }),
        bullets.end()
    );
}

void Player::Draw() {
    Color playerColor;
    if (isTurboMode) {
        playerColor = RED;
    } else {
        playerColor = RAYWHITE;
    }
    
    Vector2 direction = RotationUtils::GetDirection(rotation);
    Vector2 leftDir = RotationUtils::GetDirection(rotation + 120.0f);
    Vector2 rightDir = RotationUtils::GetDirection(rotation - 120.0f);
    
    Vector2 p1 = {
        position.x + size * direction.x,
        position.y + size * direction.y
    };
    
    Vector2 p2 = {
        position.x + size * leftDir.x,
        position.y + size * leftDir.y
    };
    
    Vector2 p3 = {
        position.x + size * rightDir.x,
        position.y + size * rightDir.y
    };
    
    // FIX: Use playerColor and try reversing order
    // Option 1: Reverse order (p3, p2, p1 instead of p1, p2, p3)
    DrawTriangle(p3, p2, p1, playerColor);  // ← Reversed order!
    DrawTriangleLines(p3, p2, p1, WHITE);
    
    // Or Option 2: Try (p2, p1, p3)
    // DrawTriangle(p2, p1, p3, playerColor);
    // DrawTriangleLines(p2, p1, p3, WHITE);
    
    if (isTurboMode) {
        DrawCircle(position.x, position.y, size + 10, {0 , 0 , 255 , 20});
    }
    
    for (auto& bullet : bullets) {
        bullet.Draw();
    }
    
    DrawText(TextFormat("Rotation: %.0f°", rotation), 10, 130, 20, WHITE);
}