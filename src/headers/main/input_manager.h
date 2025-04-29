#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "../raylib/raylib.h"
#include <string>

class InputManager
{
    public:
    enum InputAction {ACTION_MOVE_LEFT, ACTION_MOVE_RIGHT, ACTION_MOVE_UP, ACTION_MOVE_DOWN,
        ACTION_JUMP, ACTION_CONFIRM, ACTION_ESC, ACTION_F3, ACTION_TERMINAL };
    static bool IsActionPressed(InputAction action);
    static bool IsActionHeld(InputAction action);
    static char KeyToChar(KeyboardKey key, bool shift);

};

#endif