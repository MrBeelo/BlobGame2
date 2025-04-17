#include "../headers/entity.h"
#include "../headers/raylib.h"
#include "../headers/sprite.h"
#include "../headers/globals.hpp"
#include "../headers/map.h"

Entity::Entity(Vector2 pos, Vector2 size, Texture2D texture) : Sprite(pos, size, texture) {}
Entity::~Entity() {}

void Entity::Update()
{
    AddPosY(velocity.y);
    CheckCollisionsY(this, Map::collisionTiles);
    AddPosX(velocity.x);
    CheckCollisionsX(this, Map::collisionTiles);
    
    UpdateDest();
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

void Entity::CheckCollisionsX(Entity *entity, std::vector<Tile> &collisionTiles)
{
    entity->isCollidingX = false;
    
    for(Sprite tile : collisionTiles)
    {
        if(CheckCollisionRecs(entity->GetDest(), tile.GetDest()))
        {
            entity->isCollidingX = true;
            if(entity->GetDest().x > tile.GetDest().x)
            {
                entity->SetPosX(tile.GetDest().x + tile.GetDest().width);
            } else {
                entity->SetPosX(tile.GetDest().x - entity->GetDest().width);
            }
        }
    }
}

void Entity::CheckCollisionsY(Entity *entity, std::vector<Tile> &collisionTiles)
{
    entity->isCollidingY = false;
    
    for(Sprite tile : collisionTiles)
    {
        if(CheckCollisionRecs(entity->GetDest(), tile.GetDest()))
        {
            entity->isCollidingY = true;
            if(entity->GetDest().y > tile.GetDest().y)
            {
                entity->SetPosY(tile.GetDest().y + tile.GetDest().height);
            } else {
                entity->SetPosY(tile.GetDest().y - entity->GetDest().height);
            }
        }
    }
}

bool Entity::IsTouchingMapFloor()
{
    return GetPos().y >= Map::mapSize.y - GetSize().y;
}