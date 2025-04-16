#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include "globals.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Map
{
    public:
    Map();
    ~Map();
    static Texture2D atlas;
    const static int tilesize = 32;
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> tilemap[1];
    static std::vector<Vector3> normalTiles;
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> LoadMap(std::string filepath);
    static void LoadContent();
    static void UnloadContent();
    static void Draw(int currentLevel);
};

#endif