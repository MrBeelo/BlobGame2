#include "../headers/player.h"
#include "../headers/raylib.h"
#include "../headers/entity.h"
#include "../headers/globals.h"
#include <algorithm>

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

bool Player::IsTouchingGround()
{
    //TEMPORARY
    return GetPos().y >= windowSize.y - GetSize().y;
}

void Player::ResetPos()
{
    //TEMPORARY
    SetPos({10, 10});
}

void Player::ResetState()
{
    SetVelocity({0, 0.5f});
    isLeft = false;
    speed = 5;
}
