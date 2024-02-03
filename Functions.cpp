#pragma once
#include "Settings.cpp"

void setup(_difficulty *mode_);

void leftClickOnDefault(int i, int j);
void leftClickOnExposed(int i, int j);
void simulate(int mx, int my, bool leftClick, bool rightClick);
void safeFirstClick(int mx, int my, bool leftClick, bool rightClick);

void gameWonStatChange();
void gameLostStatChange();

void readGameData();
void writeGameData();

void resetStat();
void getSettings();
void saveSettings();

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


void setup(_difficulty *mode_)
{
    playSound(6);
    deleteBoard();
    count = mode.col;
    firstClick = true;
    front = 0, back = 0;
    flagged = 0, exposed = 0;
    srand((unsigned int)time(NULL));
    mode = *mode_, gameState = IN_GAME;
    _time = 0, isRecord = false, canResume = true;

	board = (_cell **)malloc(mode.col * sizeof(_cell *));
    for (int i = 0; i < mode.col; i++) board[i] = (_cell *)malloc(mode.row * sizeof(_cell));

    for (int i = 0; i < mode.col; i++){
        for (int j = 0; j < mode.row; j++){
            board[i][j].num = 0;
            board[i][j].isMine = false;
            board[i][j].visited = false;
            board[i][j].state = DEFAULT;
        }
    }

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
			if (I >= 0 && I < mode.col && J >= 0 && J < mode.row) board[I][J].num++;
		}
	}
}

void simulate(int mx, int my, bool leftClick, bool rightClick)
{
    int i = (mx - mode.x) / mode.w, j = (my - mode.y) / mode.w;
    if (leftClick && i >= 0 && i < mode.col && j >= 0 && j < mode.row)
    {
        if (board[i][j].state == DEFAULT) playSound(2), leftClickOnDefault(i, j);
        else if (board[i][j].state == EXPOSED && board[i][j].num != 0) playSound(0), leftClickOnExposed(i, j);
    }
    else if (rightClick && i >= 0 && i < mode.col && j >= 0 && j < mode.row)
    {
        if (board[i][j].state == DEFAULT)
        {
            flagged++, playSound(4);
            board[i][j].state = FLAGGED;

            if (autoChord)
            {
                for (int k = 0; k < 8; k++){
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
		if (I >= 0 && I < mode.col && J >= 0 && J < mode.row && board[I][J].state == DEFAULT){
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
    simulate(mx, my, leftClick, rightClick);
}

void readGameData()
{
    FILE *fp = fopen("GameData.txt", "rb");
    if (fp != NULL)
    {
        fread(&savedSettings, sizeof(settingsVariables), 1, fp);
        fread(stats, sizeof(statVariables), 3, fp);
        fclose(fp);
    }
    else
    {
        printf("Error opening file for reading.\n");
        exit(1);
    }
}

void writeGameData()
{
    FILE *fp = fopen("GameData.txt", "wb");
    if (fp != NULL)
    {
        fwrite(&savedSettings, sizeof(settingsVariables), 1, fp);
        fwrite(stats, sizeof(statVariables), 3, fp);
        fclose(fp);
    }
    else
    {
        printf("Error opening file for writing.\n");
        exit(1);
    }
}

void getSettings()
{
    readGameData();
    theme = savedSettings.theme_;
    music = savedSettings.music_;
    animation = savedSettings.animation_;
    autoChord = savedSettings.autoChord_;
}

void saveSettings()
{
    readGameData();
    savedSettings.theme_ = theme;
    savedSettings.music_ = music;
    savedSettings.animation_ = animation;
    savedSettings.autoChord_ = autoChord;
    writeGameData();
}

void gameWonStatChange()
{
    stats[mode.statVal].gamesWon++;
    stats[mode.statVal].gamesPlayed++;
    stats[mode.statVal].currentLosing = 0;
    if (++stats[mode.statVal].currentWinning > stats[mode.statVal].maxWinning) stats[mode.statVal].maxWinning++;

    int i;
    for (i = 0; i < 5; i++) if (_time < stats[mode.statVal].score[i].score_) break;

    if (i < 5)
    {
        isRecord = true;
        for (int j = 3; j >= i; j--) stats[mode.statVal].score[j+1] = stats[mode.statVal].score[j];

        char date[20];
        stats[mode.statVal].score[i].score_ = _time;

        time_t time2; time(&time2);
        tm *time3 = localtime(&time2);
        sprintf(date, "%02d-%02d-%d", time3->tm_mday, time3->tm_mon+1, time3->tm_year+1900);
        strcpy(stats[mode.statVal].score[i].date_, date);
    }
    writeGameData();
}

void gameLostStatChange()
{
    stats[mode.statVal].gamesPlayed++;
    stats[mode.statVal].currentWinning = 0;
    if (++stats[mode.statVal].currentLosing > stats[mode.statVal].maxLosing) stats[mode.statVal].maxLosing++;
    writeGameData();
}

void resetStat()
{
    stats[curStat].gamesPlayed = 0;
    stats[curStat].gamesWon = 0;
    stats[curStat].currentWinning = 0;
    stats[curStat].currentLosing = 0;
    stats[curStat].maxWinning = 0;
    stats[curStat].maxLosing = 0;
    for (int i = 0; i < 5; i++) stats[curStat].score[i].score_ = __INT_MAX__;
    writeGameData();
}

void inGameTimer() { _time++; }

void Qpush(int n){ queue[back++] = n; }
int Qpop() { return queue[front++]; }
int Qsize() { return back - front; }

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
    if (count)
    {
        count--;
        for (int i = 0; i < mode.col; i++) board[i][count].visited = true;
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
    saveSettings();
    if (music) Sleep(400); //to play exit sound
    exit(0);
}
