void CreateButton(int ButtonNum, int widthb, int heightb, int posx, int posy);
void ButtonActions(int ButtonNum, int ScreenNum, int Width, int Height);


int ButtonMain[4][20];

void CreateButton(int ButtonNum, int widthb, int heightb, int posx, int posy) {
    ButtonMain[0][ButtonNum] = posx; //x min
    ButtonMain[1][ButtonNum] = posx + widthb; //x max
    ButtonMain[3][ButtonNum] = posy; //y max
    ButtonMain[2][ButtonNum] = posy + heightb; //y min
}

void IsButtonClicked(int x, int y, int ScreenNum, int Width, int Height) {
    for(int i = 0; i < 20; i++) {
        if(ButtonMain[0][i] < x && ButtonMain[1][i] > x && ButtonMain[3][i] < y && ButtonMain[2][i] > y) {
            ButtonActions(i, ScreenNum, Width, Height);
        }
    }
}

void ResetButtons() {
    memset(ButtonMain, 0, sizeof(ButtonMain));
}