#include "headers/entity.h"
#include "headers/raylib.h"
#include "headers/sprite.h"
#include "headers/globals.h"

Entity::Entity(Vector2 pos, Vector2 size, Texture2D texture) : Sprite(pos, size, texture) {}
Entity::~Entity() {}

void Entity::Update()
{
    Sprite::Update();
    AddPos(velocity);
}