#include <time.h>
#include <stdlib.h>

#define PI 3.14159265358979323846
#define LIGHTSPEED 65535
#define HASMOVED 128

void ChangeSpaceDirection(int X, int Y);
void ChangeOoMVelocity(int Object);
void MoveSpace(int X, int Y);
void MoveOoMs(int Object);
char isNthBitSet (unsigned char c, int n);
void DrawRectangle(int widthr, int heightr, int posx, int posy, char color[4]);

const unsigned short SimSize[2] = {512, 512};

//EnergyTypes:   Velocity   Gravity   Charge--Anti-Charge   Color--Anti-Color
int SpaceEnergy[512][512][4];
unsigned char Space[512][512][4];
//HasMoved 0 - EnergyDirection 0x4
unsigned short OoMs[1024]; //Objects of Mass
//EnergyType 0x4 - Mass 0x12
float OoMPosition[1024][2];
short OoMEnergy[1024][2];
//DirectionX 0x16 - DirectionY 0x16


const signed char DirectionsXY[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

void InitializeSimSpace(int Amount) {
    srand(time(NULL));
    /**/
    for(int Y = 0; Y < SimSize[1]; Y+=Amount) {
        for(int X = 0; X < SimSize[0]; X+=Amount) {
            //Space[X][Y][0] = rand();
            //SpaceEnergy[X][Y][0] = rand();
        }
    }
}

void TickSimSpace() {
    //unsigned short HasMoved;
    for(int Y = 0; Y < SimSize[1] - 1; Y++) {
        for(int X = 0; X < SimSize[0] - 1; X++) {
            MoveSpace(X, Y);
        }
    }

    for(int Objects = 0; Objects < 1023; Objects++) {
        MoveOoMs(Objects);
    }
}

void ChangeOoMVelocity(int Object) {

}

void MoveOoMs(int Object) {
    float X = OoMEnergy[Object][0]/LIGHTSPEED;
    float Y = OoMEnergy[Object][1]/LIGHTSPEED;

    OoMPosition[Object][0] += X;
    OoMPosition[Object][1] += Y;

    for(int i = 0; i < 2; i++) {
        if(OoMPosition[Object][i] == 0) {
            OoMPosition[Object][i] = SimSize[i] - 1;
        }
        else if(OoMPosition[Object][i] >= SimSize[i]) {
            OoMPosition[Object][i] = 0;
        }
    }
}

void ChangeSpaceDirection(int X, int Y) {

}

void MoveSpace(int X, int Y) {
    unsigned int direction;
    int NewDirection[2], Energy;
    for(int i = 0; i < 4; i++) {
        if(Space[X][Y][i] < HASMOVED) {
            direction = Space[X][Y][i] << 4;
            direction = direction >> 4;
            if(direction > 8) {
                direction -= 8;
            }

            Energy = SpaceEnergy[X][Y][i];
            if(Energy != 0) {
                Energy = floor(Energy/3);

                NewDirection[0] = DirectionsXY[direction][0];
                NewDirection[1] = DirectionsXY[direction][1];

                unsigned int d[2];
                d[0] = X + NewDirection[0];
                d[1] = Y + NewDirection[1];
                //printf("%d, %d, %d\n", d[0], d[1], SimSize[0]);

                for(int r = 0; r < 2; r++) {
                    if(d[r] >= SimSize[r]) {
                        if(d[r] == 0) {
                            d[r] = SimSize[r] - 1;
                        }
                        else {
                            d[r] = 0;
                        }
                    }
                }

                SpaceEnergy[X][Y][i] = 0;
                Space[X][Y][i] = HASMOVED;

                SpaceEnergy[d[0]][d[1]][i] += Energy;
                SpaceEnergy[X][d[1]][i] += Energy;
                SpaceEnergy[d[0]][Y][i] += Energy;

                Space[d[0]][d[1]][i] += direction + HASMOVED;
                Space[X][d[1]][i] += direction + HASMOVED;
                Space[d[0]][Y][i] += direction + HASMOVED;
            }
        }
        else {
            Space[X][Y][i] -= HASMOVED;
        }
        
    }
}

void DrawParticals(int height, int Background) {
    for(int X = 0; X < SimSize[1]; X++) {
        for(int Y = 0; Y < SimSize[0]; Y++) {
            unsigned char r, b, a;
            if(Background) { 
                int f = SpaceEnergy[X][Y][Background - 1];
                if(f > 0) {
                    b = abs(f)/LIGHTSPEED;
                    r = 0;
                }
                else {
                    r = abs(f)/LIGHTSPEED;
                    b = 0;
                }
                a = abs(f)/LIGHTSPEED;
            }
            else { a = 0; }
            char color[4] = {r, 0, b, a};
            DrawRectangle(height/SimSize[0], height/SimSize[1], height/SimSize[0] * X, height/SimSize[1] * Y, color);
        }
    }

    for(int i = 0; i < 1023; i++) {
        int X = floor(OoMPosition[i][0]);
        int Y = floor(OoMPosition[i][1]);
        char color[4] = {255, 255, 255, 255};
        DrawRectangle(height/SimSize[0], height/SimSize[1], height/SimSize[0] * X, height/SimSize[1] * Y, color);
    }
}

char isNthBitSet (unsigned char c, int n) {
    static unsigned char mask[] = {128, 64, 32, 16, 8, 4, 2, 1};
    return ((c & mask[n]) != 0);
}