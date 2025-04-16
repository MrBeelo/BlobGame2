#include "../headers/entity.h"
#include "../headers/raylib.h"
#include "../headers/sprite.h"
#include "../headers/globals.h"

Entity::Entity(Vector2 pos, Vector2 size, Texture2D texture) : Sprite(pos, size, texture) {}
Entity::~Entity() {}

void Entity::Update()
{
    Sprite::Update();
    AddPos(velocity);
}

Vector2 Entity::GetVelocity()
{
    return this->velocity;
}

void Entity::SetVelocityX(float velocity)
{
    this->velocity.x = velocity;
}

void Entity::SetVelocityY(float velocity)
{
    this->velocity.y = velocity;
}

void Entity::SetVelocity(Vector2 velocity)
{
    this->velocity = velocity;
}

void Entity::AddVelocity(Vector2 velocity)
{
    this->velocity.x += velocity.x * simDT;
    this->velocity.y += velocity.y * simDT;
}