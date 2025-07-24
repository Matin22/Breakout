#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

SpriteRenderer *Renderer;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    ResourceManager::LoadShader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    Shader tempShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(tempShader);


    ResourceManager::LoadTexture("res/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("res/textures/stone.png", false, "stone");
    ResourceManager::LoadTexture("res/textures/bedrock.png", false, "bedrock");
    ResourceManager::LoadTexture("res/textures/cobble.png", false, "cobble");
    ResourceManager::LoadTexture("res/textures/diamond.png", false, "diamond");
    ResourceManager::LoadTexture("res/textures/iron.png", false, "iron");
    ResourceManager::LoadTexture("res/textures/emerald.png", false, "emerald");

    GameLevel one;
    one.Load("res/levels/one.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);

    this->Level = 0;
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        Texture2D backgroundTexture = ResourceManager::GetTexture("background");
        Renderer->DrawSprite(backgroundTexture, glm::vec2(0.0f, 0.0f),
                             glm::vec2(this->Width, this->Height), 0.0f);

        this->Levels[this->Level].Draw(*Renderer);
    }
}
