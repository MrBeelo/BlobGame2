#include "../headers/sprite/entity.h"
#include "../headers/raylib/raylib.h"
#include "../headers/sprite/sprite.h"
#include "../headers/main/globals.hpp"
#include "../headers/main/map.h"
#include "../headers/sprite/player.h"
#include "../headers/main/modifiers.h"
#include "../headers/main/input_manager.h"
#include "../headers/main/sounds.h"
#include <algorithm>

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
    if (horizontal) {
        this->isCollidingX = false;
    } else {
        this->isCollidingY = false;
        this->isCollidingDown = false;
    }
    
    this->isCollidingWithSwitch = false;
    this->isCollidingWithHazard = false;
    this->isCollidingWithDoubleJumpCrystal = false;
    
    for(Tile tile : collisionTiles)
    {
        if(CheckCollisionRecs(tile.GetDest(), this->GetDest()))
        {
            switch (tile.GetType()) 
            {
                case Map::CollisionTileType::SOLID:
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
                        this->SetVelocityY(0.1f);
                        this->SetPosY(tile.GetDest().y + tile.GetDest().height);
                    } else if (this->GetVelocity().y > 0) { //MOVING DOWN
                        this->isCollidingDown = true;
                        this->SetVelocityY(0.1f);
                        this->SetPosY(tile.GetDest().y - this->GetDest().height);
                    }
                }
                break;
                
                case Map::CollisionTileType::HAZARD:
                if(isPlayer) this->isCollidingWithHazard = true;
                break;
                
                case Map::CollisionTileType::PASS:
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
                    if(!isPlayer)
                    {
                        if(this->GetVelocity().y < 0) //MOVING UP
                        {
                            this->SetVelocityY(-0.1f);
                            this->SetPosY(tile.GetDest().y + tile.GetDest().height);
                        } else if (this->GetVelocity().y > 0) { //MOVING DOWN
                            this->isCollidingDown = true;
                            this->SetVelocityY(0.1f);
                            this->SetPosY(tile.GetDest().y - this->GetDest().height);
                        }
                    } else if(isPlayer && this->GetVelocity().y > 0)
                    {
                        Player* player = static_cast<Player*>(this);
                        gameState = PASS;
                        Map::AdvanceLevel(player);
                        player->Respawn();
                    }
                }
                break;
                
                case Map::CollisionTileType::WIN:
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
                        if(isPlayer)
                        {
                            Player* player = static_cast<Player*>(this);
                            gameState = WIN;
                            Map::Win(player);
                            player->Respawn();
                        }
                        
                        
                        this->isCollidingDown = true;
                        this->SetVelocityY(0.1f);
                        this->SetPosY(tile.GetDest().y - this->GetDest().height);
                    }
                }
                break;
                
                case Map::CollisionTileType::WATER:
                    if(velocity.y > 0) velocity.y = 1;
		    if(isPlayer && velocity.y > 0 && !isTerminalOpen && InputManager::IsActionHeld(InputManager::ACTION_MOVE_DOWN)) velocity.y = 3.5f;
                break;
                
                case Map::CollisionTileType::DOUBLE_JUMP:
                    isCollidingWithDoubleJumpCrystal = true;
                break;
                
                case Map::CollisionTileType::CASETTE:
                isCollidingWithSwitch = true;
                if(Map::switchBlocksOn)
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
                            this->SetVelocityY(0.1f);
                            this->SetPosY(tile.GetDest().y + tile.GetDest().height);
                        } else if (this->GetVelocity().y > 0) { //MOVING DOWN
                            this->isCollidingDown = true;
                            this->SetVelocityY(0.1f);
                            this->SetPosY(tile.GetDest().y - this->GetDest().height);
                        }
                    }
                }
                break;
            }
        }
    }
    
    for(Rectangle spike : Map::spikes)
    {
        if(CheckCollisionRecs(this->GetDest(), spike))
        {
            Player* player = static_cast<Player*>(this);
            if(((horizontal && !isCollidingX) || (!horizontal && !isCollidingY)) && !Modifiers::immunityMod) player->KillWithMessage("Died to spike.");
        }
    }
    
    for(Rectangle spring : Map::springs)
    {
        if(CheckCollisionRecs(this->GetDest(), spring))
        {
            SetVelocity({0, -20});
            if(isPlayer) PlaySound(Sounds::boing);
        }
    }
    
    if(isCollidingWithHazard && isPlayer)
    {
        Player* player = static_cast<Player*>(this);
        if(((horizontal && !isCollidingX) || (!horizontal && !isCollidingY)) && !Modifiers::immunityMod) player->KillWithMessage("Died to hazard.");
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

bool Entity::IsMoving()
{
    return GetVelocity().x != 0;
}

void Entity::Teleport(Vector2 pos)
{
    SetPos(pos);
}
