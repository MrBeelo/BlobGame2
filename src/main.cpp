#include "headers/raylib.h"
#include "headers/resource_dir.h"
#include "headers/text.hpp"
#include "headers/player.h"

Vector2 windowSize = {800, 450};
float simDT = 0;

int main(void)
{
    InitWindow(windowSize.x, windowSize.y, "Blob Game 2");
    SearchAndSetResourceDir("assets");
    
    Text::LoadContent();
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
    
    Text::UnloadContent();
    Player::UnloadContent();

    CloseWindow();

    return 0;
}