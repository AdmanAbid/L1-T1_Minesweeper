#pragma once
#include "Settings.cpp"

void setup(_difficulty *mode_);

void leftClickOnDefault(int i, int j);
void leftClickOnExposed(int i, int j);
void simulateGameplay(int mx, int my, bool leftClick, bool rightClick);
void safeFirstClick(int mx, int my, bool leftClick, bool rightClick);

void gameWonStatChange();
void gameLostStatChange();

void resetStat();
void getAllData();
void saveAllData();

void exitGame();
void deleteBoard();

void bfs();
void dfs(int i, int j);

void inGameTimer();
void winAnimation();
void playSound(int n);

int Qpop();
int Qsize();
void Qpush(int n);

void readUserData();
void freeUserData();
void checkUserPassword();
void addNewUser();
void deleteUser();

void readUserData();
void writeUserData();

void readUserStats();
void writeUserStats();

void setupLogin();
void generateBoard();
void generateMines();

void setup(_difficulty *mode_)
{
    playSound(6);
    mode = *mode_;
    firstClick = true;
    rowCount = mode.row;

    _time = 0;
    isRecord = false;
    canResume = true;
    front = 0, back = 0;
    flagged = 0, exposed = 0;

    generateBoard();
    generateMines();
    gameState = IN_GAME;
}

void generateBoard()
{
    deleteBoard();

    board = (_cell **)malloc(mode.col * sizeof(_cell *));
    for (int i = 0; i < mode.col; i++) {
        board[i] = (_cell *)malloc(mode.row * sizeof(_cell));
    }

    for (int i = 0; i < mode.col; i++)
    {
        for (int j = 0; j < mode.row; j++) 
        {
            board[i][j].num = 0;
            board[i][j].isMine = false;
            board[i][j].visited = false;
            board[i][j].state = DEFAULT;
        }
    }
}

void generateMines()
{
    srand((unsigned int)time(NULL));
    for (int n = 0; n < mode.mines; n++)
	{
		int i, j;
		do {
			i = rand() % mode.col, j = rand() % mode.row;
		} while (board[i][j].isMine);

		board[i][j].isMine = true;
		for (int k = 0; k < 8; k++)
		{
			int I = i + di[k], J = j + dj[k];
			if (I >= 0 && I < mode.col && J >= 0 && J < mode.row) {
                board[I][J].num++;
            }
		}
	}
}

void simulateGameplay(int mx, int my, bool leftClick, bool rightClick)
{
    int i = (mx - mode.x) / mode.w, j = (my - mode.y) / mode.w;
    if (leftClick && i >= 0 && i < mode.col && j >= 0 && j < mode.row)
    {
        if (board[i][j].state == DEFAULT) {
            playSound(2);
            leftClickOnDefault(i, j);
        }
        else if (board[i][j].state == EXPOSED && board[i][j].num != 0) {
            playSound(0);
            leftClickOnExposed(i, j);
        }
    }
    else if (rightClick && i >= 0 && i < mode.col && j >= 0 && j < mode.row)
    {
        if (board[i][j].state == DEFAULT)
        {
            playSound(4);
            flagged++;
            board[i][j].state = FLAGGED;

            if (autoChord)
            {
                for (int k = 0; k < 8; k++)
                {
                    int I = i + di[k], J = j + dj[k];
                    if (I >= 0 && I < mode.col && J >= 0 && J < mode.row && board[I][J].state == EXPOSED)
                    {
                        leftClickOnExposed(I, J);
                        if (gameState == GAME_LOST) break;
                    }
                }
            }
        }
        else if (board[i][j].state == FLAGGED)
        {
            flagged--, playSound(5);
            board[i][j].state = DEFAULT;
        }
    }
    if (exposed == mode.notMines)
    {
        playSound(8);
        canResume = false;
        gameWonStatChange();
        gameState = GAME_WON;
    }
}

void dfs(int i, int j)
{
	for (int k = 0; k < 8; k++)
	{
		int I = i + di[k], J = j + dj[k];
		if (I >= 0 && I < mode.col && J >= 0 && J < mode.row && board[I][J].state == DEFAULT) {
            exposed++;
			board[I][J].state = EXPOSED;
			if (board[I][J].num == 0) dfs(I, J);
		}
	}
}

void leftClickOnDefault(int i, int j)
{
    if (!board[i][j].isMine)
    {
        exposed++;
        board[i][j].state = EXPOSED;
        if (board[i][j].num == 0) dfs(i, j);
        if (autoChord) leftClickOnExposed(i, j);
    }
    else
    {
        canResume = false;
        gameLostStatChange();
        gameState = GAME_LOST;
        board[i][j].visited = true;
        if (animation) Qpush(i*30 + j);
        else playSound(3);
    }
}

void leftClickOnExposed(int i, int j)
{
    int flagCount = 0;
    for (int k = 0; k < 8; k++)
    {
        int I = i + di[k], J = j + dj[k];
        if (I >= 0 && I < mode.col && J >= 0 && J < mode.row && board[I][J].state == FLAGGED) flagCount++;
    }
    if (flagCount != board[i][j].num) return;

    for (int k = 0; k < 8; k++)
    {
        int I = i + di[k], J = j + dj[k];
        if (I >= 0 && I < mode.col && J >= 0 && J < mode.row && board[I][J].state == DEFAULT)
        {
            leftClickOnDefault(I, J);
            if (gameState == GAME_LOST) break;
        }
    }
}

void safeFirstClick(int mx, int my, bool leftClick, bool rightClick)
{
    int i = (mx - mode.x) / mode.w, j = (my - mode.y) / mode.w;
    if (i >= 0 && i < mode.col && j >= 0 && j < mode.row)
    {
        firstClick = false;
        if (leftClick && board[i][j].isMine)
        {
            int t = 0;
            while (board[t][mode.row-1].isMine && t < mode.col) t++;

            board[t][mode.row-1].isMine = true;
            for (int k = 0; k < 8; k++)
            {
                int I = t + di[k], J = mode.row-1 + dj[k];
                if (I >= 0 && I < mode.col && J >= 0 && J < mode.row) board[I][J].num++;
            }

            board[i][j].isMine = false;
            for (int k = 0; k < 8; k++)
            {
                int I = i + di[k], J = j + dj[k];
                if (I >= 0 && I < mode.col && J >= 0 && J < mode.row) board[I][J].num--;
            }
        }
    }
    simulateGameplay(mx, my, leftClick, rightClick);
}

void getAllData()
{
    readUserData();
    readUserStats();

    theme = userStats[curUser].settings.theme_;
    music = userStats[curUser].settings.music_;
    animation = userStats[curUser].settings.animation_;
    autoChord = userStats[curUser].settings.autoChord_;
}

void saveAllData()
{
    userStats[curUser].settings.theme_ = theme;
    userStats[curUser].settings.music_ = music;
    userStats[curUser].settings.animation_ = animation;
    userStats[curUser].settings.autoChord_ = autoChord;

    writeUserData();
    writeUserStats();
}

void gameWonStatChange()
{
    userStats[curUser].stats[mode.statVal].gamesWon++;
    userStats[curUser].stats[mode.statVal].gamesPlayed++;
    userStats[curUser].stats[mode.statVal].currentLosing = 0;
    if (++userStats[curUser].stats[mode.statVal].currentWinning > userStats[curUser].stats[mode.statVal].maxWinning) {
            userStats[curUser].stats[mode.statVal].maxWinning++;
        }

    int i;
    for (i = 0; i < 5; i++) if (_time < userStats[curUser].stats[mode.statVal].score[i].score_) break;

    if (i < 5)
    {
        isRecord = true;
        for (int j = 3; j >= i; j--) {
            userStats[curUser].stats[mode.statVal].score[j+1] = userStats[curUser].stats[mode.statVal].score[j];
        }
        userStats[curUser].stats[mode.statVal].score[i].score_ = _time;

        time_t time2;
        time(&time2);
        tm *time3 = localtime(&time2);

        char date[20];
        sprintf(date, "%02d-%02d-%d", time3->tm_mday, time3->tm_mon+1, time3->tm_year+1900);
        strcpy(userStats[curUser].stats[mode.statVal].score[i].date_, date);
    }
    writeUserStats();
}

void gameLostStatChange()
{
    userStats[curUser].stats[mode.statVal].gamesPlayed++;
    userStats[curUser].stats[mode.statVal].currentWinning = 0;
    if (++userStats[curUser].stats[mode.statVal].currentLosing > userStats[curUser].stats[mode.statVal].maxLosing) {
        userStats[curUser].stats[mode.statVal].maxLosing++;
    }
    writeUserStats();
}

void resetStat()
{
    userStats[curUser].stats[curStat].gamesPlayed = 0;
    userStats[curUser].stats[curStat].gamesWon = 0;
    userStats[curUser].stats[curStat].currentWinning = 0;
    userStats[curUser].stats[curStat].currentLosing = 0;
    userStats[curUser].stats[curStat].maxWinning = 0;
    userStats[curUser].stats[curStat].maxLosing = 0;
    for (int i = 0; i < 5; i++) {
        userStats[curUser].stats[curStat].score[i].score_ = __INT_MAX__;
    }
    writeUserStats();
}

void inGameTimer()
{
    _time++;
}

void Qpush(int n)
{
    queue[back++] = n;
}

int Qpop()
{
    return queue[front++];
}

int Qsize()
{
    return back - front;
}

void bfs()
{
    int size = Qsize();
    bool mine_ = false;

    while (size--)
    {
        int t = Qpop();
        int i = t / 30, j = t % 30;

        for (int k = 0; k < 8; k++)
        {
            int I = i + di[k], J = j + dj[k];
            if (I >= 0 && I < mode.col && J >= 0 && J < mode.row && !board[I][J].visited)
            {
                Qpush(I*30 + J);
                board[I][J].visited = true;
                if (board[I][J].isMine) mine_ = true;
            }
        }
    }
    if (mine_) playSound(3);
}

void winAnimation()
{
    if (rowCount)
    {
        rowCount--;
        for (int i = 0; i < mode.col; i++) board[i][rowCount].visited = true;
    }
}

void playSound(int n)
{
    if (music)
    {
        PlaySound(0, 0, 0);
        PlaySound(SOUND[n], NULL, SND_ASYNC);
    }
    if (n == 7) Sleep(100); //for better transition between screens
}

void deleteBoard()
{
    if (board)
    {
        for (int i = 0; i < mode.col; i++) free(board[i]);
        free(board);
        board = NULL;
    }
}

void exitGame()
{
    playSound(7);
    deleteBoard();
    saveAllData();
    freeUserData();
    if (music) Sleep(400); //to play exit sound
    exit(0);
}

void readUserData()
{
    free(userList);
    FILE *fp = fopen("UserData.txt", "rb");
    if (fp)
    {
        fread(&userCount, sizeof(int), 1, fp);
        userList = (_userData *)malloc(sizeof(_userData) * (userCount+1));
        fread(userList, sizeof(_userData), userCount, fp);
        fclose(fp);
    }
    else
    {
        printf("Error opening file for reading.\n");
        exit(1);
    }
}

void freeUserData()
{
    free(userList);
    free(userStats);
}

void checkUserPassword()
{
    for (int i = 0; i < userCount; i++)
    {
        if (!strcmp(name, userList[i]._name) && !strcmp(password, userList[i]._password))
        {
            name[0] = password[0] = password2[0] = 0;
            nameInd = passwordInd = 0;
            takingUserName = true, takingPassword = false;
            curUser = i;
            getAllData();
            gameState = MAIN_MENU;
            break;
        }
    }
}

void addNewUser()
{
    strcpy(userList[userCount]._name, name);
    strcpy(userList[userCount]._password, password);
    curUser = userCount;
    userCount++;

    userStats[curUser].settings.animation_ = animation;
    userStats[curUser].settings.autoChord_ = autoChord;
    userStats[curUser].settings.music_ = music;
    userStats[curUser].settings.theme_ = theme;

    for (int i = 0; i < 3; i++)
    {
        curStat = i;
        resetStat();
    }

    gameState = MAIN_MENU;
    name[0] = password[0] = password2[0] = 0;
    nameInd = passwordInd = 0;
    takingUserName = true, takingPassword = false;

    writeUserData();
    writeUserStats();

    readUserData();
    readUserStats();
}

void writeUserData()
{
    FILE *fp = fopen("UserData.txt", "wb");
    if (fp)
    {
        fwrite(&userCount, sizeof(int), 1, fp);
        fwrite(userList, sizeof(_userData), userCount, fp);
        fclose(fp);
    }
    else
    {
        printf("Error opening file for writing.\n");
        exit(1);
    }
}

void readUserStats()
{
    free(userStats);
    FILE *fp = fopen("GameData.txt", "rb");
    if (fp)
    {
        userStats = (_userStats *)malloc(sizeof(_userStats) * (userCount+1));
        fread(userStats, sizeof(_userStats), userCount, fp);
        fclose(fp);
    }
    else
    {
        printf("Error opening file for reading.\n");
        exit(1);
    }
}

void writeUserStats()
{
    FILE *fp = fopen("GameData.txt", "wb");
    if (fp)
    {
        fwrite(userStats, sizeof(_userStats), userCount, fp);
        fclose(fp);
    }
    else
    {
        printf("Error opening file for writing.\n");
        exit(1);
    }
}

void setupLogin()
{
    readUserData();
    readUserStats();

    theme = 1;
    music = false;
    animation = false;
    autoChord = false;
}

void deleteUser()
{
    for (int i = incUser+1; i < userCount; i++) {
        userStats[i-1] = userStats[i];
        userList[i-1] = userList[i];
    }
    userCount--;
}