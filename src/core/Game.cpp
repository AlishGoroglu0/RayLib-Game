#include "Game.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

// Constructor
Game::Game() {
    Init();
}

// Destructor
Game::~Game() {
    Shutdown();
}

// Initialize game
void Game::Init() {
    isRunning = true;
    rockSpawnTimer = 0.0f;
    // Player is constructed automatically
}

// Handle input
void Game::HandleInput() {
    // SPACE to fire
    if (IsKeyPressed(KEY_SPACE)) {
        player.Fire();
    }
    
    // H for damage testing
    if (IsKeyPressed(KEY_H)) {
        player.GetDamage();
    }
    
    // T to toggle turbo (debug)
    if (IsKeyPressed(KEY_T)) {
        if (player.IsTurboMode()) {
            player.DeactivateTurbo();
        } else {
            player.ActivateTurbo();
        }
    }
    
    // P to add turbo points (debug)
    if (IsKeyPressed(KEY_P)) {
        player.AddTurboPoint();
    }
}

// Update game logic
void Game::Update(float deltaTime) {
    // Update player (handles rotation, bullets, turbo timer)
    player.Update(deltaTime);
    
    // ========== ROCK SYSTEM ==========
    
    // 1. Spawn rocks
    rockSpawnTimer += deltaTime;
    if (rockSpawnTimer >= ROCK_SPAWN_INTERVAL) {
        rocks.emplace_back(player.GetPosition());
        rockSpawnTimer = 0.0f;
    }
    
    // 2. Update all rocks
    for (auto& rock : rocks) {
        rock.Update(deltaTime, player.GetPosition());
    }
    
    // 3. Check rock vs bullet collisions
    for (auto& rock : rocks) {
        if (!rock.IsActive()) continue;
        
        // Get mutable reference to bullets
        auto& bullets = player.GetBulletsMutable();
        
        for (auto& bullet : bullets) {
            if (!bullet.IsActive()) continue;
            
            // Check collision between rock and bullet
            float distance = Vector2Distance(rock.GetPosition(), bullet.GetPosition());
            float collisionDistance = rock.GetRadius() + bullet.GetRadius();
            
            if (distance < collisionDistance) {
                // Turbo bullets deal 2 damage, normal bullets deal 1
                int damage = bullet.IsTurbo() ? 2 : 1;
                rock.TakeDamage(damage);
                bullet.Deactivate();
                
                // If rock is still alive after damage, reward player
                if (rock.IsActive()) {
                    player.AddTurboPoint();
                }
                
                break;  // Rock hit, stop checking bullets for this rock
            }
        }
    }
    
    // 4. Check rock vs player collisions
    for (auto& rock : rocks) {
        if (!rock.IsActive()) continue;
        
        float distance = Vector2Distance(player.GetPosition(), rock.GetPosition());
        float collisionDistance = PLAYER_RADIUS + rock.GetRadius();
        
        if (distance < collisionDistance) {
            player.GetDamage();   // Player loses 1 health
            rock.Deactivate();    // Rock disappears on impact
        }
    }
    
    // 5. Clean up inactive rocks (memory safety)
    rocks.erase(std::remove_if(rocks.begin(), rocks.end(),
        [](const Rock& rock) { return !rock.IsActive(); }),
        rocks.end());
    
    // ========== END ROCK SYSTEM ==========
}

// Draw everything
void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    
    // Draw player and bullets
    player.Draw();
    
    // Draw rocks
    for (const auto& rock : rocks) {
        rock.Draw();
    }
    
    // Draw UI
    DrawUI();
    
    EndDrawing();
}

// Draw UI overlay
void Game::DrawUI() {
    // Controls
    DrawText("CONTROLS:", 10, 10, 20, WHITE);
    DrawText("A/D - Rotate", 10, 40, 20, WHITE);
    DrawText("SPACE - Fire", 10, 70, 20, WHITE);
    DrawText("H - Take Damage", 10, 100, 20, WHITE);
    DrawText("T - Toggle Turbo (Debug)", 10, 130, 20, WHITE);
    DrawText("P - Add Turbo Points (Debug)", 10, 160, 20, WHITE);
    
    // Player stats
    DrawText(TextFormat("Health: %d", player.GetHealth()), 10, 200, 20, WHITE);
    DrawText(TextFormat("Turbo Mode: %s", player.IsTurboMode() ? "ON" : "OFF"), 10, 230, 20, WHITE);
    
    // Show turbo timer if active, otherwise show points
    if (player.IsTurboMode()) {
        DrawText(TextFormat("Turbo Time: %.1f/5.0s", player.GetTurboTimer()), 10, 260, 20, GREEN);
    } else {
        DrawText(TextFormat("Turbo Points: %d/25", player.GetTurboPoints()), 10, 260, 20, WHITE);
    }
    
    DrawText(TextFormat("Rotation: %.0f deg", player.GetRotation()), 10, 290, 20, WHITE);
    DrawText(TextFormat("Bullets: %zu", player.GetBullets().size()), 10, 320, 20, WHITE);
    
    // Rock counter
    DrawText(TextFormat("Rocks: %zu", rocks.size()), 10, 350, 20, RED);
}

// One frame of the game — shared by native and web loops
void Game::Step() {
    float deltaTime = GetFrameTime();
    
    HandleInput();
    Update(deltaTime);
    Draw();
}

#ifdef __EMSCRIPTEN__
// Emscripten needs a plain function pointer, so route through a static pointer
static Game* g_game = nullptr;

static void WebFrame() {
    if (g_game) g_game->Step();
}
#endif

// Main game loop
void Game::Run() {
#ifdef __EMSCRIPTEN__
    g_game = this;
    emscripten_set_main_loop(WebFrame, 0, 1);   // 0 fps = match display refresh rate
#else
    while (!WindowShouldClose() && isRunning) {
        Step();
    }
#endif
}

// Shutdown
void Game::Shutdown() {
    // Cleanup if needed
    isRunning = false;
}