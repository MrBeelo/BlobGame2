#include "../headers/sound/sounds.h"

Sounds::Sounds() {}
Sounds::~Sounds() {}

Sound Sounds::success;
Sound Sounds::jump;

void Sounds::LoadContent()
{
    success = LoadSound("assets/sound/success.wav");
    jump = LoadSound("assets/sound/jump.wav");
}

void Sounds::UnloadContent()
{
    UnloadSound(success);
    UnloadSound(jump);
}