#include "iGraphics.h"
#include "Settings.cpp"
#include "Functions.cpp"

bool leftClick, rightClick;

void showStat();
void controlTimers();
void showFinalTime();
void showNum(int i, int j);
void showTimeAndMineLeft();

void showMainMenu();
void showResumeMenu();
void showLoginScreen();
void showNewGameScreen();
void showRegisterScreen();
void showSettingsScreen();
void showStatisticsScreen();
void showAboutScreen();
void showInGameScreen();
void showGameWonScreen();
void showGameLostScreen();

void simulateLogIn(int mx, int my);
void simulateRegister(int mx, int my);
void simulateMainMenu(int mx, int my);
void simulateResumeMenu(int mx, int my);
void simulateSettings(int mx, int my);
void simulateStatistics(int mx, int my);
void simulateAbout(int mx, int my);
void simulateNewGame(int mx, int my);
void simulateInGame(int mx, int my);
void simulateGameOver(int mx, int my);


void iDraw()
{
    iClear();
    controlTimers();

    switch (gameState)
    {
        case LOG_IN:
            showLoginScreen();
            if (!takingPassword && !takingUserName) {
                checkUserPassword();
            }
            break;

        case REGISTER:
            showRegisterScreen();
            if (!takingPassword && !takingUserName) {
                addNewUser();
            }
            break;

        case MAIN_MENU:
            showMainMenu();
            break;

        case RESUME_MENU:
            showResumeMenu();
            break;

        case NEW_GAME:
            showNewGameScreen();
            break;
        
        case SETTINGS:
            showSettingsScreen();
            break;

        case STATISTICS:
            showStatisticsScreen();
            break;

        case ABOUT:
            showAboutScreen();
            break;
        
        case IN_GAME:
            showInGameScreen();
            break;

        case GAME_WON:
            showGameWonScreen();
            break;

        case GAME_LOST:
            showGameLostScreen();
            break;
    }
}

void iMouse(int button, int state, int mx, int my)
{
    leftClick = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
    rightClick = (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN);

    switch(gameState)
    {
        case LOG_IN:
            simulateLogIn(mx, my);
            break;

        case REGISTER:
            simulateRegister(mx, my);
            break;

        case MAIN_MENU:
            simulateMainMenu(mx, my);
            break;

        case RESUME_MENU:
            simulateResumeMenu(mx, my);
            break;

        case SETTINGS:
            simulateSettings(mx, my);
            break;

        case STATISTICS:
            simulateStatistics(mx, my);
            break;

        case ABOUT:
            simulateAbout(mx, my);
            break;
        
        case NEW_GAME:
            simulateNewGame(mx, my);
            break;

        case IN_GAME:
            simulateInGame(mx, my);
            break;

        case GAME_WON:
        case GAME_LOST:
            simulateGameOver(mx, my);
            break;
    }
}

void iKeyboard(unsigned char key)
{
    if (takingUserName) 
    {
        if (key == '\r') {
            takingUserName = false;
            takingPassword = true;
        }
        else if (key == '\b') {
            nameInd--;
            if (nameInd < 0) nameInd = 0;
            name[nameInd] = 0;
        }
        else if (nameInd < 24) {
            name[nameInd++] = key;
            name[nameInd] = 0;
        }
    }

    else if (takingPassword) 
    {
        if (key == '\r') {
            takingPassword = false;
        }
        else if (key == '\b') {
            passwordInd--;
            if (passwordInd < 0) passwordInd = 0;
            password[passwordInd] = password2[passwordInd] = 0;
        }
        else if (passwordInd < 24) {
            password[passwordInd] = key;
            password2[passwordInd] = '*';
            passwordInd++;
            password[passwordInd] = password2[passwordInd] = 0;
        }
    }
}


void iSpecialKeyboard(unsigned char key){}
void iMouseMove(int mx, int my) {}


int main(int argc, char **argv)
{
    initiateGame();
    setupLogin();
    iInitialize(screenWidth, screenHeight, "Minesweeper");
    return 0;
}

void controlTimers()
{
    if (gameState == IN_GAME) iResumeTimer(t1);
    else iPauseTimer(t1);

    if (animation && gameState == GAME_LOST) iResumeTimer(t2);
    else iPauseTimer(t2);

    if (animation && gameState == GAME_WON) iResumeTimer(t3);
    else iPauseTimer(t3);
}

void showLoginScreen()
{
    iShowBMP(0, 0, IMAGE[theme][29]); //login page
    iShowBMP(loginX, loginY, IMAGE[theme][31]); //register
    iShowBMP(registerX, registerY, IMAGE[theme][32]); //register
    iShowBMP(exitX, exitY, IMAGE[theme][6]); //exit
    iShowBMP2(dot1X, dot1Y, IMAGE[theme][37], 0); // dot

    if (takingUserName) {
        iShowBMP2(pointerX, pointerY1, IMAGE[theme][30], 0); //pointer
    }
    if (takingPassword) {
        iShowBMP2(pointerX, pointerY2, IMAGE[theme][30], 0); //pointer
    }

    iSetColor(0, 0, 0);
    iText(nameX, nameY, name, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(passwordX, passwordY, password2, GLUT_BITMAP_TIMES_ROMAN_24);
}

void showRegisterScreen()
{
    iShowBMP(0, 0, IMAGE[theme][29]); //login page
    iShowBMP(loginX, loginY, IMAGE[theme][31]); //login
    iShowBMP(registerX, registerY, IMAGE[theme][32]); //register
    iShowBMP(exitX, exitY, IMAGE[theme][6]); //exit
    iShowBMP2(dot2X, dot1Y, IMAGE[theme][37], 0); // dot

    if (takingUserName) {
        iShowBMP2(pointerX, pointerY1, IMAGE[theme][30], 0); //pointer
    }
    if (takingPassword) {
        iShowBMP2(pointerX, pointerY2, IMAGE[theme][30], 0); //pointer
    }

    iSetColor(0, 0, 0);
    iText(nameX, nameY, name, GLUT_BITMAP_TIMES_ROMAN_24);
    iText(passwordX, passwordY, password2, GLUT_BITMAP_TIMES_ROMAN_24);
}

void showMainMenu()
{
    iShowBMP(0, 0, IMAGE[theme][0]); //background
    iShowBMP(menuX, menuY - menuH, IMAGE[theme][2]); //newgame
    iShowBMP(menuX, menuY - 2*menuH - menuP, IMAGE[theme][3]); //settings
    iShowBMP(menuX, menuY - 3*menuH - 2*menuP, IMAGE[theme][4]); //stats
    iShowBMP(menuX, menuY - 4*menuH - 3*menuP, IMAGE[theme][5]); //about
    iShowBMP(menuX, menuY - 5*menuH - 4*menuP, IMAGE[theme][33]); //logout
    iShowBMP(menuX, menuY - 6*menuH - 5*menuP, IMAGE[theme][6]); //exit
}

void showResumeMenu()
{
    iShowBMP(0, 0, IMAGE[theme][0]); //background
    iShowBMP(menuX, resumeY - menuH, IMAGE[theme][1]); //resume
    iShowBMP(menuX, resumeY - 2*menuH - menuP, IMAGE[theme][2]); //newgame
    iShowBMP(menuX, resumeY - 3*menuH - 2*menuP, IMAGE[theme][3]); //settings
    iShowBMP(menuX, resumeY - 4*menuH - 3*menuP, IMAGE[theme][4]); //stats
    iShowBMP(menuX, resumeY - 5*menuH - 4*menuP, IMAGE[theme][5]); //about
    iShowBMP(menuX, resumeY - 6*menuH - 5*menuP, IMAGE[theme][33]); //logout
    iShowBMP(menuX, resumeY - 7*menuH - 6*menuP, IMAGE[theme][6]); //exit
}

void showStatisticsScreen()
{
    iShowBMP(0, 0, IMAGE[theme][24]); //statScreen
    iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
    iShowBMP(statX, statY, IMAGE[theme][26]); //statMedium
    iShowBMP(statX-statW-statP, statY, IMAGE[theme][25]); //statEasy
    iShowBMP(statX+statW+statP, statY, IMAGE[theme][27]); //statHard

    int dotx;
    if (curStat == 0) dotx = dotS1X;
    else if (curStat == 1) dotx = dotS2X;
    else dotx = dotS3X;

    iShowBMP2(dotx, dotSY, IMAGE[theme][37], 0); // dot

    if (incUser == 0) {
        iShowBMP(resetX, resetY, IMAGE[theme][14]); //reset
    }
    if (curUser == 0 && incUser != 0) {
        iShowBMP(resetX, resetY, IMAGE[theme][36]); //delete
    }
    if (curUser+incUser > 0) {
        iShowBMP2(50, 650, IMAGE[theme][35], 0); //leftarrow
    }
    if (curUser+incUser < userCount-1) {
        iShowBMP2(1100, 650, IMAGE[theme][34], 0); //rightarrow
    }

    showStat();
}

void showNewGameScreen()
{
    iShowBMP(0, 0, IMAGE[theme][0]); //background
    iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
    iShowBMP(menuX, newGameY - menuH, IMAGE[theme][7]); //easy
    iShowBMP(menuX, newGameY - 2*menuH - menuP, IMAGE[theme][8]); //medium
    iShowBMP(menuX, newGameY - 3*menuH - 2*menuP, IMAGE[theme][9]); //hard
}

void showSettingsScreen()
{
    iShowBMP(0, 0, IMAGE[theme][0]); //background
    iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
    iShowBMP(setX, setY - setH, IMAGE[theme][15]); //theme
    iShowBMP(setX, setY - 2*setH - setP, IMAGE[theme][16]); //sound
    iShowBMP(setX, setY - 3*setH - 2*setP, IMAGE[theme][17]); //chord
    iShowBMP(setX, setY - 4*setH - 3*setP, IMAGE[theme][19]); //animation
    iShowBMP(setX2, setY - setH, IMAGE[theme][18]); //light/dark

    if (music) {
        iShowBMP(setX2, setY - 2*setH - setP, IMAGE[theme][20]); //on
    } else {
        iShowBMP(setX2, setY - 2*setH - setP, IMAGE[theme][21]); //off
    }
    if (autoChord) {
        iShowBMP(setX2, setY - 3*setH - 2*setP, IMAGE[theme][23]); //auto
    } else {
        iShowBMP(setX2, setY - 3*setH - 2*setP, IMAGE[theme][22]); //click
    }
    if (animation) {
        iShowBMP(setX2, setY - 4*setH - 3*setP, IMAGE[theme][20]); //on
    } else {
        iShowBMP(setX2, setY - 4*setH - 3*setP, IMAGE[theme][21]); //off
    }
}

void showAboutScreen()
{
    iShowBMP(0, 0, IMAGE[theme][28]); //aboutScreen
    iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
}

void showInGameScreen()
{
    iShowBMP(0, 0, IMAGE[theme][0]); //background
    iShowBMP(homeX, homeY, IMAGE[theme][13]); //home

    for (int i = 0; i < mode.col; i++) 
    {
        for (int j = 0; j < mode.row; j++) 
        {
            if (board[i][j].state == DEFAULT) {
                iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][3]); //blank
            }
            else if (board[i][j].state == FLAGGED) {
                iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][0]); //flag
            }
            else if (board[i][j].state == EXPOSED) {
                showNum(i, j);
            }
        }
    }
    showTimeAndMineLeft();
}

void showGameWonScreen()
{
    iShowBMP(0, 0, IMAGE[theme][0]); //background
    iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
    showFinalTime();

    for (int i = 0; i < mode.col; i++)
    {
        for (int j = 0; j < mode.row; j++)
        {
            if (board[i][j].isMine)
            {
                if (!animation) {
                    iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][1]); // mine
                }
                else if (board[i][j].visited) {
                    iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][1]); // mine
                }
                else {
                    iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][0]); //flag
                }
            }
            else {
                showNum(i, j);
            }
        }
    }
    if (isRecord) {
        iShowBMP(winX, winY, IMAGE[theme][12]); //newrecord
    } else {
        iShowBMP(winX, winY, IMAGE[theme][10]); //youwin
    }
}

void showGameLostScreen()
{
    iShowBMP(0, 0, IMAGE[theme][0]); //background
    iShowBMP(homeX, homeY, IMAGE[theme][13]); //home
    iShowBMP(winX, winY, IMAGE[theme][11]); //youlose

    for (int i = 0; i < mode.col; i++)
    {
        for (int j = 0; j < mode.row; j++)
        {
            if (board[i][j].isMine && board[i][j].visited) {
                iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][2]); //exmine
            }
            else if (board[i][j].isMine && !board[i][j].visited) {
                iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][1]); //mine
            }
            else if (board[i][j].state == FLAGGED) {
                iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][0]); //flag
            }
            else if (board[i][j].state == EXPOSED) {
                showNum(i, j);
            }
            else {
                iShowBMP(mode.x+mode.w*i, mode.y+mode.w*j, mode.image[theme][3]); //blank
            }
        }
    }
}

void simulateLogIn(int mx, int my)
{
    if (leftClick && mx > registerX && mx < registerX+loginW && my > registerY && my < registerY+loginH) {
        name[0] = password[0] = password2[0] = 0;
        nameInd = passwordInd = 0;
        takingUserName = true;
        takingPassword = false;
        gameState = REGISTER;
    }
    else if (leftClick && mx > nameBoxX && mx < nameBoxX2 && my > nameBoxY && my < nameBoxY2) {
        takingUserName = true, takingPassword = false;
    }
    else if (leftClick && mx > nameBoxX && mx < nameBoxX2 && my > passwordBoxY && my < passwordBoxY2) {
        takingPassword = true, takingUserName = false;
    }
    else if (leftClick && mx > exitX && mx < exitX+exitW && my > exitY && my < exitY+exitH) {
        exitGame();
    }
}

void simulateRegister(int mx, int my)
{
    if (leftClick && mx > loginX && mx < loginX+loginW && my > loginY && my < loginY+loginH) {
        name[0] = password[0] = password2[0] = 0;
        nameInd = passwordInd = 0;
        takingUserName = true;
        takingPassword = false;
        gameState = LOG_IN;
    }
    else if (leftClick && mx > nameBoxX && mx < nameBoxX2 && my > nameBoxY && my < nameBoxY2) {
        takingUserName = true;
        takingPassword = false;
    }
    else if (leftClick && mx > nameBoxX && mx < nameBoxX2 && my > passwordBoxY && my < passwordBoxY2) {
        takingPassword = true;
        takingUserName = false;
    }
    else if (leftClick && mx > exitX && mx < exitX+exitW && my > exitY && my < exitY+exitH) {
        exitGame();
    }
}

void simulateMainMenu(int mx, int my)
{
    if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY && my > menuY-menuH) {
        gameState = NEW_GAME;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY-menuH-menuP && my > menuY-2*menuH-menuP) {
        gameState = SETTINGS;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY-2*menuH-2*menuP && my > menuY-3*menuH-2*menuP) {
        incUser = 0;
        curStat = 0;
        gameState = STATISTICS;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY-3*menuH-3*menuP && my > menuY-4*menuH-3*menuP) {
        gameState = ABOUT;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY-4*menuH-4*menuP && my > menuY-5*menuH-4*menuP) {
        saveAllData();
        gameState = LOG_IN;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < menuY-5*menuH-5*menuP && my > menuY-6*menuH-5*menuP) {
        exitGame();
    }
}

void simulateResumeMenu(int mx, int my)
{
    if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY && my > resumeY-menuH) {
        gameState = IN_GAME;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-menuH-menuP && my > resumeY-2*menuH-menuP) {
        gameState = NEW_GAME;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-2*menuH-2*menuP && my > resumeY-3*menuH-2*menuP) {
        gameState = SETTINGS;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-3*menuH-3*menuP && my > resumeY-4*menuH-3*menuP) {
        incUser = 0;
        curStat = 0;
        gameState = STATISTICS;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-4*menuH-4*menuP && my > resumeY-5*menuH-4*menuP) {
        gameState = ABOUT;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-5*menuH-5*menuP && my > resumeY-6*menuH-5*menuP) {
        saveAllData();
        gameState = LOG_IN;
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < resumeY-6*menuH-6*menuP && my > resumeY-7*menuH-6*menuP) {
        exitGame();
    }
}

void simulateSettings(int mx, int my)
{
    if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) {
        gameState = (canResume ? RESUME_MENU : MAIN_MENU);
        playSound(7);
    }
    else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY && my > menuY-menuH) {
        theme = 1-theme;
        playSound(7);
    }
    else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY-setH-setP && my > menuY-2*menuH-setP) {
        music = !music;
        playSound(7);
    }
    else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY-2*setH-2*setP && my > menuY-3*menuH-2*setP) {
        autoChord = !autoChord;
        playSound(7);
    }
    else if (leftClick && mx > setX2 && mx < setX2+setW && my < setY-3*setH-3*setP && my > menuY-4*menuH-3*setP) {
        animation = !animation;
        playSound(7);
    }
}

void simulateStatistics(int mx, int my)
{
    if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) {
        gameState = (canResume ? RESUME_MENU : MAIN_MENU);
        playSound(7);
    }
    else if (leftClick && incUser == 0 && mx > resetX && mx < resetX+statW && my > resetY && my < resetY+statH) {
        resetStat();
        playSound(7);
    }
    else if (leftClick && mx > statX && mx < statX+statW && my > statY && my < statY+statH) {
        curStat = 1;
        playSound(7);
    }
    else if (leftClick && mx > statX-statW-statP && mx < statX-statP && my > statY && my < statY+statH) {
        curStat = 0;
        playSound(7);
    }
    else if (leftClick && mx > statX+statW+statP && mx < statX+2*statW+statP && my > statY && my < statY+statH) {
        curStat = 2;
        playSound(7);
    }
    else if (leftClick && curUser+incUser > 0 && 
            mx > leftarrowX && mx < leftarrowX+arrowW && my > arrowY && my < arrowY+arrowW) {
        incUser--;
    }
    else if (leftClick && curUser+incUser < userCount-1 && 
            mx > rightarrowX && mx < rightarrowX+arrowW && my > arrowY && my < arrowY+arrowW) {
        incUser++;
    }
    if (leftClick && curUser == 0 && incUser != 0 && mx > resetX && mx < resetX+statW && my > resetY && my < resetY+statH) {
        deleteUser(); 
    }
}

void simulateAbout(int mx, int my)
{
    if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) {
        gameState = (canResume ? RESUME_MENU : MAIN_MENU);
        playSound(7);
    }
}

void simulateNewGame(int mx, int my)
{
    if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) {
        gameState = (canResume ? RESUME_MENU : MAIN_MENU);
        playSound(7);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < newGameY && my > newGameY-menuH) {
        setup(&EASY);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < newGameY-menuH-menuP && my > newGameY-2*menuH-menuP) {
        setup(&MEDIUM);
    }
    else if (leftClick && mx > menuX && mx < menuX+menuW && my < newGameY-2*menuH-2*menuP && my > newGameY-3*menuH-2*menuP) {
        setup(&HARD);
    }
}

void simulateInGame(int mx, int my)
{
    if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) {
        gameState = (canResume ? RESUME_MENU : MAIN_MENU);
        playSound(7);
    }
    else if ((leftClick || rightClick) && firstClick) {
        safeFirstClick(mx, my, leftClick, rightClick);
    }
    else {
        simulateGameplay(mx, my, leftClick, rightClick);
    }
}

void simulateGameOver(int mx, int my)
{
    if (leftClick && mx > homeX && mx < homeX+homeW && my > homeY && my < homeY+homeW) {
        gameState = MAIN_MENU;
        playSound(7);
    }
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

void showTimeAndMineLeft()
{
    if (theme == 0) iSetColor(0, 0, 255);
    else iSetColor(255, 255, 255);

    sprintf(str, "Mine: %d", mode.mines-flagged);
    iText(text1X, text1Y, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "Time: %d", _time);
    iText(text2X, text2Y, str, GLUT_BITMAP_TIMES_ROMAN_24);
}

void showFinalTime()
{
    if (theme == 0) iSetColor(0, 0, 255);
    else iSetColor(255, 255, 255);

    sprintf(str, "Time: %d", _time);
    iText(text2X, text2Y, str, GLUT_BITMAP_TIMES_ROMAN_24);
}

void showStat()
{
    iSetColor(0, 0, 0);

    int len = strlen(userList[curUser+incUser]._name);
    int Dx = (12.0 - (len / 2.0)) * 12.5;

    iText(nameBox2X + Dx, nameBox2Y, userList[curUser+incUser]._name, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "%03d", userStats[curUser+incUser].stats[curStat].gamesPlayed);
    iText(stat2X, stat2Y, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "%03d", userStats[curUser+incUser].stats[curStat].gamesWon);
    iText(stat2X, stat2Y-stat2P, str, GLUT_BITMAP_TIMES_ROMAN_24);

    int t = 0;
    if (userStats[curUser+incUser].stats[curStat].gamesPlayed) {
        t = userStats[curUser+incUser].stats[curStat].gamesWon*100 / userStats[curUser+incUser].stats[curStat].gamesPlayed;
    }
    sprintf(str, "%03d", t);
    iText(stat2X, stat2Y-2*stat2P, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "%03d", userStats[curUser+incUser].stats[curStat].maxWinning);
    iText(stat2X, stat2Y-3*stat2P, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "%03d", userStats[curUser+incUser].stats[curStat].maxLosing);
    iText(stat2X, stat2Y-4*stat2P, str, GLUT_BITMAP_TIMES_ROMAN_24);

    sprintf(str, "%03d", userStats[curUser+incUser].stats[curStat].currentWinning);
    iText(stat2X, stat2Y-5*stat2P, str, GLUT_BITMAP_TIMES_ROMAN_24);

    for (t = 0; t < 5; t++)
    {
        if (userStats[curUser+incUser].stats[curStat].score[t].score_ == __INT_MAX__) break;
        sprintf(str, "%03d %30s", userStats[curUser+incUser].stats[curStat].score[t].score_, 
                                  userStats[curUser+incUser].stats[curStat].score[t].date_);
        iText(stat3X, stat3Y-t*stat3P, str, GLUT_BITMAP_TIMES_ROMAN_24);
    }

    sprintf(str, "---                 ------------");
    for (; t < 5; t++) iText(stat3X, stat3Y-t*stat3P, str, GLUT_BITMAP_TIMES_ROMAN_24);
}
