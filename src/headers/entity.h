#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "sprite.h"

class Entity : public Sprite
{
    private:
    Vector2 velocity = {0, 0};
    
    public: 
    Entity(Vector2 pos, Vector2 size, Texture2D texture);
    ~Entity();
    void Update();
    Vector2 GetVelocity();
    void SetVelocityX(float velocity);
    void SetVelocityY(float velocity);
    void SetVelocity(Vector2 velocity);
    void AddVelocity(Vector2 velocity);
};

#endif