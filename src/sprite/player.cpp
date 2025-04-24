#include "../headers/sprite/player.h"
#include "../headers/raylib/raylib.h"
#include "../headers/sprite/entity.h"
#include "../headers/main/globals.hpp"
#include "../headers/main/sounds.h"
#include "../headers/main/map.h"
#include "../headers/main/input_manager.h"
#include <algorithm>

Texture2D Player::textureAtlas;
Camera2D Player::camera;

void Player::LoadContent()
{
    textureAtlas = LoadTexture("assets/sprite/player_atlas.png");
}

void Player::UnloadContent()
{
    UnloadTexture(textureAtlas);
}

Player::Player() : Entity({0, 0}, defSize, textureAtlas, true) {
    animationTimer = {0.5f, true, true, [this]() { this->CalculateAnimations(); }};
}

Player::~Player() {}

void Player::Update()
{
    PlayerMove();
    Entity::Update();
    
    animationTimer.Update();
    EvaluateTextures();
    EvaluateTextureOffset();
    
    if(IsKeyPressed(KEY_R)) Respawn();
    
    UpdatePlayerCamera();
}

void Player::Draw()
{
    Sprite::DrawAdvanced(isLeft, {textureOffset, 0}, {20, 30});
}

void Player::ResetPos()
{
    Map::Eval(this);
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
    
    if(InputManager::IsActionHeld(InputManager::ACTION_MOVE_LEFT))
    {
        SetVelocityX(-speed);
    }
    else if(InputManager::IsActionHeld(InputManager::ACTION_MOVE_RIGHT))
    {
        SetVelocityX(speed);
    }
    
    if((IsOnGround() || isCollidingX) && InputManager::IsActionPressed(InputManager::ACTION_JUMP))
    {
        SetSoundVolume(Sounds::jump, 0.5f);
        PlaySound(Sounds::jump);
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

void Player::EvaluateTextureOffset()
{
    switch (texture) {
        case DEFAULT: textureOffset = 0; break;
        case IDLE_1: textureOffset = 20; break;
        case WALK_1: textureOffset = 40; break;
        case WALK_2: textureOffset = 60; break;
        case JUMP_1: textureOffset = 80; break;
        case JUMP_2: textureOffset = 100; break;
    }
}

void Player::EvaluateTextures()
{
    if(!IsOnGround()) //JUMPING
    {
        if(animationTimer.active) 
        {
            animationTimer.ForceDeactivate();
            //animationTimer.startTime += 0.5f;
        }
        
        if((GetVelocity().y > -3) && (GetVelocity().y < 3)) texture = JUMP_2; else texture = JUMP_1;
    } else if(IsOnGround())
    {
        if(!animationTimer.active) animationTimer.Activate();
    }
}

void Player::CameraConfig()
{
    camera.zoom = 1;
    camera.target = GetPos();
    camera.offset = {simulationSize.x / 2, simulationSize.y / 2};
}

void Player::UpdatePlayerCamera()
{
    camera.target = GetPos();

    float halfX = simulationSize.x / 2 / camera.zoom;
    float halfY = simulationSize.y / 2 / camera.zoom;

    camera.offset = {halfX, halfY};

    float clampX = std::clamp(camera.target.x, 0.0f + halfX, Map::mapSize.x - halfX);
    float clampY = std::clamp(camera.target.y, 0.0f + halfY, Map::mapSize.y - halfY);

    camera.target = {clampX, clampY};
}

void Player::CalculateAnimations()
{
    if(IsOnGround() && IsMoving()) //MOVING
    {
        if(texture == DEFAULT)
        {
            if(doWalk1)
            {
                texture = WALK_1;
                doWalk1 = false;
            } else if(!doWalk1)
            {
                texture = WALK_2;
                doWalk1 = true;
            }
        } else {
            texture = DEFAULT;
        }
    } else if(IsOnGround() && !IsMoving()) //IDLE
    {
        if(texture == DEFAULT) texture = IDLE_1; else texture = DEFAULT;
    }
}