#include "../headers/main/terminal.h"
#include "../headers/main/input_manager.h"
#include "../headers/main/text.hpp"
#include <iostream>

Terminal::Terminal() {}
Terminal::~Terminal() {}

void Terminal::Update()
{
    if(isTerminalOpen)
    {
        if(IsKeyPressed(KEY_BACKSPACE) && TextLength(text.c_str()) > 0)
        {
            //InputText = InputText.Substring(0, InputText.Length - 1);
            text = TextSubtext(text.c_str(), 0, TextLength(text.c_str()) - 1);
        } else {
            KeyboardKey key = (KeyboardKey)GetKeyPressed();
            if(key != 0)
            {
                char character = InputManager::KeyToChar(key, IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));
                std::cout << "Pressed key: " << character << std::endl;
                text += character;
            }
        }
    }
}

void Terminal::Draw()
{
    if(isTerminalOpen) {
        DrawRectangleRec(rect, {25, 25, 25, 100});
        Text::DrawOutfitBoldText(text.c_str(), {rect.x + buffer, rect.y + buffer}, 20, WHITE);
    }
}