#include "../headers/screen/modifiers_screen.h"
#include "../headers/main/modifiers.h"

ModifiersScreen::ModifiersScreen() {}
ModifiersScreen::~ModifiersScreen() {}

void ModifiersScreen::Update() 
{
    button1.Update();
    button2.Update(); 
    button3.Update();
    button4.Update();
    button5.Update();
    
    label1 = std::string("NEED MORE SPEED") + (Modifiers::speedMod ? " (ON)" : " (OFF)");
    label2 = std::string("INVERSE") + (Modifiers::inverseMod ? " (ON)" : " (OFF)");
    label3 = std::string("TICK TOCK") + (Modifiers::tickTockMod ? " (ON)" : " (OFF)");
    label4 = std::string("LIGHTS OUT") + (Modifiers::lightsOutMod ? " (ON)" : " (OFF)");
    
    button1.text = label1.c_str();
    button2.text = label2.c_str();
    button3.text = label3.c_str();
    button4.text = label4.c_str();
    
    button1.size = button1.CalculateSizeDefault(label1.c_str());
    button2.size = button2.CalculateSizeDefault(label2.c_str());
    button3.size = button3.CalculateSizeDefault(label3.c_str());
    button4.size = button4.CalculateSizeDefault(label4.c_str());
    
    button1.pos = Screen::GetCenteredPosition(button1.size, {0, (buffer + button1.size.y) * button1.yIndex});
    button2.pos = Screen::GetCenteredPosition(button2.size, {0, (buffer + button2.size.y) * button2.yIndex});
    button3.pos = Screen::GetCenteredPosition(button3.size, {0, (buffer + button3.size.y) * button3.yIndex});
    button4.pos = Screen::GetCenteredPosition(button4.size, {0, (buffer + button4.size.y) * button4.yIndex});
    
    if(button1.IsClicked()) Modifiers::speedMod = !Modifiers::speedMod;
    if(button2.IsClicked()) Modifiers::inverseMod = !Modifiers::inverseMod;
    if(button3.IsClicked()) Modifiers::tickTockMod = !Modifiers::tickTockMod;
    if(button4.IsClicked()) Modifiers::lightsOutMod = !Modifiers::lightsOutMod;
    if(button5.IsClicked()) gameState = MAIN_MENU;
}

void ModifiersScreen::Draw()
{
    DrawCenteredTitle(0, WHITE);
    
    button1.Draw();
    button2.Draw();
    button3.Draw();
    button4.Draw();
    button5.Draw();
}