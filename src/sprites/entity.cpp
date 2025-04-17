#include "../headers/entity.h"
#include "../headers/raylib.h"
#include "../headers/sprite.h"
#include "../headers/globals.hpp"
#include "../headers/map.h"
#include <algorithm>

Entity::Entity(Vector2 pos, Vector2 size, Texture2D texture) : Sprite(pos, size, texture) {}
Entity::~Entity() {}

void Entity::Update()
{
    ApplyGravity();
    
    UpdateDest();
    
    AddPosX(velocity.x);
    CheckCollisions(this, Map::collisionTiles, true);
    AddPosY(velocity.y);
    CheckCollisions(this, Map::collisionTiles, false);
    
    UpdateDest();
    SetPos({std::clamp(GetPos().x, 0.0f, Map::mapSize.x - GetSize().x), std::clamp(GetPos().y, 0.0f, Map::mapSize.y - GetSize().y)});
    
    if(velocity.x < 0)
    {
        isLeft = true;
    } else if(velocity.x > 0)
    {
        isLeft = false;
    }
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

void Entity::CheckCollisions(Entity *entity, std::vector<Tile> &collisionTiles, bool horizontal)
{
    entity->isCollidingX = false;
    entity->isCollidingY = false;
    entity->isCollidingDown = false;
    
    for(Tile tile : collisionTiles)
    {
        if(CheckCollisionRecs(tile.GetDest(), entity->GetDest()))
        {
            if(horizontal)
            {
                entity->isCollidingX = true;
                if(entity->GetVelocity().x > 0) //MOVING RIGHT
                {
                    entity->SetPosX(tile.GetDest().x - entity->GetDest().width);
                } else if(entity->GetVelocity().x < 0) { //MOVING LEFT
                    entity->SetPosX(tile.GetDest().x + tile.GetDest().width);
                }
            } else if(!horizontal)
            {
                entity->isCollidingY = true;
                if(entity->GetVelocity().y < 0) //MOVING UP
                {
                    entity->SetPosY(tile.GetDest().y + tile.GetDest().height);
                } else if (entity->GetVelocity().y > 0) { //MOVING DOWN
                    entity->SetPosY(tile.GetDest().y - entity->GetDest().height);
                    entity->isCollidingDown = true;
                }
            }
        }
    }
}

bool Entity::IsTouchingMapFloor()
{
    return GetPos().y >= Map::mapSize.y - GetSize().y;
}

void Entity::ApplyGravity()
{
    if(IsOnGround())
    {
        SetVelocityY(0.0f);
    } else {
        AddVelocity({0, 1});
    }
}

bool Entity::IsOnGround()
{
    return IsTouchingMapFloor() || isCollidingDown;
}
