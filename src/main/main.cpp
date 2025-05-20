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
#include "../headers/screen/info_screen.h"
#include "../headers/screen/modifiers_screen.h"
#include "../headers/main/sounds.h"
#include "../headers/main/map.h"
#include "../headers/main/shaders.h"
#include "../headers/raylib/resource_dir.h"
#include "../headers/main/input_manager.h"
#include "../headers/main/terminal.h"
#include "../headers/main/modifiers.h"
#include "../headers/main/savefile.h"
#include "../headers/sprite/fred.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

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
const char *version = "1.0.0";
Texture2D raylibLogo;
const char *credits = "Made By MrBeelo";
Stopwatch speedrunTimer = {false};
Color backgroundColor = WHITE;
Image windowIcon;
bool isTerminalOpen = false;
float timeLimit = 40;

std::string ToStringWithDecimalPoints(float value, int decimalPoints) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(decimalPoints) << value;
    return out.str();
}


void LeaveGame()
{
    Text::UnloadContent();
    Player::UnloadContent();
    Fred::UnloadContent();
    Map::UnloadContent();
    Sounds::UnloadContent();
    Shaders::UnloadContent();
    UnloadRenderTexture(target);
    UnloadTexture(raylibLogo);
    UnloadImage(windowIcon);

    CloseWindow();
}

int main(void)
{ 
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    
    InitWindow(windowSize.x, windowSize.y, "Blob Game 2");
    InitAudioDevice();
    SetRandomSeed(1923742355);
    
    SearchAndSetResourceDir("res");
    
    Text::LoadContent();
    Player::LoadContent();
    Fred::LoadContent();
    Map::LoadContent();
    Sounds::LoadContent();
    Shaders::LoadContent();
    
    PlaySound(Sounds::success);
    
    windowIcon = LoadImage("assets/other/icon.png");
    SetWindowIcon(windowIcon);
    SetExitKey(KEY_NULL);
    
    raylibLogo = LoadTexture("assets/other/raylib_logo.png");
    
    Player player = {};
    Fred fred = {};
    
    player.CameraConfig();
    
    target = LoadRenderTexture(simulationSize.x, simulationSize.y);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);
    
    Terminal terminal = {};
    
    SaveFile::Load();
    currentLevel = SaveFile::GetCurrentLevel();
    
    Map::MoveTo(currentLevel, &player);
    
    MainMenuScreen mainMenuScreen = {};
    PausedScreen pausedScreen = {};
    ExitScreen exitScreen = {};
    DeathScreen deathScreen = {};
    PassScreen passScreen = {};
    WinScreen winScreen = {};
    InfoScreen infoScreen = {};
    ModifiersScreen modifiersScreen = {};
    
    const char *tutorialText = "";
    const char *levelText = "";
    
    while (!WindowShouldClose())
    {  
        windowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};
        simDT = GetFrameTime() * 60;
        
        if(currentLevel > 0 && !Modifiers::immunityMod) speedrunTimer.Update();
        
        scale = std::min(windowSize.x / simulationSize.x, windowSize.y / simulationSize.y);
        
        vMouse.x = (GetMouseX() - (windowSize.x - (simulationSize.x * scale)) * 0.5f) / scale;
        vMouse.y = (GetMouseY() - (windowSize.y - (simulationSize.y * scale)) * 0.5f) / scale;
        vMouse = {std::clamp(vMouse.x, 0.0f, simulationSize.x), std::clamp(vMouse.y, 0.0f, simulationSize.y)};
        
        switch (gameState) {
            case PLAYING: 
                player.Update();
                if(Modifiers::fredMod) fred.Update(&player);
                
                if(player.GetPos().x <= 200) tutorialText = "AD to move, space to jump, S to slam.";
                else if (player.GetPos().x > 200 && player.GetPos().x <= 700) tutorialText = "Spikes kill.";
                else if (player.GetPos().x > 700 && player.GetPos().x <= 959) tutorialText = "Walljump on walls.";
                else if (player.GetPos().x > 959 && player.GetPos().x <= 1250) tutorialText = "Double jump on orange crystals.";
                else if (player.GetPos().x > 1250) tutorialText = "Get to the end in time.";
            break;  
            case MAIN_MENU: mainMenuScreen.Update(); break;
            case PAUSED: pausedScreen.Update(); break;
            case EXIT: exitScreen.Update(); break;
            case DIED: deathScreen.Update(); break;
            case PASS: passScreen.Update(); break;
            case WIN: winScreen.Update(); break;
            case INFO: infoScreen.Update(); break;
            case MODIFIERS: modifiersScreen.Update(); break;
        }
        
        switch(currentLevel)
        {
            case 0: levelText = "0 - TUTORIAL"; break;
            case 1: levelText = "1 - STARTING OFF SIMPLE"; break;
            case 2: levelText = "2 - STILL PRETTY EASY"; break;
            case 3: levelText = "3 - SPIKE HELL"; break;
            case 4: levelText = "4 - CLICK CLICK"; break;
            case 5: levelText = "5 - H2O HELPS"; break;
            case 6: levelText = "6 - WATER AND SWITCH DON'T MIX"; break;
            case 7: levelText = "7 - CHALLENGE RUN"; break;
            case 8: levelText = "8 - SPRING SPAM"; break;
            case 9: levelText = "9 - A BIT OF EVERYTHING"; break;
            case 10: levelText = "10 - AND SO IT ENDS"; break;
        }
        
        if(gameState == PLAYING || gameState == PAUSED || gameState == PASS || gameState == DIED) {
            if(currentLevel > 0)
            {
                UpdateMusicStream(Sounds::itsPizzaTime);
                if(!IsMusicStreamPlaying(Sounds::itsPizzaTime)) {
		       	PlayMusicStream(Sounds::itsPizzaTime);
			player.cameraTimer.Activate();
		}
                if(IsMusicStreamPlaying(Sounds::menuMusic)) StopMusicStream(Sounds::menuMusic);
                if(IsMusicStreamPlaying(Sounds::tutorialMusic)) StopMusicStream(Sounds::tutorialMusic);
            } else {
                UpdateMusicStream(Sounds::tutorialMusic);
                if(!IsMusicStreamPlaying(Sounds::tutorialMusic)) {
			PlayMusicStream(Sounds::tutorialMusic);
		       	player.cameraTimer.Activate();
		}
                if(IsMusicStreamPlaying(Sounds::menuMusic)) StopMusicStream(Sounds::menuMusic);
                if(IsMusicStreamPlaying(Sounds::itsPizzaTime)) StopMusicStream(Sounds::itsPizzaTime);
            }
            
            player.cameraTimer.Update(); 
        } else {
            UpdateMusicStream(Sounds::menuMusic);
            if(!IsMusicStreamPlaying(Sounds::menuMusic)) PlayMusicStream(Sounds::menuMusic);
            if(IsMusicStreamPlaying(Sounds::itsPizzaTime)) StopMusicStream(Sounds::itsPizzaTime);
            if(IsMusicStreamPlaying(Sounds::tutorialMusic)) StopMusicStream(Sounds::tutorialMusic);
            backgroundColor = {35, 35, 35, 255};
        }
        
        terminal.Update(&player);
        Shaders::Update(&player);
        
        if(Modifiers::tickTockMod) {
            if(currentLevel != 10) timeLimit = 25; else timeLimit = 40;
        } else {
            if(currentLevel != 10) timeLimit = 40; else timeLimit = 55;
        }
        
        if(InputManager::IsActionPressed(InputManager::ACTION_F3)) f3On = !f3On;
        if(InputManager::IsActionPressed(InputManager::ACTION_ESC)) {
            if(gameState == PLAYING) gameState = PAUSED;
            if(gameState == MAIN_MENU) gameState = EXIT;
        }
        if(InputManager::IsActionPressed(InputManager::ACTION_TERMINAL)) {
            isTerminalOpen = !isTerminalOpen;
            if(!terminal.text.empty()) terminal.text.pop_back();
        }
        
        BeginTextureMode(target);
        
        ClearBackground(backgroundColor);
        
        BeginMode2D(player.camera);
        
        if(gameState == PLAYING)
        {
            Map::Draw();
            player.Draw();
            if(f3On) {
                Map::DrawCollisions();
                DrawRectangleLinesEx(player.bufferedRect, 4, BLUE);
                DrawRectangleLinesEx(player.GetDest(), 4, RED);
            }
        }
        
        EndMode2D();
            
        switch (gameState) {
            case PLAYING: 
                Text::DrawOutfitBoldShakyText((ToStringWithDecimalPoints(timeLimit - speedrunTimer.GetStopwatchTime(), 1)).c_str(), {buffer, simulationSize.y - Text::MeasureOutfitBoldText(ToStringWithDecimalPoints(timeLimit - speedrunTimer.GetStopwatchTime(), 1).c_str(), 100).y - buffer}, 100, WHITE); 
                Text::DrawOutfitBoldShakyText(levelText, {buffer, buffer}, 32, WHITE);
                if(Modifiers::fredMod) fred.Draw();
                if(currentLevel == 0)
                {
                    Text::DrawOutfitBoldShakyText(tutorialText, 
                        {simulationSize.x / 2 - Text::MeasureOutfitBoldText(tutorialText, 42).x / 2,
                            simulationSize.y / 4}, 
                        42, WHITE);
                } else if(currentLevel == 10 && player.GetPos().x < 10) 
                {
                    Text::DrawOutfitBoldShakyText("FINAL LEVEL", 
                    {simulationSize.x / 2 - Text::MeasureOutfitBoldText("FINAL LEVEL", 128).x / 2,
                        simulationSize.y / 4}, 
                    128, WHITE);
                }
            break;
            case MAIN_MENU: mainMenuScreen.Draw(); break;
            case PAUSED: pausedScreen.Draw(); break;
            case EXIT: exitScreen.Draw(); break;
            case DIED: deathScreen.Draw(); break;
            case PASS: passScreen.Draw(); break;
            case WIN: winScreen.Draw(); break;
            case INFO: infoScreen.Draw(); break;
            case MODIFIERS: modifiersScreen.Draw(); break;
        }
        
        terminal.Draw();
        
        //DEBUG
        if(f3On)
        {
            Text::DrawOutfitBoldText(("Game State: " + std::to_string(gameState)).c_str(), {10, 10 + 30 * 0}, 24, WHITE);
            Text::DrawOutfitBoldText(("FPS: " + std::to_string(GetFPS())).c_str(), {10, 10 + 30 * 1}, 24, WHITE);
            Text::DrawOutfitBoldText(("Map Size: " + Text::Vector2ToString(Map::mapSize)).c_str(), {10, 10 + 30 * 2}, 24, WHITE);
            Text::DrawOutfitBoldText(("Current Level: " + std::to_string(currentLevel)).c_str(), {10, 10 + 30 * 3}, 24, WHITE);
            Text::DrawOutfitBoldText(("Pos: " + Text::Vector2ToString(player.GetPos())).c_str(), {10, 10 + 30 * 4}, 24, WHITE);
            Text::DrawOutfitBoldText(("Velocity: " + Text::Vector2ToString(player.GetVelocity())).c_str(), {10, 10 + 30 * 5}, 24, WHITE);
            Text::DrawOutfitBoldText(("Is on ground: " + std::to_string(player.IsOnGround())).c_str(), {10, 10 + 30 * 6}, 24, WHITE);
            Text::DrawOutfitBoldText(("Is Left: " + std::to_string(player.isLeft)).c_str(), {10, 10 + 30 * 7}, 24, WHITE);
            Text::DrawOutfitBoldText(("Is Colliding: " + (std::to_string(player.isCollidingX) + ", " + std::to_string(player.isCollidingY))).c_str(), {10, 10 + 30 * 8}, 24, WHITE);
            Text::DrawOutfitBoldText(("Is Alive: " + std::to_string(player.alive)).c_str(), {10, 10 + 30 * 9}, 24, WHITE);
            Text::DrawOutfitBoldText(("Is Moving: " + std::to_string(player.IsMoving())).c_str(), {10, 10 + 30 * 10}, 24, WHITE);
            Text::DrawOutfitBoldText(("Animation Active: " + std::to_string(player.animationTimer.active)).c_str(), {10, 10 + 30 * 11}, 24, WHITE);
            Text::DrawOutfitBoldText(("Texture Offset: " + std::to_string(player.textureOffset)).c_str(), {10, 10 + 30 * 12}, 24, WHITE);
            Text::DrawOutfitBoldText(("Timer time passed: " + std::to_string(GetTime() - player.animationTimer.startTime)).c_str(), {10, 10 + 30 * 13}, 24, WHITE);
            Text::DrawOutfitBoldText(("Immunity Mod: " + std::to_string(Modifiers::immunityMod)).c_str(), {10, 10 + 30 * 14}, 24, WHITE);
            Text::DrawOutfitBoldText(("Switch Blocks On: " + std::to_string(Map::switchBlocksOn)).c_str(), {10, 10 + 30 * 15}, 24, WHITE);
        }
            
        EndTextureMode();
        
        BeginDrawing();
        ClearBackground({20, 20, 20, 255});
        
        if(Shaders::useShader) BeginShaderMode(Shaders::fsShaders[Shaders::FX_CRT_FADED]);
            DrawTexturePro(target.texture, {0, 0, (float)target.texture.width, -(float)target.texture.height}, 
                {(windowSize.x - simulationSize.x * scale) * 0.5f, (windowSize.y - simulationSize.y * scale) * 0.5f, simulationSize.x * scale, simulationSize.y * scale}, 
                {0, 0}, 0.0f, WHITE);
        if(Shaders::useShader) EndShaderMode();
        
        EndDrawing();
    }

    LeaveGame();
    return 0;
}
