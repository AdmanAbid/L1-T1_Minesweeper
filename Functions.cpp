#include "Settings.cpp"


void setup(_difficulty *mode_);
void simulate(int mx, int my, bool leftClick, bool rightClick);
void leftClick_on_default(int i, int j);
void leftClick_on_exposed(int i, int j);
void dfs(int i, int j);
void saveData();
void getSettings();
void gameWon_statChange();
void gameLost_statChange();
void getStat();
void exitGame();
void safeFirstClick(int mx, int my, bool leftClick, bool rightClick);
void deleteBoard();
void inGameTimer();
void winAnimation();
void bfs();
void resetStat();
void playSound(int n);
void Qpush(int n);
int Qpop();
int Qsize();


void setup(_difficulty *mode_)
{
    playSound(6);
    srand((unsigned int)time(NULL));
    mode = *mode_, gameState = IN_GAME;
    _time = 0, isRecord = false, canResume = true;
    flagged = 0, exposed = 0;
    front = 0, back = 0;
    count = mode.row;
    firstClick = true;

    deleteBoard();
	board = (_cell **)malloc(mode.row * sizeof(_cell *));
    for (int i = 0; i < mode.row; i++)
        board[i] = (_cell *)malloc(mode.col * sizeof(_cell));
    
    for (int i = 0; i < mode.row; i++){
        for (int j = 0; j < mode.col; j++){
            board[i][j].num = 0;
            board[i][j].isMine = false;
            board[i][j].visited = false;
            board[i][j].state = DEFAULT;
        }
    }

    for (int n = 0; n < mode.mines; n++)
	{
		int i, j;
		do
		{
			i = rand() % mode.row, j = rand() % mode.col;
		} while (board[i][j].isMine);

		board[i][j].isMine = true;
		for (int k = 0; k < 8; k++)
		{
			int I = i + di[k], J = j + dj[k];
			if (I >= 0 && I < mode.row && J >= 0 && J < mode.col) board[I][J].num++;
		}
	}
}

void simulate(int mx, int my, bool leftClick, bool rightClick)
{
    int i = (mx - mode.x) / mode.w, j = (my - mode.y) / mode.w;
    if (leftClick && i >= 0 && i < mode.row && j >= 0 && j < mode.col)
    {
        if (board[i][j].state == DEFAULT)
        {
            playSound(2);
            leftClick_on_default(i, j);
        }
        else if (board[i][j].state == EXPOSED && board[i][j].num != 0) playSound(0), leftClick_on_exposed(i, j);
    }
    else if (rightClick && i >= 0 && i < mode.row && j >= 0 && j < mode.col)
    {
        if (board[i][j].state == DEFAULT)
        {
            board[i][j].state = FLAGGED;
            flagged++, playSound(4);

            if (autoChord)
            {
                for (int k = 0; k < 8; k++){
                    int I = i + di[k], J = j + dj[k];
                    if (I >= 0 && I < mode.row && J >= 0 && J < mode.col && board[I][J].state == EXPOSED)
                    {
                        leftClick_on_exposed(I, J);
                        if (gameState == GAME_LOST) break;
                    }
                }
            }
        }
        else if (board[i][j].state == FLAGGED) board[i][j].state = DEFAULT, flagged--, playSound(5);
    }
    if (exposed == mode.notMines)
    {
        playSound(8);
        gameWon_statChange();
        gameState = GAME_WON;
        canResume = false;
    }
}

void leftClick_on_default(int i, int j)
{
    if (!board[i][j].isMine)
    {
        board[i][j].state = EXPOSED;
        exposed++;
        if (autoChord) leftClick_on_exposed(i, j);
        if (board[i][j].num == 0) dfs(i, j);
    }
    else
    {
        board[i][j].visited = true;
        gameState = GAME_LOST;
        canResume = false;
        gameLost_statChange();
        if (animation) Qpush(i*30 + j);
        else playSound(3);
    }
}

void leftClick_on_exposed(int i, int j)
{
    int flagCount = 0;
    for (int k = 0; k < 8; k++)
    {
        int I = i + di[k], J = j + dj[k];
        if (I >= 0 && I < mode.row && J >= 0 && J < mode.col && board[I][J].state == FLAGGED) flagCount++;
    }
    if (flagCount != board[i][j].num) return;

    for (int k = 0; k < 8; k++)
    {
        int I = i + di[k], J = j + dj[k];
        if (I >= 0 && I < mode.row && J >= 0 && J < mode.col && board[I][J].state == DEFAULT)
        {
            leftClick_on_default(I, J);
            if (gameState == GAME_LOST) break;
        }
    }
}

void dfs(int i, int j)
{
	for (int k = 0; k < 8; k++)
	{
		int I = i + di[k], J = j + dj[k];
		if (I >= 0 && I < mode.row && J >= 0 && J < mode.col && board[I][J].state == DEFAULT){
			board[I][J].state = EXPOSED;
            exposed++;
			if (board[I][J].num == 0) dfs(I, J);
		}
	}
}

void saveData()
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
        printf("Error opening file for reading in saveData\n");
        exit(1);
    }

    fp = fopen("GameData.txt", "wb");
    if (fp != NULL)
    {
        savedSettings.theme_ = theme;
        savedSettings.music_ = music;
        savedSettings.animation_ = animation;
        savedSettings.autoChord_ = autoChord;

        fwrite(&savedSettings, sizeof(settingsVariables), 1, fp);
        fwrite(stats, sizeof(statVariables), 3, fp);
        fclose(fp);
    }
    else
    {
        printf("Error opening file for writing in saveData\n");
        exit(1);
    }
}

void getSettings()
{
    FILE *fp = fopen("GameData.txt", "rb");
    if (fp != NULL)
    {
        fread(&savedSettings, sizeof(settingsVariables), 1, fp);
        theme = savedSettings.theme_;
        music = savedSettings.music_;
        animation = savedSettings.animation_;
        autoChord = savedSettings.autoChord_;
        fclose(fp);
    }
    else
    {
        printf("Error opening file for reading\n");
        exit(1);
    }
}

void gameWon_statChange()
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
        printf("Error opening file for reading in gamewon\n");
        exit(1);
    }

    stats[mode.statVal].gamesPlayed++;
    stats[mode.statVal].gamesWon++;
    stats[mode.statVal].currentLosing = 0;
    if (++stats[mode.statVal].currentWinning > stats[mode.statVal].maxWinning) stats[mode.statVal].maxWinning++;

    int i;
    for (i = 0; i < 5; i++)
        if (_time < stats[mode.statVal].score[i].score_) break;

    if (i < 5)
    {
        isRecord = true;
        for (int j = 3; j >= i; j--) stats[mode.statVal].score[j+1] = stats[mode.statVal].score[j];
        stats[mode.statVal].score[i].score_ = _time;

        time_t time2; time(&time2);
        tm *time3 = localtime(&time2);
        char date[20];
        sprintf(date, "%02d-%02d-%d", time3->tm_mday, time3->tm_mon+1, time3->tm_year+1900);
        strcpy(stats[mode.statVal].score[i].date_, date);
    }

    fp = fopen("GameData.txt", "wb");
    if (fp != NULL)
    {
        fwrite(&savedSettings, sizeof(settingsVariables), 1, fp);
        fwrite(stats, sizeof(statVariables), 3, fp);
        fclose(fp);
    }
    else
    {
        printf("Error opening file for writing in gamewon\n");
        exit(1);
    }
}

void gameLost_statChange()
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
        printf("Error opening file for reading in gamelost\n");
        exit(1);
    }

    stats[mode.statVal].gamesPlayed++;
    stats[mode.statVal].currentWinning = 0;
    if (++stats[mode.statVal].currentLosing > stats[mode.statVal].maxLosing) stats[mode.statVal].maxLosing++;

    fp = fopen("GameData.txt", "wb");
    if (fp != NULL)
    {
        fwrite(&savedSettings, sizeof(settingsVariables), 1, fp);
        fwrite(stats, sizeof(statVariables), 3, fp);
        fclose(fp);
    }
    else
    {
        printf("Error opening file for writing in gamelost\n");
        exit(1);
    }
}

void getStat()
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
        printf("Error opening file for reading in getStat\n");
        exit(1);
    }
}

void exitGame()
{
    playSound(7);
    saveData();
    deleteBoard();
    if (music) Sleep(400);
    exit(0);
}

void safeFirstClick(int mx, int my, bool leftClick, bool rightClick)
{
    int i = (mx - mode.x) / mode.w, j = (my - mode.y) / mode.w;
    if (i >= 0 && i < mode.row && j >= 0 && j < mode.col && (leftClick || rightClick))
    {
        firstClick = false;
        if (leftClick && board[i][j].isMine)
        {
            int t = 0;
            while (board[t][mode.col-1].isMine && t < mode.row) t++;

            board[t][mode.col-1].isMine = true;
            for (int k = 0; k < 8; k++)
            {
                int I = t + di[k], J = mode.col-1 + dj[k];
                if (I >= 0 && I < mode.row && J >= 0 && J < mode.col) board[I][J].num++;
            }

            board[i][j].isMine = false;
            for (int k = 0; k < 8; k++)
            {
                int I = i + di[k], J = j + dj[k];
                if (I >= 0 && I < mode.row && J >= 0 && J < mode.col) board[I][J].num--;
            }
        }
    }
    simulate(mx, my, leftClick, rightClick);
}

void deleteBoard()
{
    if (board)
    {
        for (int i = 0; i < sizeof(board)/sizeof(_cell *); i++) free(board[i]);
        free(board);
        board = NULL;
    }
}

void inGameTimer()
{
    _time++;
}

void winAnimation()
{
    if (count){
        count--;
        for (int i = 0; i < mode.row; i++) board[i][count].visited = true;
    }
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
            if (I >= 0 && I < mode.row && J >= 0 && J < mode.col && !board[I][J].visited)
            {
                if (board[I][J].isMine) mine_ = true;
                board[I][J].visited = true;
                Qpush(I*30 + J);
            }
        }
    }
    if (mine_) playSound(3);
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

    FILE *fp = fopen("GameData.txt", "wb");
    if (fp != NULL)
    {
        fwrite(&savedSettings, sizeof(settingsVariables), 1, fp);
        fwrite(stats, sizeof(statVariables), 3, fp);
        fclose(fp);
    }
    else
    {
        printf("Error opening file for writing in resetStat\n");
        exit(1);
    }
}

void playSound(int n)
{
    if (music)
    {
        PlaySound(0, 0, 0);
        PlaySound(SOUND[n], NULL, SND_ASYNC);
    }
    if (n == 7) Sleep(100);
}

void Qpush(int n) {queue[back++] = n;}
int Qpop() {return queue[front++];}
int Qsize() {return back - front;}
