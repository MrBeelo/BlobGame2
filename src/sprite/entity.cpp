#include "../headers/sprite/entity.h"
#include "../headers/raylib/raylib.h"
#include "../headers/sprite/sprite.h"
#include "../headers/main/globals.hpp"
#include "../headers/map/map.h"
#include "../headers/sprite/player.h"
#include <algorithm>
#include <cmath>

Entity::Entity(Vector2 pos, Vector2 size, Texture2D texture) : Sprite(pos, size, texture) {
    this->isPlayer = false;
}
Entity::Entity(Vector2 pos, Vector2 size, Texture2D texture, bool isPlayer) : Sprite(pos, size, texture) {
    this->isPlayer = isPlayer;
}

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
            switch (tile.GetType()) 
            {
                case 0:
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
                break;
                
                case 1:
                if(isPlayer)
                {
                    Player* player = static_cast<Player*>(this);
                    if((horizontal && !isCollidingX) || (!horizontal && !isCollidingY))
                    {
                        
                        player->Kill();
                    }
                } 
                break;
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

void Entity::Kill()
{
    alive = false;
}
