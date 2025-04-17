#include "../headers/map.h"
#include "../headers/raylib.h"
#include "../headers/globals.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Map::Map() {}
Map::~Map() {}

Texture2D Map::normalAtlas;
Texture2D Map::collisionAtlas;

std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> Map::normalTilemap[levelAmount];
std::vector<Sprite> Map::normalTiles;

std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> Map::collisionTilemap[levelAmount];
std::vector<Sprite> Map::collisionTiles;

Vector2 Map::mapSize;

std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> Map::LoadMap(std::string filepath)
{
    std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> result;
    std::fstream file;
    
    int y = 0;
    std::string line;
    
    file.open(filepath, std::ios::in);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (!line.empty())
            {
                int count = 0;
                char** items = TextSplit(line.c_str(), ',', &count);
                
                for (int x = 0; x < count; x++)
                {
                    int value = std::stoi(items[x]);
                    if (value >= 0)
                    {
                        result[{(float)x, (float)y}] = value;
                    }
                }
                
                y++;
            }
        }
        
        file.close();
    }
    else
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
    }
    
    return result;
}

void Map::GetMapSize(std::string filepath)
{
    std::fstream file;
    int y = 0;
    int x = 0;
    std::string line;

    file.open(filepath, std::ios::in);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (!line.empty())
            {
                int count = 0;
                char** items = TextSplit(line.c_str(), ',', &count);

                if (y == 0) x = count;

                y++;
            }
        }

        file.close();
    }
    else
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
    }

    mapSize = { (float)(x * tilesize), (float)(y * tilesize) };
}

void Map::GetCurrentMapSize(int currentLevel)
{
    GetMapSize("res/data/level" + std::to_string(currentLevel) + "_collision.csv");
}

void Map::LoadContent()
{
    normalAtlas = LoadTexture("res/assets/map/normal_atlas.png");
    collisionAtlas = LoadTexture("res/assets/map/collision_atlas.png");
    
    for(int i = 0; i < levelAmount; i++)
    {
        normalTilemap[i] = LoadMap("res/data/level" + std::to_string(i) + "_normal.csv");
        collisionTilemap[i] = LoadMap("res/data/level" + std::to_string(i) + "_collision.csv");
    }
}

void Map::UnloadContent()
{
    UnloadTexture(normalAtlas);
    UnloadTexture(collisionAtlas);
}

void Map::Draw(int currentLevel)
{
    normalTiles.clear();

    int tpr = 8; //Tiles per row
    int p_tilesize = 32; //Pixel Tilesize
    
    for(std::pair<Vector2, int> item : normalTilemap[currentLevel])
    {
        Rectangle dest = {
            item.first.x * tilesize,
            item.first.y * tilesize,
            tilesize,
            tilesize
        };
        
        int x = item.second % tpr;
        int y = item.second / tpr;
        
        Rectangle src = {
            (float) x * p_tilesize,
            (float) y * p_tilesize,
            (float) p_tilesize,
            (float) p_tilesize
        };
        
        normalTiles.push_back({dest, normalAtlas}); //TEXTURE WON'T BE NEEDED HERE, JUST TEMPORARY
        
        DrawTexturePro(normalAtlas, src, dest, {0, 0}, 0.0f, WHITE);
    }
}

void Map::DrawCollisions(int currentLevel)
{
    collisionTiles.clear();
    
    int tpr = 8; //Tiles per row
    int p_tilesize = 32; //Pixel Tilesize
    
    for(std::pair<Vector2, int> item : collisionTilemap[currentLevel])
    { 
        Rectangle dest = {
            item.first.x * tilesize,
            item.first.y * tilesize,
            tilesize,
            tilesize
        };
        
        int x = item.second % tpr;
        int y = item.second / tpr;
        
        Rectangle src = {
            (float) x * p_tilesize,
            (float) y * p_tilesize,
            (float) p_tilesize,
            (float) p_tilesize
        };
        
        collisionTiles.push_back({dest, collisionAtlas});
        
        DrawTexturePro(collisionAtlas, src, dest, {0, 0}, 0.0f, WHITE);
    }
}

void Map::CheckCollisionsX(Sprite *sprite, std::vector<Sprite> &collisionTiles)
{
    sprite->isCollidingX = false;
    
    for(Sprite tile : collisionTiles)
    {
        if(CheckCollisionRecs(sprite->GetDest(), tile.GetDest()))
        {
            sprite->isCollidingX = true;
            if(sprite->GetDest().x > tile.GetDest().x)
            {
                sprite->SetPosX(tile.GetDest().x + tile.GetDest().width);
            } else {
                sprite->SetPosX(tile.GetDest().x - sprite->GetDest().width);
            }
        }
    }
}

void Map::CheckCollisionsY(Sprite *sprite, std::vector<Sprite> &collisionTiles)
{
    sprite->isCollidingY = false;
    
    for(Sprite tile : collisionTiles)
    {
        if(CheckCollisionRecs(sprite->GetDest(), tile.GetDest()))
        {
            sprite->isCollidingY = true;
            if(sprite->GetDest().y > tile.GetDest().y)
            {
                sprite->SetPosY(tile.GetDest().y + tile.GetDest().height);
            } else {
                sprite->SetPosY(tile.GetDest().y - sprite->GetDest().height);
            }
        }
    }
}
