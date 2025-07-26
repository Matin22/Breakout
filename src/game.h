#ifndef GAME_H
#define GAME_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "sprite_renderer.h"

#include "game_level.h"

const glm::vec2 PLAYER_SIZE(125.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 15.0f;

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    GameState               State;
    bool                    Keys[1024];
    unsigned int            Width, Height;
    std::vector<GameLevel>  Levels;
    unsigned int            Level;

    Game(unsigned int Width, unsigned int Height);
    ~Game();

    void Init();

    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
private:
    SpriteRenderer *Renderer;
};

#endif