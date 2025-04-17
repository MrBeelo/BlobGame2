#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "sprite.h"

class Tile : public Sprite
{
    private:
    int type = 0;
    
    public: 
    Tile(Vector2 pos, Vector2 size, Texture2D texture, int type);
    Tile(Rectangle dest, Texture2D texture, int type);
    ~Tile();
    int GetType();
};

#endif