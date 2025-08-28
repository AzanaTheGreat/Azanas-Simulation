#include "ScreenTools.c"
#include "../Colors.c"

#define FONTSIZE 24

void DrawStartHomeTab();
void DrawStartSimulationsTab();

int SelectedTab = 0;

void StartScreenButtons(int ButtonNum) {
    switch(ButtonNum) {
        case 0:
            SelectedTab = 0;
        break;
        case 1:
            SelectedTab = 1;
        break;
    }
}

void CreateStartScreen(int Width, int Height) {
    ResetButtons();
    CreateButton(0, 250, 75, 25, 175);
    CreateButton(1, 250, 75, 25, 275);
}

void DrawStartScreen(int Width, int Height) {
    const int x = 25;
    const int y = 175;
    DrawRectangle(Width, Height, 0, 0, Black);

    DrawRectangle(300, Height, 0, 0, Black);
    DrawRectangle(5, Height, 300, 0, White);

    DrawString("Azana's", FONTSIZE, 175, 75, 5, 0, White);
    DrawString("Simulation", FONTSIZE, 290, 100, 5, 45, White);

    NiceLookingButton(250, 75, x, y, FONTSIZE, "Home         ", White, Black, White);
    NiceLookingButton(250, 75, x, y + 100, FONTSIZE, "Simulations", White, Black, White);
    NiceLookingButton(250, 75, x, y + 200, FONTSIZE, "Settings    ", White, Black, White);

    switch (SelectedTab) {
    case 0:
        DrawStartHomeTab();
    break;
    case 1:
        DrawStartSimulationsTab();
    break;
    
    default:
        DrawStartHomeTab();
    break;
    }
}

void DrawStartHomeTab() {
    DrawRectangle(25, 75, 275, 175, White);
    DrawRectangle(35, 65, 270, 180, Black);
}

void DrawStartSimulationsTab() {
    DrawRectangle(25, 75, 275, 275, White);
    DrawRectangle(35, 65, 270, 280, Black);
}