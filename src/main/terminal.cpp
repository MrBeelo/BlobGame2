#include "../headers/main/terminal.h"
#include "../headers/main/input_manager.h"
#include "../headers/main/text.hpp"
#include "../headers/main/sounds.h"
#include "../headers/main/modifiers.h"

Terminal::Terminal() {}
Terminal::~Terminal() {}

void Terminal::Update(Player *player)
{
    if(isTerminalOpen)
    {
        int key = GetCharPressed();
        
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125)) text += (char)key;
            key = GetCharPressed();
        }
        
        if (IsKeyPressed(KEY_BACKSPACE)) if (!text.empty()) text.pop_back();
        
        if(InputManager::IsActionPressed(InputManager::ACTION_CONFIRM))
        {
            //Unfortunately you can't switch strings in C++
            //I would come up with a better method but I'm too bored
            //if/else if spam it is...
            
            if(text == "/resetPos") player->ResetPos();
            if(text == "/resetState") player->ResetState();
            if(text == "/respawn") player->Respawn();
            if(text == "/yipee") PlaySound(Sounds::success);
            if(text == "/speedMod") Modifiers::speedMod = !Modifiers::speedMod;
            if(text == "/inverseMod") Modifiers::inverseMod = !Modifiers::inverseMod;
            if(text == "/lightsOutMod") Modifiers::lightsOutMod = !Modifiers::lightsOutMod;
            if(text == "/tickTockMod") Modifiers::tickTockMod = !Modifiers::tickTockMod;
            if(text == "/immunityMod") Modifiers::immunityMod = !Modifiers::immunityMod;
            
            text = "";
            isTerminalOpen = false;
        }
    }
}

void Terminal::Draw()
{
    if(isTerminalOpen) {
        DrawRectangleRec(rect, {25, 25, 25, 100});
        Text::DrawOutfitBoldText(text.c_str(), {rect.x + buffer, rect.y + buffer}, 50, WHITE);
    }
}