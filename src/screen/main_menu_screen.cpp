#include "../headers/screen/main_menu_screen.h"
#include "../headers/main/globals.hpp"

MainMenuScreen::MainMenuScreen() {}
MainMenuScreen::~MainMenuScreen() {}

void MainMenuScreen::Update() 
{
    button1.Update();
    button2.Update(); 
    
    if (button1.IsClicked()) gameState = PLAYING;
    if (button2.IsClicked()) gameState = EXIT;
}

void MainMenuScreen::Draw() {
    DrawCenteredTitle();
    
    button1.Draw();
    button2.Draw();
}