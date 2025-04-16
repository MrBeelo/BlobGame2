#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "sprite.h"

class Entity : public Sprite
{
    public: 
    Vector2 velocity;
    Entity(Vector2 pos, Vector2 size, Texture2D texture);
    ~Entity();
    void Update();
};

#endif