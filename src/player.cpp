#include "headers/player.h"
#include "headers/raylib.h"
#include "headers/entity.h"
#include "headers/globals.h"

Texture2D Player::texture;

void Player::LoadContent()
{
    texture = LoadTexture("blob.png");
}

void Player::UnloadContent()
{
    UnloadTexture(texture);
}

Player::Player(Vector2 pos, Vector2 size) : Entity(pos, size, texture) {}
Player::~Player() {}

void Player::Update()
{
    velocity = {0, 0};
    
    if(IsKeyDown(KEY_W))
    {
        velocity.y = -5;
    }
    
    if(IsKeyDown(KEY_S))
    {
        velocity.y = 5;
    }
    
    if(IsKeyDown(KEY_A))
    {
        velocity.x = -5;
    }
    
    if(IsKeyDown(KEY_D))
    {
        velocity.x = 5;
    }
    
    Entity::Update();
}

void Player::Draw()
{
    Sprite::Draw();
}