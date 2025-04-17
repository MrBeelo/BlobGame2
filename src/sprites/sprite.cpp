#include "../headers/sprite.h"
#include "../headers/raylib.h"
#include "../headers/globals.hpp"

Sprite::Sprite(Vector2 pos, Vector2 size, Texture2D texture)
{
    this->pos = pos;
    this->size = size;
    this->texture = texture;
}

Sprite::Sprite(Rectangle dest, Texture2D texture)
{
    this->pos = {dest.x, dest.y};
    this->size = {dest.width, dest.height};
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

void Sprite::SetPosX(float pos)
{
    this->pos.x = pos;
}

void Sprite::SetPosY(float pos)
{
    this->pos.y = pos;
}

void Sprite::SetPos(Vector2 pos)
{
    this->pos = pos;
}

void Sprite::SetSize(Vector2 size)
{
    this->size = size;
}

Rectangle Sprite::GetDest()
{
    return this->dest;
}

void Sprite::AddPosX(float pos)
{
    this->pos.x += pos * simDT;
}

void Sprite::AddPosY(float pos)
{
    this->pos.y += pos * simDT;
}

void Sprite::AddPos(Vector2 pos)
{
    this->pos.x += pos.x * simDT;
    this->pos.y += pos.y * simDT;
}

void Sprite::Update()
{
    dest = {pos.x, pos.y, size.x, size.y};
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