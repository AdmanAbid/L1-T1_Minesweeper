void playSound(int n);
void dfs(int i, int j);
void bfs();
void inGameTimer();
void deleteBoard();
void leftClick_on_exposed(int i, int j);
void winAnimation();
void Qpush(int n);
int Qpop();
int Qsize();

enum _gameState
{
    MAIN_MENU,
    RESUME_MENU,
    NEW_GAME,
    SETTINGS,
    STATISTICS,
    HELP,
    IN_GAME,
    GAME_WON,
    GAME_LOST,
};
_gameState gameState = MAIN_MENU;

enum _cellState
{
    DEFAULT,
    FLAGGED,
    EXPOSED,
    DETONATED,
};

struct _cell
{
    bool isMine, canChord, visited;
    int num;
    _cellState state;
};
_cell **board = NULL;

struct _difficulty
{
    int row, col, mines, notMines, x, y, w, statNum;
    char image[2][13][50];
};
_difficulty EASY, MEDIUM, HARD, mode;
char IMAGE[2][26][50];
char SOUND[10][50];

void initiate()
{
    EASY.row = 9;
    EASY.col = 9;
    EASY.mines = 10;
    EASY.notMines = 71;
    EASY.x = 312;
    EASY.y = 111;
    EASY.w = 64;
    EASY.statNum = 0;

    strcpy(EASY.image[0][0], "Images/Light/flag.bmp");
    strcpy(EASY.image[0][1], "Images/Light/mine.bmp");
    strcpy(EASY.image[0][2], "Images/Light/exmine.bmp");
    strcpy(EASY.image[0][3], "Images/Light/blank.bmp");
    strcpy(EASY.image[0][4], "Images/Light/zero.bmp");
    strcpy(EASY.image[0][5], "Images/Light/one.bmp");
    strcpy(EASY.image[0][6], "Images/Light/two.bmp");
    strcpy(EASY.image[0][7], "Images/Light/three.bmp");
    strcpy(EASY.image[0][8], "Images/Light/four.bmp");
    strcpy(EASY.image[0][9], "Images/Light/five.bmp");
    strcpy(EASY.image[0][10], "Images/Light/six.bmp");
    strcpy(EASY.image[0][11], "Images/Light/seven.bmp");
    strcpy(EASY.image[0][12], "Images/Light/eight.bmp");

    strcpy(EASY.image[1][0], "Images/Dark/flag.bmp");
    strcpy(EASY.image[1][1], "Images/Dark/mine.bmp");
    strcpy(EASY.image[1][2], "Images/Dark/exmine.bmp");
    strcpy(EASY.image[1][3], "Images/Dark/blank.bmp");
    strcpy(EASY.image[1][4], "Images/Dark/zero.bmp");
    strcpy(EASY.image[1][5], "Images/Dark/one.bmp");
    strcpy(EASY.image[1][6], "Images/Dark/two.bmp");
    strcpy(EASY.image[1][7], "Images/Dark/three.bmp");
    strcpy(EASY.image[1][8], "Images/Dark/four.bmp");
    strcpy(EASY.image[1][9], "Images/Dark/five.bmp");
    strcpy(EASY.image[1][10], "Images/Dark/six.bmp");
    strcpy(EASY.image[1][11], "Images/Dark/seven.bmp");
    strcpy(EASY.image[1][12], "Images/Dark/eight.bmp");


    MEDIUM.row = 16;
    MEDIUM.col = 16;
    MEDIUM.mines = 40;
    MEDIUM.notMines = 216;
    MEDIUM.x = 312;
    MEDIUM.y = 111;
    MEDIUM.w = 36;
    MEDIUM.statNum = 1;

    strcpy(MEDIUM.image[0][0], "Images/Light/flag2.bmp");
    strcpy(MEDIUM.image[0][1], "Images/Light/mine2.bmp");
    strcpy(MEDIUM.image[0][2], "Images/Light/exmine2.bmp");
    strcpy(MEDIUM.image[0][3], "Images/Light/blank2.bmp");
    strcpy(MEDIUM.image[0][4], "Images/Light/zero2.bmp");
    strcpy(MEDIUM.image[0][5], "Images/Light/one2.bmp");
    strcpy(MEDIUM.image[0][6], "Images/Light/two2.bmp");
    strcpy(MEDIUM.image[0][7], "Images/Light/three2.bmp");
    strcpy(MEDIUM.image[0][8], "Images/Light/four2.bmp");
    strcpy(MEDIUM.image[0][9], "Images/Light/five2.bmp");
    strcpy(MEDIUM.image[0][10], "Images/Light/six2.bmp");
    strcpy(MEDIUM.image[0][11], "Images/Light/seven2.bmp");
    strcpy(MEDIUM.image[0][12], "Images/Light/eight2.bmp");

    strcpy(MEDIUM.image[1][0], "Images/Dark/flag2.bmp");
    strcpy(MEDIUM.image[1][1], "Images/Dark/mine2.bmp");
    strcpy(MEDIUM.image[1][2], "Images/Dark/exmine2.bmp");
    strcpy(MEDIUM.image[1][3], "Images/Dark/blank2.bmp");
    strcpy(MEDIUM.image[1][4], "Images/Dark/zero2.bmp");
    strcpy(MEDIUM.image[1][5], "Images/Dark/one2.bmp");
    strcpy(MEDIUM.image[1][6], "Images/Dark/two2.bmp");
    strcpy(MEDIUM.image[1][7], "Images/Dark/three2.bmp");
    strcpy(MEDIUM.image[1][8], "Images/Dark/four2.bmp");
    strcpy(MEDIUM.image[1][9], "Images/Dark/five2.bmp");
    strcpy(MEDIUM.image[1][10], "Images/Dark/six2.bmp");
    strcpy(MEDIUM.image[1][11], "Images/Dark/seven2.bmp");
    strcpy(MEDIUM.image[1][12], "Images/Dark/eight2.bmp");


    HARD.row = 30;
    HARD.col = 16;
    HARD.mines = 99;
    HARD.notMines = 381;
    HARD.x = 60;
    HARD.y = 111;
    HARD.w = 36;
    HARD.statNum = 2;

    strcpy(HARD.image[0][0], "Images/Light/flag2.bmp");
    strcpy(HARD.image[0][1], "Images/Light/mine2.bmp");
    strcpy(HARD.image[0][2], "Images/Light/exmine2.bmp");
    strcpy(HARD.image[0][3], "Images/Light/blank2.bmp");
    strcpy(HARD.image[0][4], "Images/Light/zero2.bmp");
    strcpy(HARD.image[0][5], "Images/Light/one2.bmp");
    strcpy(HARD.image[0][6], "Images/Light/two2.bmp");
    strcpy(HARD.image[0][7], "Images/Light/three2.bmp");
    strcpy(HARD.image[0][8], "Images/Light/four2.bmp");
    strcpy(HARD.image[0][9], "Images/Light/five2.bmp");
    strcpy(HARD.image[0][10], "Images/Light/six2.bmp");
    strcpy(HARD.image[0][11], "Images/Light/seven2.bmp");
    strcpy(HARD.image[0][12], "Images/Light/eight2.bmp");

    strcpy(HARD.image[1][0], "Images/Dark/flag2.bmp");
    strcpy(HARD.image[1][1], "Images/Dark/mine2.bmp");
    strcpy(HARD.image[1][2], "Images/Dark/exmine2.bmp");
    strcpy(HARD.image[1][3], "Images/Dark/blank2.bmp");
    strcpy(HARD.image[1][4], "Images/Dark/zero2.bmp");
    strcpy(HARD.image[1][5], "Images/Dark/one2.bmp");
    strcpy(HARD.image[1][6], "Images/Dark/two2.bmp");
    strcpy(HARD.image[1][7], "Images/Dark/three2.bmp");
    strcpy(HARD.image[1][8], "Images/Dark/four2.bmp");
    strcpy(HARD.image[1][9], "Images/Dark/five2.bmp");
    strcpy(HARD.image[1][10], "Images/Dark/six2.bmp");
    strcpy(HARD.image[1][11], "Images/Dark/seven2.bmp");
    strcpy(HARD.image[1][12], "Images/Dark/eight2.bmp");


    strcpy(IMAGE[0][0], "Images/Light/background.bmp");
    strcpy(IMAGE[0][1], "Images/Light/resume.bmp");
    strcpy(IMAGE[0][2], "Images/Light/newgame.bmp");
    strcpy(IMAGE[0][3], "Images/Light/settings.bmp");
    strcpy(IMAGE[0][4], "Images/Light/statistics.bmp");
    strcpy(IMAGE[0][5], "Images/Light/about.bmp");
    strcpy(IMAGE[0][6], "Images/Light/exit.bmp");
    strcpy(IMAGE[0][7], "Images/Light/easy.bmp");
    strcpy(IMAGE[0][8], "Images/Light/medium.bmp");
    strcpy(IMAGE[0][9], "Images/Light/hard.bmp");
    strcpy(IMAGE[0][10], "Images/Light/youwin.bmp");
    strcpy(IMAGE[0][11], "Images/Light/youlose.bmp");
    strcpy(IMAGE[0][12], "Images/Light/newrecord.bmp");
    strcpy(IMAGE[0][13], "Images/Light/home.bmp");
    strcpy(IMAGE[0][14], "Images/Light/reset.bmp");
    strcpy(IMAGE[0][15], "Images/Light/theme.bmp");
    strcpy(IMAGE[0][16], "Images/Light/sound.bmp");
    strcpy(IMAGE[0][17], "Images/Light/chord.bmp");
    strcpy(IMAGE[0][18], "Images/Light/light.bmp");
    strcpy(IMAGE[0][19], "Images/Light/animation.bmp");
    strcpy(IMAGE[0][20], "Images/Light/on.bmp");
    strcpy(IMAGE[0][21], "Images/Light/off.bmp");
    strcpy(IMAGE[0][22], "Images/Light/click.bmp");
    strcpy(IMAGE[0][23], "Images/Light/auto.bmp");

    strcpy(IMAGE[1][0], "Images/Dark/background.bmp");
    strcpy(IMAGE[1][1], "Images/Dark/resume.bmp");
    strcpy(IMAGE[1][2], "Images/Dark/newgame.bmp");
    strcpy(IMAGE[1][3], "Images/Dark/settings.bmp");
    strcpy(IMAGE[1][4], "Images/Dark/statistics.bmp");
    strcpy(IMAGE[1][5], "Images/Dark/about.bmp");
    strcpy(IMAGE[1][6], "Images/Dark/exit.bmp");
    strcpy(IMAGE[1][7], "Images/Dark/easy.bmp");
    strcpy(IMAGE[1][8], "Images/Dark/medium.bmp");
    strcpy(IMAGE[1][9], "Images/Dark/hard.bmp");
    strcpy(IMAGE[1][10], "Images/Dark/youwin.bmp");
    strcpy(IMAGE[1][11], "Images/Dark/youlose.bmp");
    strcpy(IMAGE[1][12], "Images/Dark/newrecord.bmp");
    strcpy(IMAGE[1][13], "Images/Dark/home.bmp");
    strcpy(IMAGE[1][14], "Images/Dark/reset.bmp");
    strcpy(IMAGE[1][15], "Images/Dark/theme.bmp");
    strcpy(IMAGE[1][16], "Images/Dark/sound.bmp");
    strcpy(IMAGE[1][17], "Images/Dark/chord.bmp");
    strcpy(IMAGE[1][18], "Images/Dark/dark.bmp");
    strcpy(IMAGE[1][19], "Images/Dark/animation.bmp");
    strcpy(IMAGE[1][20], "Images/Dark/on.bmp");
    strcpy(IMAGE[1][21], "Images/Dark/off.bmp");
    strcpy(IMAGE[1][22], "Images/Dark/click.bmp");
    strcpy(IMAGE[1][23], "Images/Dark/auto.bmp");


    strcpy(SOUND[0], "Sounds/Chord.wav");
    strcpy(SOUND[1], "Sounds/ChordFailed.wav");
    strcpy(SOUND[2], "Sounds/Click.wav");
    strcpy(SOUND[3], "Sounds/Explosion.wav");
    strcpy(SOUND[4], "Sounds/Flag.wav");
    strcpy(SOUND[5], "Sounds/Unflag.wav");
    strcpy(SOUND[6], "Sounds/GameStart.wav");
    strcpy(SOUND[7], "Sounds/UIClick.wav");
    strcpy(SOUND[8], "Sounds/Win.wav");
}

const int screenWidth = 1200, screenHeight = 750;
const int menuX = 490, menuY = 525, menuH = 50, menuW = 220, menuP = 10;
const int newGameY = 490, resumeY = 570;
const int homeX = 574, homeY = 5, homeW = 52;
const int ywinX = 450, ywinY = 690;
const int yloseX = 450, yloseY = 690;
const int statX = 450, statY = 550, statW = 45;
const int winX = 460, winY = 693;
const int resetX = 450, resetY = 100, resetH = 100, resetW = 300;
const int setX = 325, setX2 = 725, setY = 520, setP = 10, setH = 50, setW = 150;

int di[] = {1, 1, 1, -1, -1, -1, 0, 0};
int dj[] = {0, 1, -1, 0, 1, -1, 1, -1};

int flagged = 0, exposed = 0;
bool isRecord = false, canResume = false;
int _time = 0;
char str[50];

int theme = 1;
bool music = true;
bool animation = false;
bool autoChord = true;

int queue[500];
int front = 0, back = 0, count = 0;

int t1 = iSetTimer(1000, inGameTimer);
int t2 = iSetTimer(500, bfs);
int t3 = iSetTimer(600, winAnimation);

void setup(_difficulty *mode_)
{
    playSound(6);
    srand((unsigned int)time(NULL));
    mode = *mode_, gameState = IN_GAME;
    _time = 0, isRecord = false, canResume = true;
    flagged = 0, exposed = 0;
    front = 0, back = 0;
    count = mode.row;

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
        gameState = GAME_WON;
        canResume = false;
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

void winAnimation()
{
    if (count){
        count--;
        for (int i = 0; i < mode.row; i++) board[i][count].visited = true;
    }
}

void inGameTimer()
{
    _time++;
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

void exitGame()
{
    playSound(7);
    deleteBoard();
    if (music) Sleep(400);
    exit(0);
}