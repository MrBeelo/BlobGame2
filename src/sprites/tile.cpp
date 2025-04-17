#include "../headers/tile.h"
#include "../headers/raylib.h"
#include "../headers/sprite.h"

Tile::Tile(Vector2 pos, Vector2 size, Texture2D texture, int type) : Sprite(pos, size, texture) {
    this->type = type;
}

Tile::Tile(Rectangle dest, Texture2D texture, int type) : Sprite(dest, texture) {
    this->type = type;
}

Tile::~Tile() {}