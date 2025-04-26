#include "../headers/screen/info_screen.h"
#include "../headers/main/globals.hpp"

InfoScreen::InfoScreen() {}
InfoScreen::~InfoScreen() {}

void InfoScreen::Update() 
{
    button1.Update();
    
    if (button1.IsClicked()) gameState = MAIN_MENU;
}

void InfoScreen::Draw()
{
    DrawCenteredTitle();
    
    button1.Draw();
    
    std::string lines[] = {
                    "Hey!",
                    "This is a sequel to Blob Game, made to test my nonexistant C++ coding skills!",
                    "'Blob' was a meme made by my friend Nick_Greek as a test for Minecraft modeling.",
                    "I want this version of the game to be different from the original,",
                    "so I'm theming it around speedruns.",
                    "",
                    "",
                    "CONTROLS:",
                    "AD to move",
                    "Space to jump",
                    "",
                    "",
                    "CREDITS:",
                    "Most of the art, coding, sound effects and the menu music made by MrBeelo.",
                    "Inspiration and a little help with art by Nick_Greek.",
                    "Some coding fundementals by 'Coding with Sphere' and 'GameDev Quickie'. Built with RayLib",
                    "Font: Outfit Bold by Rodrigo Fuenzalida.",
                    "Game music: It's Pizza Time! by Tour De Pizza.",
                    "Inspiration from the roblox game 'Grace' for the speedrun idea.",
                    "",
                    "",
                    "SPECIAL THANKS:",
                    "You <3"
                    };
                    
    for(int i = 0; i < sizeof(lines) / sizeof(lines[0]); i++)
    {
        Text::DrawOutfitBoldText(lines[i].c_str(), {simulationSize.x / 2 - (Text::MeasureOutfitBoldText(lines[i].c_str(), 30).x / 2), static_cast<float>(i * 30 + i * 5 + 80)}, 30, BLACK);
    }
}