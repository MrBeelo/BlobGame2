#include "../headers/main/sounds.h"

Sounds::Sounds() {}
Sounds::~Sounds() {}

Sound Sounds::success;
Sound Sounds::jump;
Music Sounds::itsPizzaTime;
Music Sounds::menuMusic;
Music Sounds::tutorialMusic;

void Sounds::LoadContent()
{
    success = LoadSound("assets/sound/success.wav");
    jump = LoadSound("assets/sound/jump.wav");
    itsPizzaTime = LoadMusicStream("assets/sound/itsPizzaTime.mp3");
    menuMusic = LoadMusicStream("assets/sound/menuMusic.mp3");
    tutorialMusic = LoadMusicStream("assets/sound/tutorialMusic.mp3");
}

void Sounds::UnloadContent()
{
    UnloadSound(success);
    UnloadSound(jump);
    UnloadMusicStream(itsPizzaTime);
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(tutorialMusic);
}