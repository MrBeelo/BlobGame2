#include "headers/player.h"
#include "headers/raylib.h"
#include "headers/entity.h"
#include "headers/globals.h"
#include "headers/text.hpp"
#include <algorithm>
#include <string>

using namespace std;

Texture2D Player::texture;

void Player::LoadContent()
{
    texture = LoadTexture("player/blob.png");
}

void Player::UnloadContent()
{
    UnloadTexture(texture);
}

Player::Player(Vector2 pos, Vector2 size) : Entity(pos, size, texture) {}
Player::~Player() {}

void Player::Update()
{
    //TEMPORARY
    SetPos({clamp(GetPos().x, 0.0f, windowSize.x - GetSize().x), clamp(GetPos().y, 0.0f, windowSize.y - GetSize().y)});
    
    if(IsKeyDown(KEY_W))
    {
        SetVelocityY(-speed);
    }  
    else if(IsKeyDown(KEY_S))
    {
        SetVelocityY(speed);
    }
    
    if(IsKeyDown(KEY_A))
    {
        SetVelocityX(-speed);
    }
    else if(IsKeyDown(KEY_D))
    {
        SetVelocityX(speed);
    }
    else
    {
        SetVelocityX(0);
    }
    
    if(IsTouchingGround())  
    {
        SetVelocityY(0.5f);
        
        if(IsKeyPressed(KEY_SPACE))
        {
            SetVelocityY(-15);
        }
    } else 
    {
        AddVelocity({0, 1});
    }
    
    if(GetVelocity().x < 0)
    {
        isLeft = true;
    } else if(GetVelocity().x > 0)
    {
        isLeft = false;
    }
    
    Entity::Update();
}

void Player::Draw()
{
    Sprite::DrawWithFlip(isLeft);
    Text::DrawOutfitBoldText(("Pos: " + Text::Vector2ToString(GetPos())).c_str(), {10, 10}, 32, BLACK);
    Text::DrawOutfitBoldText(("Velocity: " + Text::Vector2ToString(GetVelocity())).c_str(), {10, 50}, 32, BLACK);
    Text::DrawOutfitBoldText(("Is on ground: " + to_string(IsTouchingGround())).c_str(), {10, 90}, 32, BLACK);
    Text::DrawOutfitBoldText(("Is Left: " + to_string(isLeft)).c_str(), {10, 130}, 32, BLACK);
}

bool Player::IsTouchingGround()
{
    //TEMPORARY
    return GetPos().y >= windowSize.y - GetSize().y;
}