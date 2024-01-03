#include "iGraphics.h"
#include "settings.cpp"

void printText();
void showNum(int i, int j);

void iDraw()
{
    iClear();

    if (gameState == IN_GAME) iResumeTimer(t1);
    else iPauseTimer(t1);

    if (animation && gameState == GAME_LOST) iResumeTimer(t2);
    else iPauseTimer(t2);

    if (animation && gameState == GAME_WON) iResumeTimer(t3);
    else iPauseTimer(t3);

    switch (gameState)
    {
    case MAIN_MENU:
        iShowBMP(0, 0, IMAGE[theme][0]); //background
        iShowBMP(menuX, menuY - menuH, IMAGE[theme][2]); //newgame
        iShowBMP(menuX, menuY - 2*menuH - menuP, IMAGE[theme][3]); //settings
        iShowBMP(menuX, menuY - 3*menuH - 2*menuP, IMAGE[theme][4]); //stats
        iShowBMP(menuX, menuY - 4*menuH - 3*menuP, IMAGE[theme][5]); //about
        iShowBMP(menuX, menuY - 5*menuH - 4*menuP, IMAGE[theme][6]); //exit
        break;

    case RESUME_MENU:
        iShowBMP(0, 0, IMAGE[theme][0]); //background
        iShowBMP(menuX, resumeY - menuH, IMAGE[theme][1]); //newgame
        iShowBMP(menuX, resumeY - 2*menuH - menuP, IMAGE[theme][2]); //settings
        iShowBMP(menuX, resumeY - 3*menuH - 2*menuP, IMAGE[theme][3]); //stats
        iShowBMP(menuX, resumeY - 4*menuH - 3*menuP, IMAGE[theme][4]); //about
        iShowBMP(menuX, resumeY - 5*menuH - 4*menuP, IMAGE[theme][5]); //exit
        iShowBMP(menuX, resumeY - 6*menuH - 5*menuP, IMAGE[theme][6]); //exit
        break;

    case NEW_GAME:
        iShowBMP(0, 0, IMAGE[theme][0]); //background
        iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
        iShowBMP(menuX, newGameY - menuH, IMAGE[theme][7]); //easy
        iShowBMP(menuX, newGameY - 2*menuH - menuP, IMAGE[theme][8]); //medium
        iShowBMP(menuX, newGameY - 3*menuH - 2*menuP, IMAGE[theme][9]); //hard
        break;
    
    case SETTINGS:
        iShowBMP(0, 0, IMAGE[theme][0]); //background
        iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
        iShowBMP(setX, setY - setH, IMAGE[theme][15]); //theme
        iShowBMP(setX, setY - 2*setH - setP, IMAGE[theme][16]); //sound
        iShowBMP(setX, setY - 3*setH - 2*setP, IMAGE[theme][17]); //chord
        iShowBMP(setX, setY - 4*setH - 3*setP, IMAGE[theme][19]); //animation
        iShowBMP(setX2, setY - setH, IMAGE[theme][18]); //light/dark
        if (music) iShowBMP(setX2, setY - 2*setH - setP, IMAGE[theme][20]); //on
        else iShowBMP(setX2, setY - 2*setH - setP, IMAGE[theme][21]); //off
        if (autoChord) iShowBMP(setX2, setY - 3*setH - 2*setP, IMAGE[theme][23]); //auto
        else iShowBMP(setX2, setY - 3*setH - 2*setP, IMAGE[theme][22]); //click
        if (animation) iShowBMP(setX2, setY - 4*setH - 3*setP, IMAGE[theme][20]); //on
        else iShowBMP(setX2, setY - 4*setH - 3*setP, IMAGE[theme][21]); //off
        break;
    
    case IN_GAME:
        iShowBMP(0, 0, IMAGE[theme][0]); //background
        iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
        for (int i = 0; i < mode.row; i++){
            for (int j = 0; j < mode.col; j++){
                if (board[i][j].state == DEFAULT) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][3]);
                else if (board[i][j].state == FLAGGED) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][0]);
                else if (board[i][j].state == EXPOSED) showNum(i, j);
            }
        }
        printText();
        break;

    case GAME_WON:
        iShowBMP(0, 0, IMAGE[theme][0]); //background
        iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
        for (int i = 0; i < mode.row; i++){
            for (int j = 0; j < mode.col; j++){
                if (board[i][j].isMine)
                {
                    if (!animation) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][1]); // mine
                    else if (board[i][j].visited) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][1]); // mine
                    else iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][0]); //flag
                }
                else showNum(i, j);
            }
        }
        if (isRecord) iShowBMP(winX, winY, IMAGE[theme][12]);
        else iShowBMP(winX, winY, IMAGE[theme][10]);
        break;

    case GAME_LOST:
        iShowBMP(0, 0, IMAGE[theme][0]); //background
        iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
        iShowBMP(winX, winY, IMAGE[theme][11]);
        for (int i = 0; i < mode.row; i++){
            for (int j = 0; j < mode.col; j++){
                if (board[i][j].isMine && board[i][j].visited) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][2]); //exmine
                else if (board[i][j].isMine && !board[i][j].visited) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][1]); //mine
                else if (board[i][j].state == FLAGGED) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][0]);
                else if (board[i][j].state == EXPOSED) showNum(i, j);
                else iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][3]);
            }
        }
        break;
    }
}

void iMouse(int button, int state, int mx, int my)
{
    bool leftClick = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
    bool rightClick = (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN);

    switch(gameState)
    {
    case MAIN_MENU:
        if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY && my > menuY-menuH) gameState = NEW_GAME, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY-menuH-menuP && my > menuY-2*menuH-menuP) gameState = SETTINGS, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY-4*menuH-4*menuP && my > menuY-5*menuH-4*menuP) exitGame();
        break;

    case RESUME_MENU:
        if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY && my > resumeY-menuH) gameState = IN_GAME, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-menuH-menuP && my > resumeY-2*menuH-menuP) gameState = NEW_GAME, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-2*menuH-2*menuP && my > resumeY-3*menuH-2*menuP) gameState = SETTINGS, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-5*menuH-5*menuP && my > resumeY-6*menuH-5*menuP) exitGame();
        break;

    case SETTINGS:
        if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) gameState = (canResume ? RESUME_MENU : MAIN_MENU), playSound(7);
        else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY && my > menuY-menuH) theme = 1-theme, playSound(7);
        else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY-setH-setP && my > menuY-2*menuH-setP) music = !music, playSound(7);
        else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY-2*setH-2*setP && my > menuY-3*menuH-2*setP) autoChord = !autoChord, playSound(7);
        else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY-3*setH-3*setP && my > menuY-4*menuH-3*setP) animation = !animation, playSound(7);
        break;
    
    case NEW_GAME:
        if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) gameState = (canResume ? RESUME_MENU : MAIN_MENU), playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < newGameY && my > newGameY-menuH) setup(&EASY);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < newGameY-menuH-menuP && my > newGameY-2*menuH-menuP) setup(&MEDIUM);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < newGameY-2*menuH-2*menuP && my > newGameY-3*menuH-2*menuP) setup(&HARD);
        break;

    case IN_GAME:
        if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) gameState = (canResume ? RESUME_MENU : MAIN_MENU), playSound(7);
        else if (firstClick) safeFirstClick(mx, my, leftClick, rightClick);
        else simulate(mx, my, leftClick, rightClick);
        break;

    case GAME_WON:
    case GAME_LOST:
        if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) gameState = MAIN_MENU, playSound(7);
        break;
    }
}

void iMouseMove(int mx, int my) {}
void iKeyboard(unsigned char key) {}
void iSpecialKeyboard(unsigned char key) {}

int main()
{
    initiate();
    getSettings();
    iInitialize(screenWidth, screenHeight, "Minesweeper");
    return 0;
}

void showNum(int i, int j)
{
    switch(board[i][j].num)
    {
        case 0:
            iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][4]);
            break;
        case 1:
            iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][5]);
            break;
        case 2:
            iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][6]);
            break;
        case 3:
            iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][7]);
            break;
        case 4:
            iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][8]);
            break;
        case 5:
            iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][9]);
            break;
        case 6:
            iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][10]);
            break;
        case 7:
            iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][11]);
            break;
        case 8:
            iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][12]);
            break;
    }
}

void printText()
{
    if (theme == 0) iSetColor(0, 0, 255);
    else iSetColor(255, 255, 255);

    sprintf(str, "Mine: %d", mode.mines-flagged);
    iText(130, 710, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "Time: %d", _time);
    iText(1025, 710, str, GLUT_BITMAP_TIMES_ROMAN_24);
}