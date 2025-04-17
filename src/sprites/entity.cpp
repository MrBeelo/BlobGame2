#include "../headers/entity.h"
#include "../headers/raylib.h"
#include "../headers/sprite.h"
#include "../headers/globals.hpp"
#include "../headers/map.h"
#include <algorithm>
#include <cmath>

Entity::Entity(Vector2 pos, Vector2 size, Texture2D texture) : Sprite(pos, size, texture) {}
Entity::~Entity() {}

void Entity::Update()
{
    ApplyGravity();
    
    UpdateDest();
    
    AddPosX(velocity.x);
    CheckCollisions(Map::collisionTiles, true);
    AddPosY(velocity.y);
    CheckCollisions(Map::collisionTiles, false);
    
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

void Entity::CheckCollisions(std::vector<Tile> &collisionTiles, bool horizontal)
{
    this->isCollidingX = false;
    this->isCollidingY = false;
    this->isCollidingDown = false;
    
    for(Tile tile : collisionTiles)
    {
        if(CheckCollisionRecs(tile.GetDest(), this->GetDest()))
        {
            if(horizontal)
            {
                this->isCollidingX = true;
                if(this->GetVelocity().x > 0) //MOVING RIGHT
                {
                    this->SetPosX(tile.GetDest().x - this->GetDest().width);
                } else if(this->GetVelocity().x < 0) { //MOVING LEFT
                    this->SetPosX(tile.GetDest().x + tile.GetDest().width);
                }
            } else
            {
                this->isCollidingY = true;
                if(this->GetVelocity().y < 0) //MOVING UP
                {
                    this->SetVelocityY(-0.1f);
                    this->SetPosY(tile.GetDest().y + tile.GetDest().height);
                } else if (this->GetVelocity().y > 0) { //MOVING DOWN
                    this->isCollidingDown = true;
                    this->SetVelocityY(0.1f);
                    this->SetPosY(tile.GetDest().y - this->GetDest().height);
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
    if(!IsOnGround())
    {
        AddVelocity({0, 1});
    }
}

bool Entity::IsOnGround()
{
    return IsTouchingMapFloor() || isCollidingDown;
}
