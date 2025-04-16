#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "entity.h"

class Player : public Entity
{
    public:
    Player(Vector2 pos, Vector2 size);
    ~Player();
    static Texture2D texture;
    
    static void LoadContent();
    static void UnloadContent();
    
    void Update();
    void Draw();
    
    float speed = 5;
    bool isTouchingGround();
};

#endif