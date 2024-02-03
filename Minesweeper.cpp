#include "iGraphics.h"
#include "Settings.cpp"
#include "Functions.cpp"

void showStat();
void printText();
void printText2();
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
        iShowBMP(menuX, resumeY - menuH, IMAGE[theme][1]); //resume
        iShowBMP(menuX, resumeY - 2*menuH - menuP, IMAGE[theme][2]); //newgame
        iShowBMP(menuX, resumeY - 3*menuH - 2*menuP, IMAGE[theme][3]); //settings
        iShowBMP(menuX, resumeY - 4*menuH - 3*menuP, IMAGE[theme][4]); //stats
        iShowBMP(menuX, resumeY - 5*menuH - 4*menuP, IMAGE[theme][5]); //about
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

    case STATISTICS:
        iShowBMP(0, 0, IMAGE[theme][24]); //statScreen
        iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
        iShowBMP(resetX, resetY, IMAGE[theme][14]); //reset
        iShowBMP(statX, statY, IMAGE[theme][26]); //statMedium
        iShowBMP(statX-statW-statP, statY, IMAGE[theme][25]); //statEasy
        iShowBMP(statX+statW+statP, statY, IMAGE[theme][27]); //statHard
        showStat();
        break;

    case ABOUT:
        iShowBMP(0, 0, IMAGE[theme][28]); //aboutScreen
        iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
        break;
    
    case IN_GAME:
        iShowBMP(0, 0, IMAGE[theme][0]); //background
        iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
        for (int i = 0; i < mode.col; i++){
            for (int j = 0; j < mode.row; j++){
                if (board[i][j].state == DEFAULT) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][3]); //blank
                else if (board[i][j].state == FLAGGED) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][0]); //flag
                else if (board[i][j].state == EXPOSED) showNum(i, j);
            }
        }
        printText();
        break;

    case GAME_WON:
        iShowBMP(0, 0, IMAGE[theme][0]); //background
        iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
        printText2();
        for (int i = 0; i < mode.col; i++){
            for (int j = 0; j < mode.row; j++){
                if (board[i][j].isMine)
                {
                    if (!animation) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][1]); // mine
                    else if (board[i][j].visited) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][1]); // mine
                    else iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][0]); //flag
                }
                else showNum(i, j);
            }
        }
        if (isRecord) iShowBMP(winX, winY, IMAGE[theme][12]); //newrecord
        else iShowBMP(winX, winY, IMAGE[theme][10]); //youwin
        break;

    case GAME_LOST:
        iShowBMP(0, 0, IMAGE[theme][0]); //background
        iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
        iShowBMP(winX, winY, IMAGE[theme][11]); //youlose
        for (int i = 0; i < mode.col; i++){
            for (int j = 0; j < mode.row; j++){
                if (board[i][j].isMine && board[i][j].visited) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][2]); //exmine
                else if (board[i][j].isMine && !board[i][j].visited) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][1]); //mine
                else if (board[i][j].state == FLAGGED) iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][0]); //flag
                else if (board[i][j].state == EXPOSED) showNum(i, j);
                else iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][3]); //blank
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
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY-2*menuH-2*menuP && my > menuY-3*menuH-2*menuP) gameState = STATISTICS, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY-3*menuH-3*menuP && my > menuY-4*menuH-3*menuP) gameState = ABOUT, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY-4*menuH-4*menuP && my > menuY-5*menuH-4*menuP) exitGame();
        break;

    case RESUME_MENU:
        if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY && my > resumeY-menuH) gameState = IN_GAME, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-menuH-menuP && my > resumeY-2*menuH-menuP) gameState = NEW_GAME, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-2*menuH-2*menuP && my > resumeY-3*menuH-2*menuP) gameState = SETTINGS, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-3*menuH-3*menuP && my > resumeY-4*menuH-3*menuP) gameState = STATISTICS, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-4*menuH-4*menuP && my > resumeY-5*menuH-4*menuP) gameState = ABOUT, playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-5*menuH-5*menuP && my > resumeY-6*menuH-5*menuP) exitGame();
        break;

    case SETTINGS:
        if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) gameState = (canResume ? RESUME_MENU : MAIN_MENU), playSound(7);
        else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY && my > menuY-menuH) theme = 1-theme, playSound(7);
        else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY-setH-setP && my > menuY-2*menuH-setP) music = !music, playSound(7);
        else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY-2*setH-2*setP && my > menuY-3*menuH-2*setP) autoChord = !autoChord, playSound(7);
        else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY-3*setH-3*setP && my > menuY-4*menuH-3*setP) animation = !animation, playSound(7);
        break;

    case STATISTICS:
        if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) gameState = (canResume ? RESUME_MENU : MAIN_MENU), playSound(7);
        else if (leftClick && mx > resetX && mx < resetX+statW && my > resetY && my < resetY+statH) resetStat(), playSound(7);
        else if (leftClick && mx > statX && mx < statX+statW && my > statY && my < statY+statH) curStat = 1, playSound(7);
        else if (leftClick && mx > statX-statW-statP && mx < statX-statP && my > statY && my < statY+statH) curStat = 0, playSound(7);
        else if (leftClick && mx > statX+statW+statP && mx < statX+2*statW+statP && my > statY && my < statY+statH) curStat = 2, playSound(7);
        break;

    case ABOUT:
        if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) gameState = (canResume ? RESUME_MENU : MAIN_MENU), playSound(7);
        break;
    
    case NEW_GAME:
        if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) gameState = (canResume ? RESUME_MENU : MAIN_MENU), playSound(7);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < newGameY && my > newGameY-menuH) setup(&EASY);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < newGameY-menuH-menuP && my > newGameY-2*menuH-menuP) setup(&MEDIUM);
        else if (leftClick && mx > menuX && mx < menuX+menuW && my < newGameY-2*menuH-2*menuP && my > newGameY-3*menuH-2*menuP) setup(&HARD);
        break;

    case IN_GAME:
        if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) gameState = (canResume ? RESUME_MENU : MAIN_MENU), playSound(7);
        else if ((leftClick || rightClick) && firstClick) safeFirstClick(mx, my, leftClick, rightClick);
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

int main(int argc, char **argv)
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
    iText(text1X, text1Y, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "Time: %d", _time);
    iText(text2X, text2Y, str, GLUT_BITMAP_TIMES_ROMAN_24);
}

void printText2()
{
    if (theme == 0) iSetColor(0, 0, 255);
    else iSetColor(255, 255, 255);

    sprintf(str, "Time: %d", _time);
    iText(text2X, text2Y, str, GLUT_BITMAP_TIMES_ROMAN_24);
}

void showStat()
{
    iSetColor(0, 0, 0);

    sprintf(str, "%03d", stats[curStat].gamesPlayed);
    iText(stat2X, stat2Y, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "%03d", stats[curStat].gamesWon);
    iText(stat2X, stat2Y-stat2P, str, GLUT_BITMAP_TIMES_ROMAN_24);

    int t = 0;
    if (stats[curStat].gamesPlayed) t = stats[curStat].gamesWon*100 / stats[curStat].gamesPlayed;
    sprintf(str, "%03d", t);
    iText(stat2X, stat2Y-2*stat2P, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "%03d", stats[curStat].maxWinning);
    iText(stat2X, stat2Y-3*stat2P, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "%03d", stats[curStat].maxLosing);
    iText(stat2X, stat2Y-4*stat2P, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "%03d", stats[curStat].currentWinning);
    iText(stat2X, stat2Y-5*stat2P, str, GLUT_BITMAP_TIMES_ROMAN_24);

    for (t = 0; t < 5; t++)
    {
        if (stats[curStat].score[t].score_ == __INT_MAX__) break;
        sprintf(str, "%03d %30s", stats[curStat].score[t].score_, stats[curStat].score[t].date_);
        iText(stat3X, stat3Y-t*stat3P, str, GLUT_BITMAP_TIMES_ROMAN_24);
    }

    sprintf(str, "---                 ------------");
    for (; t < 5; t++) iText(stat3X, stat3Y-t*stat3P, str, GLUT_BITMAP_TIMES_ROMAN_24);
}
