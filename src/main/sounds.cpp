#include "../headers/main/sounds.h"

Sounds::Sounds() {}
Sounds::~Sounds() {}

Sound Sounds::success;
Sound Sounds::jump;
Sound Sounds::lSwitch;
Music Sounds::itsPizzaTime;
Music Sounds::menuMusic;
Music Sounds::tutorialMusic;

void Sounds::LoadContent()
{
    success = LoadSound("assets/sound/success.wav");
    jump = LoadSound("assets/sound/jump.wav");
    lSwitch = LoadSound("assets/sound/switch.wav");
    itsPizzaTime = LoadMusicStream("assets/sound/itsPizzaTime.mp3");
    menuMusic = LoadMusicStream("assets/sound/menuMusic.mp3");
    tutorialMusic = LoadMusicStream("assets/sound/tutorialMusic.mp3");
}

void Sounds::UnloadContent()
{
    UnloadSound(success);
    UnloadSound(jump);
    UnloadSound(lSwitch);
    UnloadMusicStream(itsPizzaTime);
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(tutorialMusic);
}
