#include "../headers/screen/main_menu_screen.h"
#include "../headers/main/globals.hpp"
#include "../headers/raylib/raylib.h"

MainMenuScreen::MainMenuScreen() {}
MainMenuScreen::~MainMenuScreen() {}

void MainMenuScreen::Update() 
{
    button1.Update();
    button2.Update();
    button3.Update();
    button4.Update();
    
    if (button1.IsClicked()) {
        gameState = PLAYING;
        speedrunTimer.Start();
    }
    
    if (button2.IsClicked()) gameState = MODIFIERS;
    if (button3.IsClicked()) gameState = INFO;
    if (button4.IsClicked()) gameState = EXIT;
}

void MainMenuScreen::Draw() {
    DrawCenteredTitle(0, WHITE);
    
    button1.Draw();
    button2.Draw();
    button3.Draw();
    button4.Draw();
    
    Text::DrawOutfitBoldText(version, {buffer, simulationSize.y - Text::MeasureOutfitBoldText(version, 24).y - buffer}, 24, WHITE);
    Text::DrawOutfitBoldText(credits, {simulationSize.x - Text::MeasureOutfitBoldText(credits, 24).x - buffer, simulationSize.y - Text::MeasureOutfitBoldText(credits, 24).y - buffer}, 24, WHITE);
    DrawTexture(raylibLogo, simulationSize.x - raylibLogo.width - buffer, buffer, WHITE);
}