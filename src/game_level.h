#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>

#include <GLAD/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

class GameLevel{
public:
    std::vector<GameObject> Bricks;
    GameLevel(){}

    void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
    void Draw(SpriteRenderer &renderer);

    bool IsComplete();

private:
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif