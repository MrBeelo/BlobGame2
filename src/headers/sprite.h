#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

class Sprite
{
    private:
    Vector2 pos = {0, 0};
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
    void AddPosX(float pos);
    void AddPosY(float pos);
    void AddPos(Vector2 pos);
    void Update();
    void Draw();
    void DrawWithSrc(Vector2 srcRect);
    void DrawWithFlip(bool isLeft);
    void DrawAdvanced(bool isLeft, Vector2 srcRect);
};


#endif