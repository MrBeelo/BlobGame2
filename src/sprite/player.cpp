#include "../headers/sprite/player.h"
#include "../headers/raylib/raylib.h"
#include "../headers/sprite/entity.h"
#include "../headers/main/globals.hpp"

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

Player::Player(Vector2 pos, Vector2 size) : Entity(pos, size, texture, true) {}
Player::~Player() {}

void Player::Update()
{
    PlayerMove();
    Entity::Update();
    
    if(IsKeyPressed(KEY_R))
    {
        ResetPos();
        ResetState();
    }
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
    alive = true;
}

void Player::PlayerMove()
{
    SetVelocityX(0);
    
    if(IsKeyDown(KEY_A))
    {
        SetVelocityX(-speed);
    }
    else if(IsKeyDown(KEY_D))
    {
        SetVelocityX(speed);
    }
    
    if(IsOnGround() && IsKeyPressed(KEY_SPACE))
    {
        SetVelocityY(-15);
    }
}

void Player::Kill()
{
    Entity::Kill();
    Respawn();
    gameState = DIED;
}

void Player::Respawn()
{
    ResetPos();
    ResetState();
}