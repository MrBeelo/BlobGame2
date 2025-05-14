#include "../headers/main/map.h"
#include "../headers/raylib/raylib.h"
#include "../headers/main/globals.hpp"
#include "../headers/sprite/tile.h"
#include "../headers/main/savefile.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Map::Map() {}
Map::~Map() {}

Texture2D Map::normalAtlas;
Texture2D Map::collisionAtlas;

std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> Map::normalTilemap[levelAmount];
std::vector<Tile> Map::normalTiles;

std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> Map::collisionTilemap[levelAmount];
std::vector<Tile> Map::collisionTiles;

std::unordered_map<Vector2, int, Vector2Hash, Vector2Equal> Map::backTilemap[levelAmount];
std::vector<Tile> Map::backTiles;

std::vector<Rectangle> Map::spikes;

Vector2 Map::mapSize;
Vector2 Map::currentSpawnPoint;

bool Map::switchBlocksOn;
bool Map::mapHasSwitchBlocks;

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

void Map::GetCurrentMapSize()
{
    GetMapSize("data/level" + std::to_string(currentLevel) + "_collision.csv");
}

void Map::LoadContent()
{
    normalAtlas = LoadTexture("assets/map/normal_atlas.png");
    collisionAtlas = LoadTexture("assets/map/collision_atlas.png");
    
    for(int i = 0; i < levelAmount; i++)
    {
        normalTilemap[i] = LoadMap("data/level" + std::to_string(i) + "_normal.csv");
        collisionTilemap[i] = LoadMap("data/level" + std::to_string(i) + "_collision.csv");
	backTilemap[i] = LoadMap("data/level" + std::to_string(i) + "_back.csv"); 
    }
}

void Map::UnloadContent()
{
    UnloadTexture(normalAtlas);
    UnloadTexture(collisionAtlas);
}

void Map::CalculateTiles()
{
    normalTiles.clear();
    collisionTiles.clear();
    backTiles.clear();

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
        
        normalTiles.push_back({dest, normalAtlas, item.second}); //TEXTURE WON'T BE NEEDED HERE, JUST TEMPORARY
    }
    
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
        
        collisionTiles.push_back({dest, collisionAtlas, item.second}); //TEXTURE WON'T BE NEEDED HERE, JUST TEMPORARY
    }

    for(std::pair<Vector2, int> item : backTilemap[currentLevel])
    {
        Rectangle dest = {
            .x=item.first.x * tilesize,
            .y=item.first.y * tilesize,
            .width=tilesize,
            .height=tilesize
        };

        int x = item.second % tpr;
        int y = item.second / tpr;

        Rectangle src = {
            .x=(float) x * p_tilesize,
            .y=(float) y * p_tilesize,
            .width=(float) p_tilesize,
            .height=(float) p_tilesize
        };

        backTiles.push_back({dest, normalAtlas, item.second}); //TEXTURE WON'T BE NEEDED HERE, JUST TEMPORARY
    }
}

void Map::Draw()
{
    int tpr = 8; //Tiles per row
    int p_tilesize = 32; //Pixel Tilesize
    
    for(std::pair<Vector2, int> item : backTilemap[currentLevel])
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
        
        DrawTexturePro(normalAtlas, src, dest, {0, 0}, 0.0f, WHITE);
    }
    
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
        
        //if(item.second >= 16 && item.second <= 31 && !switchBlocksOn) src.y += (float) tilesize * 2;
        Color color = WHITE;
        if(item.second >= 16 && item.second <= 31 && !switchBlocksOn) color.a -= 200;
        DrawTexturePro(normalAtlas, src, dest, {0, 0}, 0.0f, color);
    }
}

void Map::DrawCollisions()
{
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
        
        DrawTexturePro(collisionAtlas, src, dest, {0, 0}, 0.0f, WHITE);
    }
}

void Map::MoveTo(int level, Player *player)
{
    if(level < levelAmount) currentLevel = level; else currentLevel = 0;
    LoadMapSizeAndTiles();
    mapHasSwitchBlocks = false;
    Eval();
    speedrunTimer.Stop();
    player->ResetPos();
    SaveFile::SetCurrentLevel(currentLevel);
}

void Map::AdvanceLevel(Player *player)
{ MoveTo(currentLevel + 1, player); }

void Map::Win(Player *player)
{ MoveTo(0, player); }

void Map::LoadMapSizeAndTiles()
{
    Map::GetCurrentMapSize();
    Map::CalculateTiles();
}

void Map::Eval()
{
    spikes.clear();
    
    for(Tile tile : collisionTiles)
    {
        switch (tile.GetType()) {
            case Map::CollisionTileType::SPIKE_DOWN:
                spikes.push_back({tile.GetPos().x + 8, tile.GetPos().y + 12, 16, 20});
            break;
            
            case Map::CollisionTileType::SPIKE_LEFT:
                spikes.push_back({tile.GetPos().x, tile.GetPos().y + 8, 20, 16});
            break;
            
            case Map::CollisionTileType::SPIKE_UP:
                spikes.push_back({tile.GetPos().x + 8, tile.GetPos().y, 16, 20});
            break;
            
            case Map::CollisionTileType::SPIKE_RIGHT:
                spikes.push_back({tile.GetPos().x + 12, tile.GetPos().y + 8, 20, 16});
            break;
            
            case Map::CollisionTileType::SPAWN_PLAYER:
                currentSpawnPoint = tile.GetPos();
            break;

	    case Map::CollisionTileType::CASETTE:
	    	mapHasSwitchBlocks = true;
	    break;
        }
    }
}
