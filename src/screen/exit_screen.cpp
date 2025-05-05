#include "../headers/screen/exit_screen.h"
#include "../headers/main/globals.hpp"

ExitScreen::ExitScreen() {}
ExitScreen::~ExitScreen() {}

void ExitScreen::Update() 
{
    button1.Update();
    button2.Update(); 
    
    if (button1.IsClicked()) LeaveGame();
    if (button2.IsClicked()) gameState = MAIN_MENU;
}

void ExitScreen::Draw()
{
    DrawCenteredTitle();

    button1.Draw();
    button2.Draw();
}