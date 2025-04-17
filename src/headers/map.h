#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include "globals.hpp"
#include "sprite.h"
#include <string>
#include <unordered_map>
#include <vector>

class Map
{
    public:
    Map();
    ~Map();
    const static int tilesize = 32;
    const static int levelAmount = 1;
    static Texture2D normalAtlas;
    static Texture2D collisionAtlas;
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> normalTilemap[levelAmount];
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> collisionTilemap[levelAmount];
    static std::vector<Sprite> normalTiles;
    static std::vector<Sprite> collisionTiles;
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> LoadMap(std::string filepath);
    static Vector2 mapSize;
    static void GetMapSize(std::string filepath);
    static void GetCurrentMapSize(int currentLevel);
    static void LoadContent();
    static void UnloadContent();
    static void Draw(int currentLevel);
    static void DrawCollisions(int currentLevel);
    static void CheckCollisionsX(Sprite *sprite, std::vector<Sprite> &collisionTiles);
    static void CheckCollisionsY(Sprite *sprite, std::vector<Sprite> &collisionTiles);
};

#endif