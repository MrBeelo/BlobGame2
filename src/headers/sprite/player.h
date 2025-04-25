#ifndef PLAYER_H
#define PLAYER_H

#include "../raylib/raylib.h"
#include "../main/timer.h"
#include "entity.h"

class Player : public Entity
{
    public:
    Player();
    Player(const Player &) = default;
    Player(Player &&) = delete;
    Player &operator=(const Player &) = default;
    Player &operator=(Player &&) = delete;
    ~Player();
    static Texture2D textureAtlas;
    static void LoadContent();
    static void UnloadContent();
    void Update();
    void Draw();
    float speed = 7;
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
    void EvaluateTextures();
    static Camera2D camera;
    void CameraConfig();
    void UpdatePlayerCamera();
    void CalculateAnimations();
    bool doWalk1 = true;
    Timer animationTimer = {0};
    bool shouldResetAnimation = false;
    Timer cameraTimer = {0};
    bool cameraGoingLeft = false;
    void RotateCameraAndUpdateBGColor();
};

#endif