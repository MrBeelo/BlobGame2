#include "../headers/sprite/sprite.h"
#include "../headers/raylib/raylib.h"
#include "../headers/main/globals.hpp"

Sprite::Sprite(Vector2 pos, Vector2 size, Texture2D texture)
{
    this->pos = pos;
    this->size = size;
    this->texture = texture;
    UpdateDest();
}

Sprite::Sprite(Rectangle dest, Texture2D texture)
{
    this->pos = {dest.x, dest.y};
    this->size = {dest.width, dest.height};
    this->texture = texture;
    UpdateDest();
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

void Sprite::SetPosX(float pos)
{
    this->pos.x = pos;
    UpdateDest();
}

void Sprite::SetPosY(float pos)
{
    this->pos.y = pos;
    UpdateDest();
}

void Sprite::SetPos(Vector2 pos)
{
    this->pos = pos;
    UpdateDest();
}

void Sprite::SetSize(Vector2 size)
{
    this->size = size;
    UpdateDest();
}

Rectangle Sprite::GetDest()
{
    return this->dest;
}

void Sprite::AddPosX(float pos)
{
    this->pos.x += pos * simDT;
    UpdateDest();
}

void Sprite::AddPosY(float pos)
{
    this->pos.y += pos * simDT;
    UpdateDest();
}

void Sprite::AddPos(Vector2 pos)
{
    this->pos.x += pos.x * simDT;
    this->pos.y += pos.y * simDT;
    UpdateDest();
}

void Sprite::Draw()
{
    DrawTexturePro(texture, {0, 0, (float) texture.width, (float) texture.height}, dest, {0, 0}, 0, WHITE);
}

void Sprite::DrawWithSrc(Vector2 srcRect)
{
    DrawTexturePro(texture, {srcRect.x, srcRect.y, (float) texture.width, (float) texture.height}, dest, {0, 0}, 0, WHITE);
}

void Sprite::DrawWithFlip(bool isLeft)
{
    float flip = isLeft ? -1.0f : 1.0f;
    DrawTexturePro(texture, {0, 0, (float) texture.width * flip, (float) texture.height}, dest, {0, 0}, 0, WHITE);
}

void Sprite::DrawAdvanced(bool isLeft, Vector2 srcRect)
{
    float flip = isLeft ? -1.0f : 1.0f;
    DrawTexturePro(texture, {srcRect.x, srcRect.y, (float) texture.width * flip, (float) texture.height}, dest, {0, 0}, 0, WHITE);
}

void Sprite::UpdateDest()
{
    dest = {pos.x, pos.y, size.x, size.y};
}