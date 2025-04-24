#include <algorithm>

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
#include "../headers/main/sounds.h"
#include "../headers/main/map.h"
#include "../headers/main/shaders.h"
#include "../headers/raylib/resource_dir.h"
#include "../headers/main/input_manager.h"
#include "../headers/main/timer.h"
#include <string>

float buffer = 10.0f;
Vector2 windowSize = {1920, 1031};
const Vector2 simulationSize = {1920, 1080};
float simDT = 0;
bool f3On = false;
int currentLevel = 0;
GameState gameState = MAIN_MENU;
RenderTexture2D target;
float scale;
Vector2 vMouse;
const char *version = "PRE-ALPHA";
Texture2D raylibLogo;
const char *credits = "Made By MrBeelo";
void LeaveGame()
{
    Text::UnloadContent();
    Player::UnloadContent();
    Map::UnloadContent();
    Sounds::UnloadContent();
    Shaders::UnloadContent();
    UnloadRenderTexture(target);

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
    Shaders::LoadContent();
    
    PlaySound(Sounds::success);
    
    SetWindowIcon(LoadImage("assets/other/icon.png"));
    SetExitKey(KEY_NULL);
    
    raylibLogo = LoadTexture("assets/other/raylib_logo.png");
    
    Player player = {};
    Map::LoadMapSizeAndTiles();
    
    player.CameraConfig();
    
    MainMenuScreen mainMenuScreen = {};
    PausedScreen pausedScreen = {};
    ExitScreen exitScreen = {};
    DeathScreen deathScreen = {};
    PassScreen passScreen = {};
    WinScreen winScreen = {};
    
    target = LoadRenderTexture(simulationSize.x, simulationSize.y);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);
    
    Map::MoveTo(0, &player);
    
    while (!WindowShouldClose())
    {  
        windowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};
        simDT = GetFrameTime() * 60;
        
        scale = std::min(windowSize.x / simulationSize.x, windowSize.y / simulationSize.y);
        
        vMouse.x = (GetMouseX() - (windowSize.x - (simulationSize.x * scale)) * 0.5f) / scale;
        vMouse.y = (GetMouseY() - (windowSize.y - (simulationSize.y * scale)) * 0.5f) / scale;
        vMouse = {std::clamp(vMouse.x, 0.0f, simulationSize.x), std::clamp(vMouse.y, 0.0f, simulationSize.y)};
        
        if(InputManager::IsActionPressed(InputManager::ACTION_F3)) f3On = !f3On;
        if(InputManager::IsActionPressed(InputManager::ACTION_ESC)) {
            if(gameState == PLAYING) gameState = PAUSED;
            if(gameState == MAIN_MENU) gameState = EXIT;
        }
        
        switch (gameState) {
            case PLAYING: player.Update(); break;  
            case MAIN_MENU: mainMenuScreen.Update(); break;
            case PAUSED: pausedScreen.Update(); break;
            case EXIT: exitScreen.Update(); break;
            case DIED: deathScreen.Update(); break;
            case PASS: passScreen.Update(); break;
            case WIN: winScreen.Update(); break;
        }
        
        BeginTextureMode(target);
        
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
            Text::DrawOutfitBoldText(("Game State: " + std::to_string(gameState)).c_str(), {10, 10 + 30 * 0}, 24, BLACK);
            Text::DrawOutfitBoldText(("FPS: " + std::to_string(GetFPS())).c_str(), {10, 10 + 30 * 1}, 24, BLACK);
            Text::DrawOutfitBoldText(("Map Size: " + Text::Vector2ToString(Map::mapSize)).c_str(), {10, 10 + 30 * 2}, 24, BLACK);
            Text::DrawOutfitBoldText(("Current Level: " + std::to_string(currentLevel)).c_str(), {10, 10 + 30 * 3}, 24, BLACK);
            Text::DrawOutfitBoldText(("Pos: " + Text::Vector2ToString(player.GetPos())).c_str(), {10, 10 + 30 * 4}, 24, BLACK);
            Text::DrawOutfitBoldText(("Velocity: " + Text::Vector2ToString(player.GetVelocity())).c_str(), {10, 10 + 30 * 5}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is on ground: " + std::to_string(player.IsOnGround())).c_str(), {10, 10 + 30 * 6}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is Left: " + std::to_string(player.isLeft)).c_str(), {10, 10 + 30 * 7}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is Colliding: " + (std::to_string(player.isCollidingX) + ", " + std::to_string(player.isCollidingY))).c_str(), {10, 10 + 30 * 8}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is Alive: " + std::to_string(player.alive)).c_str(), {10, 10 + 30 * 9}, 24, BLACK);
            Text::DrawOutfitBoldText(("Is Moving: " + std::to_string(player.IsMoving())).c_str(), {10, 10 + 30 * 10}, 24, BLACK);
            Text::DrawOutfitBoldText(("Texture Tick Counter: " + std::to_string(player.textureTickCounter)).c_str(), {10, 10 + 30 * 11}, 24, BLACK);
            Text::DrawOutfitBoldText(("Texture Offset: " + std::to_string(player.textureOffset)).c_str(), {10, 10 + 30 * 12}, 24, BLACK);
        }
            
        EndTextureMode();
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        if(Shaders::useShader) BeginShaderMode(Shaders::fsShaders[Shaders::shader]);
            DrawTexturePro(target.texture, {0, 0, (float)target.texture.width, -(float)target.texture.height}, 
                {(windowSize.x - simulationSize.x * scale) * 0.5f, (windowSize.y - simulationSize.y * scale) * 0.5f, simulationSize.x * scale, simulationSize.y * scale}, 
                {0, 0}, 0.0f, WHITE);
        if(Shaders::useShader) EndShaderMode();
        
        EndDrawing();
    }

    LeaveGame();
    
    return 0;
}