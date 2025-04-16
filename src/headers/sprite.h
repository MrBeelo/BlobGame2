#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"

class Sprite
{
    private:
    Vector2 pos;
    Vector2 size;
    Rectangle bounds;
    Texture2D texture;
    
    public:
    Sprite(Vector2 pos, Vector2 size, Texture2D texture);
    ~Sprite();
    Vector2 GetPos();
    Vector2 GetSize();
    Rectangle GetBounds();
    void SetPos(Vector2 pos);
    void SetSize(Vector2 size);
    void AddPos(Vector2 pos);
    void Update();
    void Draw();
};


#endif