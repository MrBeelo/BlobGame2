#include "../headers/sprite/tile.h"
#include "../headers/raylib/raylib.h"
#include "../headers/sprite/sprite.h"

Tile::Tile(Vector2 pos, Vector2 size, Texture2D texture, int type) : Sprite(pos, size, texture) {
    this->type = type;
}

Tile::Tile(Rectangle dest, Texture2D texture, int type) : Sprite(dest, texture) {
    this->type = type;
}

Tile::~Tile() {}

int Tile::GetType()
{
    return this->type;
}