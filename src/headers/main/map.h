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
    static void MoveTo(int level, Player *player);
    static void AdvanceLevel(Player *player);
    static void Win(Player *player);
    static void LoadMapSizeAndTiles();
    static void Eval(Player *player);
    enum NormalTileType {GRASS = 0, DIRT, STONE, LEAVES, SAND, 
        PLANKS, ICE, METAL, SPIKE_DOWN = 16, SPIKE_RIGHT, SPIKE_UP, SPIKE_LEFT, 
        LAVA_BLOCK, LAVA_TOP, WATER_BLOCK = 24, WATER_TOP, SPEED_CRYSTAL, PASS_BLOCK, WIN_BLOCK,
        BREAKABLE_BLOCK, DASH_BLOCK, DOUBLE_JUMP_CRYSTAL, MILK_CARTON, XARTOMANTILA};
    
    enum CollisionTileType {SOLID = 0, HAZARD, PASS, WIN, WATER, 
        CRYSTAL, BREAKABLE, DASH, DOUBLE_JUMP, HEALTH, COLLECTIBLE, 
        SPIKE_REC_DOWN, SPIKE_REC_LEFT, SPIKE_REC_UP, SPIKE_REC_RIGHT, 
        SPAWN_PLAYER = 16, SPAWN_TRIANGLE, SPAWN_BOSS, SPAWN_CIRCLE};
};

#endif