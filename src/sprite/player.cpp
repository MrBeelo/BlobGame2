#include "../headers/sprite/player.h"
#include "../headers/raylib/raylib.h"
#include "../headers/sprite/entity.h"
#include "../headers/main/globals.hpp"
#include "../headers/main/sounds.h"
#include "../headers/main/map.h"
#include "../headers/main/input_manager.h"
#include "../headers/screen/death_screen.h"
#include "../headers/main/modifiers.h"
#include <algorithm>
#include <string>

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
    animationTimer = {0.3f, true, true, [this]() { this->CalculateAnimations(); }};
    cameraTimer = {0.33333333333f, true, false, [this]() { this->RotateCameraAndUpdateBGColor(); }};
}

Player::~Player() {}

void Player::Update()
{
    if(!isTerminalOpen) PlayerMove();
    Entity::Update();
    HandleXBufferedCollisions(Map::collisionTiles);
    
    animationTimer.Update();
    EvaluateTextures();
    EvaluateTextureOffset();
    
    if(speedrunTimer.GetStopwatchTime() > timeLimit) KillWithMessage("Died to time.");
    if(Modifiers::speedMod) speed = 12; else speed = 7;
    
    UpdatePlayerCamera();
    screenPos = GetWorldToScreen2D(GetPos(), Player::camera);
    screenPos.x = std::clamp(screenPos.x, 0.0f, simulationSize.x);
    screenPos.y = std::clamp(screenPos.y, 0.0f, simulationSize.y);
}

void Player::Draw()
{
    Sprite::DrawAdvanced(isLeft, {textureOffset, 0}, {20, 30});
}

void Player::ResetPos()
{
    SetPos(Map::currentSpawnPoint);
}

void Player::ResetState()
{
    SetVelocity({0, 0.5f});
    isLeft = false;
    if(Modifiers::speedMod) speed = 12; else speed = 7;
    alive = true;
}

void Player::PlayerMove()
{
    SetVelocityX(0);
    
    if(InputManager::IsActionHeld(InputManager::ACTION_MOVE_LEFT))
    {
        SetVelocityX(!Modifiers::inverseMod ? -speed : speed);
    }
    else if(InputManager::IsActionHeld(InputManager::ACTION_MOVE_RIGHT))
    {
        SetVelocityX(!Modifiers::inverseMod ? speed : -speed);
    }
    
    if((IsOnGround() || isCollidingXWithBuffer || isCollidingWithDoubleJumpCrystal) && InputManager::IsActionPressed(InputManager::ACTION_JUMP))
    {
        SetSoundVolume(Sounds::jump, 0.5f);
        PlaySound(Sounds::jump);
        SetVelocityY(-15);
    }
}

void Player::Kill()
{
    KillWithMessage("");
}

void Player::KillWithMessage(std::string text)
{
    Entity::Kill();
    Respawn();
    DeathScreen::deathMessage = text;
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
            shouldResetAnimation = true;
        }
        
        if((GetVelocity().y > -3) && (GetVelocity().y < 3)) texture = JUMP_2; else texture = JUMP_1;
    } else if(IsOnGround())
    {
        if(!animationTimer.active && shouldResetAnimation) {
            animationTimer.ActivateImmediately();
            shouldResetAnimation = false;
        }
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
    
    if(camera.rotation < 0) camera.rotation += simDT;
    if(camera.rotation > 0) camera.rotation -= simDT;

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

void Player::RotateCameraAndUpdateBGColor()
{
    if(cameraGoingLeft) camera.rotation -= 4; else camera.rotation += 4;
    cameraGoingLeft = !cameraGoingLeft;

    if(!offbeat)
    {
	offbeat = true;
  	Map::switchBlocksOn = !Map::switchBlocksOn;
  	if(Map::mapHasSwitchBlocks) PlaySound(Sounds::lSwitch);
    } else {
 	offbeat = false;
    }

    int color = GetRandomValue(0, 5);
    switch (color) {
        case 0: backgroundColor = {36, 22, 22, 255}; break; //RED
        case 1: backgroundColor = {36, 28, 22, 255}; break; //ORANGE
        case 2: backgroundColor = {36, 36, 22, 255}; break; //YELLOW
        case 3: backgroundColor = {22, 36, 22, 255}; break; //GREEN
        case 4: backgroundColor = {22, 36, 36, 255}; break; //BLUE
        case 5: backgroundColor = {36, 22, 36, 255}; break; //PURPLE
    }
}

void Player::HandleXBufferedCollisions(std::vector<Tile> &collisionTiles)
{
    isCollidingXWithBuffer = false;
    
    for(Tile tile : collisionTiles)
    {
        float rectBuffer = 8;
        bufferedRect = GetDest();
        bufferedRect.x -= rectBuffer;
        bufferedRect.width += rectBuffer * 2;
        
        if(CheckCollisionRecs(tile.GetDest(), bufferedRect))
        {
            switch(tile.GetType())
            {
                case Map::CollisionTileType::SOLID:
                case Map::CollisionTileType::PASS:
                case Map::CollisionTileType::WIN:
                this->isCollidingXWithBuffer = true;
                break;
            }
        }
    }
}
