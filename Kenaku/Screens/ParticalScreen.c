#include "ScreenTools.c"
#include "../Chemical/ParticalSim.c"

#define RUNSIM 1
#define STOPSIM 2

void InitializeSimSpace(int Amount);
char RunSim = 0;

void ParticalScreenButtons(int ButtonNum) {
    switch(ButtonNum) {
        case 0:
            ChangeScreenNumber(1);
        break;
        case 1:
            RunSim = 1;
        break;
        case 2:
            RunSim = 0;
        break;            
        case 3:
            InitializeSimSpace(32);
        break;
    }
}

void CreateParticalScreen(int Width, int Height) {
    ResetButtons();
    //CreateButton(0, 75, 25, Height, 0);
    CreateButton(3, 75, 25, Height, 90);
    CreateButton(RUNSIM, 75, 25, Height, 30);
    CreateButton(STOPSIM, 75, 25, Height, 60);
}

void DrawParticalScreen(int Width, int Height) {
    char Black[4] = {0, 0, 0, 0};
    DrawRectangle(Width, Height, 0, 0, Black);
    char White[4] = {255, 255, 255, 255};
    DrawRectangle(75, 25, Height, 0, White);
    DrawRectangle(75, 25, Height, 90, White);
    DrawRectangle(75, 25, Height, 30, White);
    DrawRectangle(75, 25, Height, 60, White);
}