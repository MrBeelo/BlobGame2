#ifndef SPRITE_H
#define SPRITE_H

#include "../raylib/raylib.h"

class Sprite
{
    private:
    Vector2 pos = {0, 0};
    Vector2 size;
    Rectangle dest;
    Texture2D texture;
    
    public:
    Sprite(Vector2 pos, Vector2 size, Texture2D texture);
    Sprite(Rectangle dest, Texture2D texture);
    ~Sprite();
    Vector2 GetPos();
    Vector2 GetSize();
    void SetPosX(float pos);
    void SetPosY(float pos);
    void SetPos(Vector2 pos);
    void SetSize(Vector2 size);
    Rectangle GetDest();
    void AddPosX(float pos);
    void AddPosY(float pos);
    void AddPos(Vector2 pos);
    void Draw();
    void DrawWithSrc(Vector2 srcRect, Vector2 textureSnippetSize);
    void DrawWithFlip(bool isLeft);
    void DrawAdvanced(bool isLeft, Vector2 srcRect, Vector2 textureSnippetSize);
    void UpdateDest();
};


#endif