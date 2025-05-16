#include "../headers/sprite/fred.h"
#include "../headers/main/globals.hpp"
#include "../headers/main/sounds.h"

Texture2D Fred::textureAtlas;

Fred::Fred() : Sprite({simulationSize.x / 2 - defSize.x / 2, simulationSize.y / 2 - defSize.y / 2}, defSize, textureAtlas){
    rotationTimer = {0.15f, true, true, [this]() { this->Tick(); }};
    spawnTimer = {15.0f, true, true, [this]() { this->Spawn(); }};
}

Fred::~Fred() {}

void Fred::LoadContent()
{
    textureAtlas = LoadTexture("assets/sprite/fred_atlas.png");
}

void Fred::UnloadContent()
{
    UnloadTexture(textureAtlas);
}

void Fred::Update(Player *player)
{
    rotationTimer.Update();
    spawnTimer.Update();
    
    openEyes = eyeDelay >= 10 ? true : false;
    
    if(eyeDelay >= 11) {
        eyeDelay = 0;
        Despawn();
    }
    
    if(isSpawned && openEyes) if(player->IsMoving()) player->KillWithMessage("Died to Fred.");
    
    //SetPos(defPos);
    //AddPos(posOffset);
}

void Fred::Spawn()
{
    this->isSpawned = true;
}

void Fred::Despawn()
{
    this->isSpawned = false;
}

void Fred::Tick()
{
    if(isSpawned)
    {
        if(rotationQuarterCounter < 4) rotationQuarterCounter++; else rotationQuarterCounter = 0;
        eyeDelay++;
        posOffset = {(float) GetRandomValue(-10, 10), (float) GetRandomValue(-10, 10)};
        SetSoundPitch(Sounds::fredBoop, GetRandomValue(5, 15) / 10.0f);
        PlaySound(Sounds::fredBoop);
    }
}

void Fred::Draw()
{
    if(isSpawned) DrawWithSrc({48.0f * rotationQuarterCounter, 48.0f * openEyes}, {48.0f, 48.0f});
}