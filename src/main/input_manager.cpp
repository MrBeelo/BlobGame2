#include "../headers/main/input_manager.h"
#include <cctype>
#include <cstddef>

bool InputManager::IsActionPressed(InputAction action) {
    switch (action) {
        case ACTION_MOVE_LEFT:
            return IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT) ||
                (IsGamepadAvailable(0) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.5f);

        case ACTION_MOVE_RIGHT:
            return IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT) ||
                (IsGamepadAvailable(0) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0.5f);

        case ACTION_MOVE_UP:
            return IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) ||
                (IsGamepadAvailable(0) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.5f);

        case ACTION_MOVE_DOWN:
            return IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN) ||
                (IsGamepadAvailable(0) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.5f);
                   
        case ACTION_JUMP:
            return IsKeyPressed(KEY_SPACE) ||
                (IsGamepadAvailable(0) && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN));

        case ACTION_CONFIRM:
            return IsKeyPressed(KEY_ENTER) ||
                (IsGamepadAvailable(0) && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT));

        case ACTION_ESC:
            return IsKeyPressed(KEY_ESCAPE) ||
                (IsGamepadAvailable(0) && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT));
                
        case ACTION_F3:
            return IsKeyPressed(KEY_F3);
            
        case ACTION_TERMINAL:
            return IsKeyPressed(KEY_GRAVE);

        default:
            return false;
    }
}

bool InputManager::IsActionHeld(InputAction action) {
    switch (action) {
        case ACTION_MOVE_LEFT:
            return IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ||
                (IsGamepadAvailable(0) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.5f);

        case ACTION_MOVE_RIGHT:
            return IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ||
                (IsGamepadAvailable(0) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0.5f);

        case ACTION_MOVE_UP:
            return IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) ||
                (IsGamepadAvailable(0) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.5f);

        case ACTION_MOVE_DOWN:
            return IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ||
                (IsGamepadAvailable(0) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.5f);

        default:
            return false;
    }
}

char InputManager::KeyToChar(KeyboardKey key, bool shift)
{

    // Handle A-Z
    if (key >= KEY_A && key <= KEY_Z)
    {
        char base = shift ? 'A' : 'a';
        return base + (key - KEY_A); // map KEY_A to 'a' or 'A'
    }

    switch (key)
    {
        case KEY_ONE: return shift ? '!' : '1';
        case KEY_TWO: return shift ? '@' : '2';
        case KEY_THREE: return shift ? '#' : '3';
        case KEY_FOUR: return shift ? '$' : '4';
        case KEY_FIVE: return shift ? '%' : '5';
        case KEY_SIX: return shift ? '^' : '6';
        case KEY_SEVEN: return shift ? '&' : '7';
        case KEY_EIGHT: return shift ? '*' : '8';
        case KEY_NINE: return shift ? '(' : '9';
        case KEY_ZERO: return shift ? ')' : '0';
        case KEY_SPACE: return ' ';
        case KEY_COMMA: return shift ? '<' : ','; // Comma or Less-than
        case KEY_PERIOD: return shift ? '>' : '.'; // Period or Greater-than
        case KEY_SLASH: return shift ? '?' : '/'; // Slash or Question Mark
        case KEY_SEMICOLON: return shift ? ':' : ';'; // Semicolon or Colon
        case KEY_APOSTROPHE: return shift ? '"' : '\''; // Quote or Double Quote
        case KEY_LEFT_BRACKET: return shift ? '{' : '['; // Open Bracket or Curly Brace
        case KEY_RIGHT_BRACKET: return shift ? '}' : ']'; // Close Bracket or Curly Brace
        case KEY_BACKSLASH: return shift ? '|' : '\\'; // Pipe or Backslash
        case KEY_EQUAL: return shift ? '+' : '='; // Plus or Equal
        case KEY_MINUS: return shift ? '_' : '-'; // Underscore or Hyphen
    };
    
    return '\0';
}
