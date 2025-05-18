#include "../headers/main/sounds.h"

Sounds::Sounds() {}
Sounds::~Sounds() {}

Sound Sounds::success;
Sound Sounds::jump;
Sound Sounds::boing;
Sound Sounds::lSwitch;
Sound Sounds::fredBoop;
Music Sounds::itsPizzaTime;
Music Sounds::menuMusic;
Music Sounds::tutorialMusic;

void Sounds::LoadContent()
{
    success = LoadSound("assets/sound/success.wav");
    jump = LoadSound("assets/sound/jump.wav");
    boing = LoadSound("assets/sound/boing.wav");
    lSwitch = LoadSound("assets/sound/switch.wav");
    fredBoop = LoadSound("assets/sound/boop.wav");
    itsPizzaTime = LoadMusicStream("assets/sound/itsPizzaTime.mp3");
    menuMusic = LoadMusicStream("assets/sound/menuMusic.mp3");
    tutorialMusic = LoadMusicStream("assets/sound/tutorialMusic.mp3");
}

void Sounds::UnloadContent()
{
    UnloadSound(success);
    UnloadSound(jump);
    UnloadSound(boing);
    UnloadSound(lSwitch);
    UnloadSound(fredBoop);
    UnloadMusicStream(itsPizzaTime);
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(tutorialMusic);
}
