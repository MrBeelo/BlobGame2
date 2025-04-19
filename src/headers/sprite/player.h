#ifndef PLAYER_H
#define PLAYER_H

#include "../raylib/raylib.h"
#include "entity.h"

class Player : public Entity
{
    public:
    Player(Vector2 pos);
    ~Player();
    static Texture2D textureAtlas;
    static void LoadContent();
    static void UnloadContent();
    void Update();
    void Draw();
    float speed = 5;
    constexpr static Vector2 defSize = {40, 60};
    enum Animation { DEFAULT, IDLE_1, WALK_1, WALK_2, JUMP_1, JUMP_2 };
    Animation texture = DEFAULT;
    float textureOffset = 0;
    void ResetPos();
    void ResetState();
    void PlayerMove();
    void Kill();
    void Respawn();
    void EvaluateTextureOffset();
    float textureTickCounter = 0;
    void EvaluateTextures(float delay);
    static Camera2D camera;
    void CameraConfig();
    void UpdatePlayerCamera();
};

#endif