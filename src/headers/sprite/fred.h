#ifndef FRED_H
#define FRED_H

#include "../raylib/raylib.h"
#include "../main/globals.hpp"
#include "player.h"
#include "sprite.h"
#include "../main/timer.h"

class Fred : public Sprite
{
    public:
    Fred();
    ~Fred();
    static Texture2D textureAtlas;
    static void LoadContent();
    static void UnloadContent();
    void Update(Player *player);
    void Tick();
    void Spawn();
    void CheckPlayer();
    void Despawn();
    void Draw();
    constexpr static Vector2 defSize = {48 * 4, 48 * 4};
    Vector2 defPos = {simulationSize.x / 2 - defSize.x / 2, simulationSize.y / 2 - defSize.y / 2};
    int rotationQuarterCounter = 0;
    bool isSpawned = false;
    bool openEyes = false;
    Timer rotationTimer = {0};
    Timer spawnTimer = {0};
    int eyeDelay = 0;
    Vector2 posOffset = {0, 0};
};


#endif