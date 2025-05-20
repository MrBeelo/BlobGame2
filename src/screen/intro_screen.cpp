#include "../headers/screen/intro_screen.h"
#include "../headers/main/globals.hpp"
#include "../headers/main/savefile.h"

int IntroScreen::textCounter = 0;
Timer IntroScreen::textTimer = {0};

IntroScreen::IntroScreen() {
    textTimer = {2.5f, true, false, [this]() { this->AddText(); }};
}
IntroScreen::~IntroScreen() {}

void IntroScreen::Update() 
{
    textTimer.Update();
    if(textCounter >= 5) 
    {
        gameState = PLAYING; 
        speedrunTimer.Start();
        SaveFile::SetIntroDone(true);
        introDone = SaveFile::GetIntroDone();
    }
}

void IntroScreen::Draw()
{
    if(textCounter >= 1) Text::DrawOutfitBoldText(text1, {Text::GetCenteredOutfitBoldXPos(text1, fontsize), 450}, fontsize, WHITE);
    if(textCounter >= 2) Text::DrawOutfitBoldText(text2, {Text::GetCenteredOutfitBoldXPos(text2, fontsize), 500}, fontsize, WHITE);
    if(textCounter >= 3) Text::DrawOutfitBoldText(text3, {Text::GetCenteredOutfitBoldXPos(text3, fontsize), 550}, fontsize, WHITE);
    if(textCounter >= 4) Text::DrawOutfitBoldText(text4, {Text::GetCenteredOutfitBoldXPos(text4, fontsize), 600}, fontsize, WHITE);
}

void IntroScreen::Start()
{
    textCounter = 0;
    textTimer.Activate();
}

void IntroScreen::AddText()
{
    textCounter++;
}