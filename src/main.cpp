#include "core/Game.hpp"

int main() {
    // Initialize window
    InitWindow(WIDTH, HEIGHT, "My Game");
    SetTargetFPS(60);
    
    // Create and run game
    Game game;
    game.Run();
    
    // Cleanup
    CloseWindow();
    return 0;
}