#include "../headers/sprite.h"
#include "../headers/raylib.h"
#include "../headers/globals.h"

Sprite::Sprite(Vector2 pos, Vector2 size, Texture2D texture)
{
    this->pos = pos;
    this->size = size;
    this->texture = texture;
}

Sprite::~Sprite() {}

Vector2 Sprite::GetPos()
{
    return this->pos;
}

Vector2 Sprite::GetSize()
{
    return this->size;
}

Rectangle Sprite::GetBounds()
{
    return {pos.x, pos.y, size.x, size.y};
}

void Sprite::SetPos(Vector2 pos)
{
    this->pos = pos;
}

void Sprite::SetSize(Vector2 size)
{
    this->size = size;
}

void Sprite::AddPos(Vector2 pos)
{
    this->pos.x += pos.x * simDT;
    this->pos.y += pos.y * simDT;
}

void Sprite::Update()
{
    bounds = {pos.x, pos.y, size.x, size.y};
}

void Sprite::Draw()
{
    DrawTexturePro(texture, {0, 0, (float) texture.width, (float) texture.height}, bounds, {0, 0}, 0, WHITE);
}

void Sprite::DrawWithFlip(bool isLeft)
{
    float flip = isLeft ? -1.0f : 1.0f;
    DrawTexturePro(texture, {0, 0, (float) texture.width * flip, (float) texture.height}, bounds, {0, 0}, 0, WHITE);
}