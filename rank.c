#include "game.h"

void ranksave(int score, char name[])
{
    DATA r[11], temp;
    r[10].rank = 11;
    r[10].score = score;
    int a;
    for(a = 0; a < 20; a++)
    {
        r[10].name[a] = name[a];
    }
    int i, j, k, l;

    FILE *read;
    FILE *save;
    read = fopen("rank.txt", "r");
    save = fopen("temp.txt", "w");

    for(i = 0; i < 10; i++)
        fscanf(read, "%d %s %d", &r[i].rank, r[i].name, &r[i].score);

    for(j = 0; j < 10; j++)
    {
        for(k = 0; k < 10 - j; k++)
        {
            if(r[k].score < r[k+1].score)
            {
                temp.score = r[k].score;
                r[k].score = r[k+1].score;
                r[k+1].score = temp.score;
                for(l = 0; l < 10; l++)
                {
                    *temp.name = r[k].name[l];
                    r[k].name[l] = r[k+1].name[l];
                    r[k+1].name[l] = *temp.name;
                }
            }
        }
    }

    for(i = 0; i < 10; i++)
        fprintf(save, "%d %s %d\n", r[i].rank, r[i].name, r[i].score);
    fclose(save);
    fclose(read);

    rankinit();
}

void rankinit()
{
    DATA s[10];
    int i;
    FILE* read;
    FILE* save;

    read = fopen("rank.txt", "w");
    save = fopen("temp.txt", "r");
    for(i = 0; i < 10; i++)
        fscanf(save, "%d %s %d", &s[i].rank, s[i].name, &s[i].score);
    for(i = 0; i < 10; i++)
        fprintf(read, "%d %s %d\n", s[i].rank, s[i].name, s[i].score);

    fclose(read);
    fclose(save);

}

void rankshow()
{
    clear();
    DATA t[10];
    int i;
    FILE* read;
    read = fopen("rank.txt", "r");
    mvprintw(4, 20, "Rank     Name       Score");
    for(i = 0; i < 10; i++)
    {
        fscanf(read, "%d %s %d", &t[i].rank, t[i].name, &t[i].score);
        mvprintw(i+5, 20, "%2d %10s %10d\n", t[i].rank, t[i].name, t[i].score);
        refresh();
    }
    fclose(read);
}