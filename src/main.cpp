#include "headers/raylib.h"
#include "headers/resource_dir.h"
#include "headers/sprite.h"
#include "headers/player.h"

Vector2 windowSize = {800, 450};
float simDT = 0;

int main(void)
{
    InitWindow(windowSize.x, windowSize.y, "Blob Game 2");
    SearchAndSetResourceDir("assets");
    
    Player::LoadContent();
    
    Player player = {{10, 10}, {40, 60}};
    
    while (!WindowShouldClose())
    {
        simDT = GetFrameTime() * 60;
        
        player.Update();
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            player.Draw();
        EndDrawing();
    }
    
    Player::UnloadContent();

    CloseWindow();

    return 0;
}