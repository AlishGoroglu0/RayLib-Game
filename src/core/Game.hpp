#pragma once

#include "entities/player.hpp"
#include "entities/rocks.hpp"
#include "raylib.h"
#include <vector>
#include <algorithm>

class Game {
private:
    Player player;
    std::vector<Rock> rocks;
    float rockSpawnTimer;
    const float ROCK_SPAWN_INTERVAL = 3.0f;
    const float PLAYER_RADIUS = 20.0f;
    bool isRunning;

public:
    Game();
    ~Game();
    
    void Init();
    void HandleInput();
    void Update(float deltaTime);
    void Draw();
    void DrawUI();
    void Run();
    void Shutdown();
};