#include "../headers/main/input_manager.h"

bool InputManager::IsActionPressed(InputAction action) {
    switch (action) {
        case ACTION_MOVE_LEFT:
            return IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT) ||
                (IsAnyGamepadAvailable(16) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.5f);

        case ACTION_MOVE_RIGHT:
            return IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT) ||
                (IsAnyGamepadAvailable(16) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0.5f);

        case ACTION_MOVE_UP:
            return IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) ||
                (IsAnyGamepadAvailable(16) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.5f);

        case ACTION_MOVE_DOWN:
            return IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN) ||
                (IsAnyGamepadAvailable(16) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.5f);
                   
        case ACTION_JUMP:
            return IsKeyPressed(KEY_SPACE) ||
                (IsAnyGamepadAvailable(16) && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN));

        case ACTION_CONFIRM:
            return IsKeyPressed(KEY_ENTER) ||
                (IsAnyGamepadAvailable(16) && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT));

        case ACTION_ESC:
            return IsKeyPressed(KEY_ESCAPE) ||
                (IsAnyGamepadAvailable(16) && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT));
                
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
                (IsAnyGamepadAvailable(16) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.5f);

        case ACTION_MOVE_RIGHT:
            return IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ||
                (IsAnyGamepadAvailable(16) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0.5f);

        case ACTION_MOVE_UP:
            return IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) ||
                (IsAnyGamepadAvailable(16) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.5f);

        case ACTION_MOVE_DOWN:
            return IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ||
                (IsAnyGamepadAvailable(16) && GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.5f);

        default:
            return false;
    }
}

bool InputManager::IsAnyGamepadAvailable(int gamepads)
{
    for(int i = 0; i < gamepads; i++) {
        if(!IsGamepadAvailable(i)) continue;
        else if(IsGamepadAvailable(i)) return true; break;
    }
    
    return false;
}
