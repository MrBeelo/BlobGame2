#include "../headers/player.h"
#include "../headers/raylib.h"
#include "../headers/entity.h"
#include "../headers/map.h"
#include <algorithm>

using namespace std;

Texture2D Player::texture;

void Player::LoadContent()
{
    texture = LoadTexture("res/assets/player/blob.png");
}

void Player::UnloadContent()
{
    UnloadTexture(texture);
}

Player::Player(Vector2 pos, Vector2 size) : Entity(pos, size, texture) {}
Player::~Player() {}

void Player::Update()
{
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
    
    if(IsTouchingMapFloor() || isCollidingDown)  
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
    
    if(IsKeyPressed(KEY_R))
    {
        ResetPos();
        ResetState();
    }
    
    Entity::Update();
}

void Player::Draw()
{
    Sprite::DrawWithFlip(isLeft);
}

void Player::ResetPos()
{
    //TEMPORARY
    SetPos({50, 50});
}

void Player::ResetState()
{
    SetVelocity({0, 0.5f});
    isLeft = false;
    speed = 5;
}
