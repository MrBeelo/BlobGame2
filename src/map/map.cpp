#include "../headers/map.h"
#include "../headers/raylib.h"
#include "../headers/globals.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Texture2D Map::atlas;

Map::Map() {}
Map::~Map() {}

std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> Map::tilemap[1];
std::vector<Vector3> Map::normalTiles;

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
                
                //delete[] items;
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

void Map::LoadContent()
{
    atlas = LoadTexture("res/assets/map/atlas.png");
    
    for(int i = 0; i < 1; i++)
    {
        tilemap[i] = LoadMap("res/data/level" + std::to_string(i) + "_normal.csv");
    }
}

void Map::UnloadContent()
{
    UnloadTexture(atlas);
}

void Map::Draw(int currentLevel)
{
    int tpr = 8; //Tiles per row
    int p_tilesize = 32; //Pixel Tilesize
    
    for(std::pair<Vector2, int> item : tilemap[currentLevel])
    {
        normalTiles.push_back({(float) item.second, item.first.x, item.first.y});
        
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
        
        DrawTexturePro(atlas, src, dest, {0, 0}, 0.0f, WHITE);
    }
}
