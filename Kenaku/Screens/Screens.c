#include "ParticalScreen.c"
#include "StartScreen.c"

void ParticalScreenButtons(int ButtonNum);

int Opacity = 256;

void ButtonActions(int ButtonNum, int ScreenNum, int Width, int Height) {
    switch(ScreenNum) {
        case 0:
            StartScreenButtons(ButtonNum);
        break;
        case 1:
            
        break;
        case 2:
            ParticalScreenButtons(ButtonNum);
            if(ButtonNum == 0) {
                
            }
        break;
    }
}

void ReRenderScreen(int ScreenNum, int Width, int Height) {
     if(ScreenNum == 0) {
        DrawStartScreen(Width, Height);
     }

     if(ScreenNum == 1) {
        
     }

     if(ScreenNum == 2) {
        DrawParticalScreen(Width, Height);
     }
}

void RunAnimations(int Width, int Height) {

}