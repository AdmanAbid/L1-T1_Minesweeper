#pragma once

void bfs();
void inGameTimer();
void winAnimation();

enum _gameState
{
    MAIN_MENU,
    RESUME_MENU,
    SETTINGS,
    STATISTICS,
    ABOUT,
    NEW_GAME,
    IN_GAME,
    GAME_WON,
    GAME_LOST,
    LOG_IN,
    REGISTER,
} gameState = LOG_IN;

struct _difficulty
{
    int col, row, mines, notMines, x, y, w, statVal;
    char image[2][13][50];
} EASY, MEDIUM, HARD, mode;

struct settingsVariables
{
    int theme_;
    bool music_, autoChord_, animation_;
} savedSettings;

struct score_date
{
    int score_;
    char date_[20];
};

struct statVariables
{
    int gamesPlayed, gamesWon, maxWinning, maxLosing, currentWinning, currentLosing;
    score_date score[5];
} stats[3];

struct userData
{
    int userIndex;
    settingsVariables settings;
    statVariables stats[3];
};

struct _userData
{
    char _name[100];
    char _password[100];
};

enum _cellState
{
    DEFAULT,
    FLAGGED,
    EXPOSED,
};

struct _cell
{
    int num;
    bool isMine, visited;
    _cellState state;
};
_cell **board = NULL;


const int screenWidth = 1200, screenHeight = 750;
const int menuX = 490, menuY = 525, menuH = 50, menuW = 220, menuP = 10;
const int text1X = 130, text1Y = 710, text2X = 1025, text2Y = 710;
const int newGameY = 490, resumeY = 570;
const int homeX = 574, homeY = 5, homeW = 52;
const int winX = 460, winY = 693;
const int resetX = 540, resetY = 150;
const int statX = 540, statY = 600, statH = 50, statW = 120, statP = 20;
const int stat2X = 1030, stat2Y = 498, stat2P = 45;
const int stat3X = 128, stat3Y = 452, stat3P = 45;
const int setX = 325, setX2 = 725, setY = 520, setP = 10, setH = 50, setW = 150;

int _time = 0, curStat = 0;
int flagged = 0, exposed = 0;
bool isRecord = false, canResume = false, firstClick = false;

int theme = 1;
bool music = true;
bool autoChord = true;
bool animation = false;

int queue[500];
int front = 0, back = 0, rowCount = 0;

int di[] = {1, 1, 1, -1, -1, -1, 0, 0};
int dj[] = {0, 1, -1, 0, 1, -1, 1, -1};

int t1 = iSetTimer(1000, inGameTimer);
int t2 = iSetTimer(500, bfs);
int t3 = iSetTimer(500, winAnimation);

char str[50];
char SOUND[10][50];
char IMAGE[2][50][50];

char name[100], password[100], password2[100];
int nameInd = 0, passwordInd = 0;
bool takingUserName = true, takingPassword = false;
int userCount = 0, curUser = 0;
_userData *userList = NULL;

void initiate()
{
    EASY.col = 9;
    EASY.row = 9;
    EASY.mines = 10;
    EASY.notMines = 71;
    EASY.x = 312;
    EASY.y = 111;
    EASY.w = 64;
    EASY.statVal = 0;

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


    MEDIUM.col = 16;
    MEDIUM.row = 16;
    MEDIUM.mines = 40;
    MEDIUM.notMines = 216;
    MEDIUM.x = 312;
    MEDIUM.y = 111;
    MEDIUM.w = 36;
    MEDIUM.statVal = 1;

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


    HARD.col = 30;
    HARD.row = 16;
    HARD.mines = 99;
    HARD.notMines = 381;
    HARD.x = 60;
    HARD.y = 111;
    HARD.w = 36;
    HARD.statVal = 2;

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
    strcpy(IMAGE[0][24], "Images/Light/statscreen.bmp");
    strcpy(IMAGE[0][25], "Images/Light/stateasy.bmp");
    strcpy(IMAGE[0][26], "Images/Light/statmedium.bmp");
    strcpy(IMAGE[0][27], "Images/Light/stathard.bmp");
    strcpy(IMAGE[0][28], "Images/Light/aboutscreen.bmp");

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
    strcpy(IMAGE[1][24], "Images/Dark/statscreen.bmp");
    strcpy(IMAGE[1][25], "Images/Dark/stateasy.bmp");
    strcpy(IMAGE[1][26], "Images/Dark/statmedium.bmp");
    strcpy(IMAGE[1][27], "Images/Dark/stathard.bmp");
    strcpy(IMAGE[1][28], "Images/Dark/aboutscreen.bmp");
    strcpy(IMAGE[1][29], "Images/Dark/loginpage.bmp");
    strcpy(IMAGE[1][30], "Images/Dark/pointer.bmp");
    strcpy(IMAGE[1][31], "Images/Dark/login.bmp");
    strcpy(IMAGE[1][32], "Images/Dark/register.bmp");
    strcpy(IMAGE[1][33], "Images/Dark/logout.bmp");


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
