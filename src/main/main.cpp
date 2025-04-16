#define RAYGUI_IMPLEMENTATION

#include "../headers/raygui.h"
#include "../headers/raylib.h"
#include "../headers/resource_dir.h"
#include "../headers/text.hpp"
#include "../headers/player.h"
#include "../headers/globals.h"
#include "../headers/main_menu_screen.h"
#include <string>

float buffer = 10.0f;
Vector2 windowSize = {800, 450};
float simDT = 0;
GameState gameState = MAIN_MENU;

void LeaveGame()
{
    Text::UnloadContent();
    Player::UnloadContent();

    CloseWindow();
}

int main(void)
{ 
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    InitWindow(windowSize.x, windowSize.y, "Blob Game 2");
    SearchAndSetResourceDir("assets");
    
    InitAudioDevice();
    SetWindowIcon(LoadImage("other/icon.png"));
    SetExitKey(KEY_NULL);
    
    Text::LoadContent();
    Player::LoadContent();
    
    Player player = {{10, 10}, {40, 60}};
    
    while (!WindowShouldClose())
    {
        simDT = GetFrameTime() * 60;
        
        switch (gameState) {
            case PLAYING:
                player.Update();
            break;
                
            case MAIN_MENU:
                MainMenuScreen::Update();
            break;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
            
        switch (gameState) {
            case PLAYING:
                player.Draw();
            break;
                
            case MAIN_MENU:
                MainMenuScreen::Draw();
            break;
        }
            
        Text::DrawOutfitBoldText(("Game State: " + std::to_string(gameState)).c_str(), {10, 10}, 24, BLACK);
        Text::DrawOutfitBoldText(("Pos: " + Text::Vector2ToString(player.GetPos())).c_str(), {10, 40}, 24, BLACK);
        Text::DrawOutfitBoldText(("Velocity: " + Text::Vector2ToString(player.GetVelocity())).c_str(), {10, 70}, 24, BLACK);
        Text::DrawOutfitBoldText(("Is on ground: " + std::to_string(player.IsTouchingGround())).c_str(), {10, 100}, 24, BLACK);
        Text::DrawOutfitBoldText(("Is Left: " + std::to_string(player.isLeft)).c_str(), {10, 130}, 24, BLACK);
            
        EndDrawing();
    }

    LeaveGame();
    
    return 0;
}