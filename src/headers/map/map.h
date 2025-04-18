#ifndef MAP_H
#define MAP_H

#include "../raylib/raylib.h"
#include "../main/globals.hpp"
#include "../sprite/sprite.h"
#include "../sprite/tile.h"
#include "../sprite/entity.h"
#include <string>
#include <unordered_map>
#include <vector>

class Map
{
    public:
    Map();
    ~Map();
    const static int tilesize = 32;
    const static int levelAmount = 11;
    static Texture2D normalAtlas;
    static Texture2D collisionAtlas;
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> normalTilemap[levelAmount];
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> collisionTilemap[levelAmount];
    static std::vector<Tile> normalTiles;
    static std::vector<Tile> collisionTiles;
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> LoadMap(std::string filepath);
    static Vector2 mapSize;
    static void GetMapSize(std::string filepath);
    static void GetCurrentMapSize();
    static void LoadContent();
    static void UnloadContent();
    static void CalculateTiles();
    static void Draw();
    static void DrawCollisions();
    static void AdvanceLevel();
    static void Win();
    static void LoadMapSizeAndTiles();
};

#endif