#define RAYGUI_IMPLEMENTATION

#include "../headers/raylib/raylib.h"
#include "../headers/main/text.hpp"
#include "../headers/sprite/player.h"
#include "../headers/main/globals.hpp"
#include "../headers/screen/main_menu_screen.h"
#include "../headers/screen/paused_screen.h"
#include "../headers/screen/exit_screen.h"
#include "../headers/screen/death_screen.h"
#include "../headers/screen/pass_screen.h"
#include "../headers/screen/win_screen.h"
#include "../headers/sound/sounds.h"
#include "../headers/map/map.h"
#include "../headers/raylib/resource_dir.h"
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
    Sounds::UnloadContent();

    CloseWindow();
}

int main(void)
{ 
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    
    InitWindow(windowSize.x, windowSize.y, "Blob Game 2");
    InitAudioDevice();
    
    SearchAndSetResourceDir("res");
    
    Text::LoadContent();
    Player::LoadContent();
    Map::LoadContent();
    Sounds::LoadContent();
    
    PlaySound(Sounds::success);
    
    SetWindowIcon(LoadImage("assets/other/icon.png"));
    SetExitKey(KEY_NULL);
    
    Player player = {{50, 50}};
    Map::LoadMapSizeAndTiles();
    
    player.CameraConfig();
    
    MainMenuScreen mainMenuScreen = {};
    PausedScreen pausedScreen = {};
    ExitScreen exitScreen = {};
    DeathScreen deathScreen = {};
    PassScreen passScreen = {};
    WinScreen winScreen = {};
    
    while (!WindowShouldClose())
    {
        windowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};
        simDT = GetFrameTime() * 60;
        
        if(IsKeyPressed(KEY_F3)) f3On = !f3On;
        if(IsKeyPressed(KEY_ESCAPE) && gameState == PLAYING) gameState = PAUSED;
        
        switch (gameState) {
            case PLAYING: player.Update(); break;  
            case MAIN_MENU: mainMenuScreen.Update(); break;
            case PAUSED: pausedScreen.Update(); break;
            case EXIT: exitScreen.Update(); break;
            case DIED: deathScreen.Update(); break;
            case PASS: passScreen.Update(); break;
            case WIN: winScreen.Update(); break;
        }
        
        BeginDrawing();
        
        ClearBackground(SKYBLUE);
        
        BeginMode2D(player.camera);
        
        if(gameState == PLAYING)
        {
            Map::Draw();
            player.Draw();
            if(f3On) Map::DrawCollisions();
        }
        
        EndMode2D();
            
        switch (gameState) {
            case PLAYING: break;
            case MAIN_MENU: mainMenuScreen.Draw(); break;
            case PAUSED: pausedScreen.Draw(); break;
            case EXIT: exitScreen.Draw(); break;
            case DIED: deathScreen.Draw(); break;
            case PASS: passScreen.Draw(); break;
            case WIN: winScreen.Draw(); break;
        }
        
        //DEBUG
        if(f3On)
        {
            Text::DrawOutfitBoldText(("Game State: " + std::to_string(gameState)).c_str(), {10, 10}, 24, BLACK);
            Text::DrawOutfitBoldText(("Map Size: " + Text::Vector2ToString(Map::mapSize)).c_str(), {10, 40}, 24, BLACK);
            Text::DrawOutfitBoldText(("Current Level: " + std::to_string(currentLevel)).c_str(), {10, 70}, 24, BLACK);
            Text::DrawOutfitBoldText(("Pos: " + Text::Vector2ToString(player.GetPos())).c_str(), {10, 100}, 24, BLACK);
            Text::DrawOutfitBoldText(("Velocity: " + Text::Vector2ToString(player.GetVelocity())).c_str(), {10, 130}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is on ground: " + std::to_string(player.IsOnGround())).c_str(), {10, 160}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is Left: " + std::to_string(player.isLeft)).c_str(), {10, 190}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is Colliding: " + (std::to_string(player.isCollidingX) + ", " + std::to_string(player.isCollidingY))).c_str(), {10, 220}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is Alive: " + std::to_string(player.alive)).c_str(), {10, 250}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is Moving: " + std::to_string(player.IsMoving())).c_str(), {10, 280}, 24, BLACK);
            Text::DrawOutfitBoldText(("Texture Tick Counter: " + std::to_string(player.textureTickCounter)).c_str(), {10, 310}, 24, BLACK);
            Text::DrawOutfitBoldText(("Texture Offset: " + std::to_string(player.textureOffset)).c_str(), {10, 340}, 24, BLACK);
        }
            
        EndDrawing();
    }

    LeaveGame();
    
    return 0;
}