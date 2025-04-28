#ifndef MAP_H
#define MAP_H

#include "../raylib/raylib.h"
#include "../main/globals.hpp"
#include "../sprite/sprite.h"
#include "../sprite/tile.h"
#include "../sprite/entity.h"
#include "../sprite/player.h"
#include <string>
#include <unordered_map>
#include <vector>

class Map
{
    public:
    Map();
    ~Map();
    const static int tilesize = 32;
    const static int levelAmount = 3;
    static Texture2D normalAtlas;
    static Texture2D collisionAtlas;
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> normalTilemap[levelAmount];
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> collisionTilemap[levelAmount];
    static std::vector<Tile> normalTiles;
    static std::vector<Tile> collisionTiles;
    static std::vector<Rectangle> spikes;
    static std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> LoadMap(std::string filepath);
    static Vector2 mapSize;
    static void GetMapSize(std::string filepath);
    static void GetCurrentMapSize();
    static void LoadContent();
    static void UnloadContent();
    static void CalculateTiles();
    static void Draw();
    static void DrawCollisions();
    static void MoveTo(int level, Player *player);
    static void AdvanceLevel(Player *player);
    static void Win(Player *player);
    static void LoadMapSizeAndTiles();
    static void Eval(Player *player);
    enum CollisionTileType {SOLID = 0, HAZARD, PASS, WIN, WATER, DOUBLE_JUMP, 
        SPIKE_DOWN = 8, SPIKE_LEFT, SPIKE_UP, SPIKE_RIGHT, SPAWN_PLAYER = 16};
    static Vector2 currentSpawnPoint;
};

#endif