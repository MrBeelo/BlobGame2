#ifndef TERMINAL_H
#define TERMINAL_H

#include "../raylib/raylib.h"
#include "../main/globals.hpp"
#include "../sprite/player.h"
#include <string>

class Terminal
{
    public:
    Terminal();
    ~Terminal();
    void Update(Player *player);
    void Draw();
    std::string text = "";
    void HandleText();
    const Rectangle rect = {buffer, simulationSize.y - buffer * 6 - buffer, simulationSize.x - buffer * 2, buffer * 6};
};

#endif