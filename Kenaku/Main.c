#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

//X11
#include <X11/Xlib.h> //for getting screen size

//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//Other Scripts
#include "Widgets.c" //Making Buttons Work
#include "Screens/Screens.c" //Making Screens Work

void IsButtonClicked(int x, int y, int ScreenNum, int Width, int Height);
void RunAnimations(int Width, int Height);
void InitiateWindow();
void Initiate();

int frames = 0;
char Exit = 0;
int width, height;
unsigned char ticks;
int ScreenNumber = 0;
int DesktopWidth, DesktopHeight;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
SDL_DisplayMode dm;
Uint32 Mouse;
SDL_Surface* surfaceMessage;
TTF_Font* font;
int MouseX, MouseY;

int main() {
    Initiate();
    while(1) {
        usleep(1);
        ticks++;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    Exit = 1;
                break;

                case SDL_MOUSEBUTTONDOWN:
                    Mouse = SDL_GetMouseState(&MouseX, &MouseY);
                    IsButtonClicked(MouseX, MouseY, ScreenNumber, DesktopWidth, DesktopHeight);
                break;

                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_EXPOSED) {
                        
                    }
                break;
            }
        }

        switch(ticks) {
            case 1:
                SDL_RenderClear(renderer);
                ReRenderScreen(ScreenNumber, DesktopWidth, DesktopHeight);
                SDL_RenderPresent(renderer);
            break;

            case 20:
                ticks = 0;
            break;
        }

        if(Exit == 1) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 0;
        }
    }

   return 0;
}

void InitiateWindow() {
    Display *display;
    Screen* scren;
    int screen;
    display = XOpenDisplay(NULL);
    screen = DefaultScreen(display);
    scren = ScreenOfDisplay(display, screen);
    DesktopWidth = WidthOfScreen(scren);
	DesktopHeight = HeightOfScreen(scren);

    window = SDL_CreateWindow("Azana's Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DesktopWidth, DesktopHeight, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    TTF_Init();
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Initiate() {
    InitiateWindow();
    CreateStartScreen(DesktopWidth, DesktopHeight);
    ReRenderScreen(ScreenNumber, DesktopWidth, DesktopHeight);
}

void ChangeScreenNumber(int ScreenNum) {
    ScreenNumber = ScreenNum;
}

//Everything is related to drawing on the screen from here on down

void DrawRectangle(int widthr, int heightr, int posx, int posy, char color[4]) {
    int Xmin = posx;
    int Xmax = posx + widthr;
    int Ymax = posy;
    int Ymin = posy + heightr;
    Sint16 vx[] = {Xmax, Xmax, Xmin, Xmin};
    Sint16 vy[] = {Ymax, Ymin, Ymin, Ymax};
    filledPolygonRGBA(renderer, vx, vy, 4, color[0], color[1], color[2], color[3]);
}

void DrawString(char* text, int FontSize, int widths, int heights, int posx, int posy, char color[4]) {
    font = TTF_OpenFont("OpenSans-Regular.ttf", FontSize);
    SDL_Color Color = {color[0], color[1], color[2], color[3]};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, Color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = posx;
    Message_rect.y = posy;
    Message_rect.w = widths;
    Message_rect.h = heights;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void DrawTexture(char* file, int widtht, int heightt, int posx, int posy) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, file);
    SDL_Rect texture_rect;
    texture_rect.x = posx;
    texture_rect.y = posy;
    texture_rect.w = widtht;
    texture_rect.h = heightt;
    SDL_RenderCopy(renderer, texture, NULL, &texture_rect);
    if(texture == NULL) {
        printf("Failed to load Texture\n");
    }
}

void NiceLookingButton(int widthnlb, int heightnlb, int posx, int posy, int fontsize, char* text, char BorderColor[4], char MiddleColor[4], char TextColor[4]) {
    DrawRectangle(widthnlb, heightnlb, posx, posy, BorderColor);
    DrawRectangle(widthnlb - 10, heightnlb - 10, posx + 5, posy + 5, MiddleColor);
    DrawString(text, fontsize, widthnlb - 20, heightnlb - 20, posx + 10, posy + 10, TextColor);
}

void RenderScreen(int PresentOrClear) {
    if(PresentOrClear) {
        SDL_RenderPresent(renderer);
    }
    else {
        SDL_RenderClear(renderer);
    }
}