#include "../headers/screen/pass_screen.h"
#include "../headers/main/globals.hpp"
#include <string>

PassScreen::PassScreen() {}
PassScreen::~PassScreen() {}

void PassScreen::Update() 
{
    button1.Update();
    
    if (button1.IsClicked()) {
        gameState = PLAYING;
        speedrunTimer.Start();
    }
}

void PassScreen::Draw() {
    DrawCenteredTitle();
    
    button1.Draw();
    
    std::string speedrunText = "Clocked in at " + ToStringWithDecimalPoints(speedrunTimer.GetStopwatchTime(), 1);
    
    Text::DrawOutfitBoldText(speedrunText.c_str(), 
        {simulationSize.x / 2 - Text::MeasureOutfitBoldText(speedrunText.c_str(), 42).x / 2,
            simulationSize.y / 4}, 
        42, BLACK);
}