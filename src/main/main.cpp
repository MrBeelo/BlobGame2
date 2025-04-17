#define RAYGUI_IMPLEMENTATION

#include "../headers/raygui.h"
#include "../headers/raylib.h"
#include "../headers/text.hpp"
#include "../headers/player.h"
#include "../headers/globals.hpp"
#include "../headers/main_menu_screen.h"
#include "../headers/map.h"
#include <string>

float buffer = 10.0f;
Vector2 windowSize = {1920, 1031};
float simDT = 0;
bool f3On = false;
int currentLevel = 0;
GameState gameState = MAIN_MENU;

void LeaveGame()
{
    Text::UnloadContent();
    Player::UnloadContent();
    Map::UnloadContent();

    CloseWindow();
}

int main(void)
{ 
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    InitWindow(windowSize.x, windowSize.y, "Blob Game 2");
    //SearchAndSetResourceDir("res/assets");
    
    InitAudioDevice();
    SetWindowIcon(LoadImage("res/assets/other/icon.png"));
    SetExitKey(KEY_NULL);
    
    Text::LoadContent();
    Player::LoadContent();
    Map::LoadContent();
    
    Map::LoadMapSizeAndTiles(currentLevel);
    Player player = {{50, 50}, {40, 60}};
    
    while (!WindowShouldClose())
    {
        windowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};
        simDT = GetFrameTime() * 60;
        
        if(IsKeyPressed(KEY_F3)) f3On = !f3On;
        
        switch (gameState) {
            case PLAYING:
                player.Update();
            break;
                
            case MAIN_MENU:
                MainMenuScreen::Update();
            break;
        }
        
        BeginDrawing();
        ClearBackground(SKYBLUE);
            
        switch (gameState) {
            case PLAYING:
                Map::Draw(currentLevel);
                player.Draw();
            break;
                
            case MAIN_MENU:
                MainMenuScreen::Draw();
            break;
        }
        
        //DEBUG
        if(f3On)
        {
            if(gameState == PLAYING) Map::DrawCollisions(currentLevel);
            Text::DrawOutfitBoldText(("Game State: " + std::to_string(gameState)).c_str(), {10, 10}, 24, BLACK);
            Text::DrawOutfitBoldText(("Map Size: " + Text::Vector2ToString(Map::mapSize)).c_str(), {10, 40}, 24, BLACK);
            Text::DrawOutfitBoldText(("Pos: " + Text::Vector2ToString(player.GetPos())).c_str(), {10, 70}, 24, BLACK);
            Text::DrawOutfitBoldText(("Velocity: " + Text::Vector2ToString(player.GetVelocity())).c_str(), {10, 100}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is on ground: " + std::to_string(player.IsOnGround())).c_str(), {10, 130}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is Left: " + std::to_string(player.isLeft)).c_str(), {10, 160}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is Colliding: " + (std::to_string(player.isCollidingX) + ", " + std::to_string(player.isCollidingY))).c_str(), {10, 190}, 24, BLACK);
        }
            
        EndDrawing();
    }

    LeaveGame();
    
    return 0;
}