void CreateButton(int ButtonNum, int widthb, int heightb, int posx, int posy);
void DrawRectangle(int widthr, int heightr, int posx, int posy, char color[4]);
void DrawString(char* text, int FontSize, int widths, int heights, int posx, int posy, char color[4]);
void DrawTexture(char* file, int widtht, int heightt, int posx, int posy);
void NiceLookingButton(int widthnlb, int heightnlb, int posx, int posy, int fontsize, char* text, char BorderColor[4], char MiddleColor[4], char TextColor[4]);
void ChangeScreenNumber(int ScreenNum);
void ResetButtons();