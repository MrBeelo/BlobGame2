#include "../headers/main/sounds.h"

Sounds::Sounds() {}
Sounds::~Sounds() {}

Sound Sounds::success;
Sound Sounds::jump;
Music Sounds::itsPizzaTime;

void Sounds::LoadContent()
{
    success = LoadSound("assets/sound/success.wav");
    jump = LoadSound("assets/sound/jump.wav");
    itsPizzaTime = LoadMusicStream("assets/sound/itsPizzaTime.mp3");
}

void Sounds::UnloadContent()
{
    UnloadSound(success);
    UnloadSound(jump);
}