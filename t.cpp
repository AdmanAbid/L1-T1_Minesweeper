#include <stdio.h>
#include <limits.h>
#include <cstring>

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
};
statVariables stats[3];

int main()
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
        printf("Error opening file for writing\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) printf("%d ", stats[0].score[i].score_);
}
