#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "ball_object.h"

SpriteRenderer  *Renderer;
GameObject      *Player;
BallObject *Ball;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
    delete Renderer;
    delete Player;
    delete Ball;
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
    ResourceManager::LoadTexture("res/textures/paddle.png", true, "paddle");
    ResourceManager::LoadTexture("res/textures/slimeball.png", true, "ball");

    GameLevel one;
    one.Load("res/levels/one.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    
    GameLevel two;
    two.Load("res/levels/two.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(two);
     
    GameLevel three;
    three.Load("res/levels/three.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(three);
    
    GameLevel four;
    four.Load("res/levels/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(four);

    this->Level = 0;

    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ball"));
}

void Game::ProcessInput(float dt)
{
    if(this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;

        if (this->Keys[GLFW_KEY_LEFT])
        {
            if(Player->Position.x >= 0.0f)
            {
                Player->Position.x -= velocity;
                if (Ball->Stuck) Ball->Position.x -= velocity;
            }
        }
        
        if (this->Keys[GLFW_KEY_RIGHT])
        {
            if(Player->Position.x <= this->Width - Player->Size.x)
            {
                Player->Position.x += velocity;
                if (Ball->Stuck) Ball->Position.x += velocity;
            }
        }

        if (this->Keys[GLFW_KEY_SPACE])
            Ball->Stuck = false;
    }
}

void Game::Update(float dt)
{
    Ball->Move(dt, this->Width);
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        Texture2D backgroundTexture = ResourceManager::GetTexture("background");
        Renderer->DrawSprite(backgroundTexture, glm::vec2(0.0f, 0.0f),
                             glm::vec2(this->Width, this->Height), 0.0f);

        this->Levels[this->Level].Draw(*Renderer);
        Player->Draw(*Renderer);
        Ball->Draw(*Renderer);
    }
}
