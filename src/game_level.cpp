#include "game_level.h"

#include <fstream>
#include <sstream>

void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight)
{
    this->Bricks.clear();

    unsigned int tileCode;
    GameLevel level;

    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;

    if(fstream)
    {
        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode)
                row.push_back(tileCode); // each word seperated by space
            tileData.push_back(row);
        }

        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
    for (GameObject &tile : this->Bricks)
    if (!tile.Destroyed)
        tile.Draw(renderer);
}

bool GameLevel::IsComplete()
{
    for (GameObject &tile : this->Bricks)
    if (!tile.IsSolid && !tile.Destroyed)
        return false;
    return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight){
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();
    float unit_width = levelWidth / static_cast<float>(width);
    float unit_height = levelHeight / static_cast<float>(height);
    Texture2D blockTexture;

    for (unsigned int y = 0; y < height; y++)
    {
        for (unsigned int x = 0; x < width; x++)
        {
            if (tileData[y][x] == 1) // solid block
            { 
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                Texture2D solidTexture = ResourceManager::GetTexture("bedrock");
                GameObject obj(pos, size, solidTexture, glm::vec3(0.8f, 0.8f, 0.7f));
                obj.IsSolid = true;
                this->Bricks.push_back(obj);
            }

            else if (tileData[y][x] > 1) // non solid
            {
                glm::vec3 color = glm::vec3(1.0f);
                if      (tileData[y][x] == 2) blockTexture = ResourceManager::GetTexture("stone");
                else if (tileData[y][x] == 3) blockTexture = ResourceManager::GetTexture("iron");
                else if (tileData[y][x] == 4) blockTexture = ResourceManager::GetTexture("emerald");
                else if (tileData[y][x] == 5) blockTexture = ResourceManager::GetTexture("diamond");
                else blockTexture = ResourceManager::GetTexture("cobble");

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);

                
                this->Bricks.push_back(GameObject(pos, size, blockTexture, color));
            }
        }
    }
}
