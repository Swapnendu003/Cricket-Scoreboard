#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wel.h"

void newentry();
void view();

int main()
{
    int n;
    do
    {
        stylesheet();
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            newentry();
            break;
        case 2:
            view();
            break;
        case 3:
            printf("THANK YOU");
            break;
        default:
            printf("Wrong choice! Try again");
        }
    } while (n != 3);

    return 0;
}

void newentry()
{

    char team1[20], team2[20], venue[20], date[20];
    int score1, score2, extra1, extra2;
    FILE *fp;
    struct bat
    {
        char name[40];
        int run;
    };
    struct bat t1[11], t2[11];
    struct ball
    {
        char name[40];
        int overs, wickets, runs;
    };
    struct ball t1b[11], t2b[11];
    int t1c = 0, t2c = 0, t1bc = 0, t2bc = 0, f = 1, s1 = 0, s2 = 0, w1 = 0, w2 = 0, i1l, i2l; // s1, s2 are the variables to calculate the total run of team 1 and team 2 rspt  i1l and 12l are the variables to maintain the number of rows in the table
    char fname[128];
    printf("Enter Scoreboard File name: ");
    scanf("%123s", fname);
    getchar();
    strcat(fname, ".txt");
    printf("Enter the date: ");
    gets(date);
    printf("Enter the venue: ");
    gets(venue);
    printf("Enter name of team 1: ");
    scanf("%s", team1);
    printf("Enter name of team 2: ");
    scanf("%s", team2);
    getchar();
    fp = fopen(fname, "w");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    fprintf(fp, "===================================================================================================================================================\n");
    fprintf(fp, "                                                     |        %s vs %s        |\n", team1, team2);
    fprintf(fp, "===================================================================================================================================================\n");
    fprintf(fp, "                                                   ####Date: %s     Venue: %s####\n", date, venue);
    fprintf(fp, "===================================================================================================================================================\n");
    printf("Enter the details of the batters of %s\n", team1);
    while (f != 0)
    {
        printf("Enter name, runs: ");
        gets(t1[t1c].name);
        scanf("%d", &t1[t1c].run);
        s1 = s1 + t1[t1c].run;
        t1c++;
        printf("Enter 1 for next batter or enter 0 to enter bowlers: ");
        scanf("%d", &f);
        getchar();
    }
    f = 1;
    printf("Enter the details of the bowlers of %s\n", team1);
    while (f != 0)
    {
        printf("Enter name, overs, wickets, runs given: ");
        gets(t1b[t1bc].name);
        scanf("%d %d %d", &t1b[t1bc].overs, &t1b[t1bc].wickets, &t1b[t1bc].runs);
        w1 = w1 + t1b[t1bc].wickets;
        t1bc++;
        printf("Enter 1 for next bowler or enter 0 to enter next team details: ");
        scanf("%d", &f);

        getchar();
    }
    printf("Extra runs given by %s\n", team1);
    scanf("%d", &extra1);
    getchar();
    f = 1;
    printf("Enter the details of the batters of %s\n", team2);
    while (f != 0)
    {
        printf("Enter name, runs: ");
        gets(t2[t2c].name);
        scanf("%d", &t2[t2c].run);
        s2 = s2 + t2[t2c].run;
        t2c++;
        printf("Enter 1 for next batter or enter 0 to enter bowlers: ");
        scanf("%d", &f);
        getchar();
    }
    f = 1;
    printf("Enter the details of the bowlers of %s\n", team2);
    while (f != 0)
    {
        printf("Enter name, overs, wickets, runs given: ");
        gets(t2b[t2bc].name);
        scanf("%d %d %d", &t2b[t2bc].overs, &t2b[t2bc].wickets, &t2b[t2bc].runs);
        w2 = w2 + t2b[t2bc].wickets;
        t2bc++;
        printf("Enter 1 for next bowler or enter 0 to end: ");
        scanf("%d", &f);
        getchar();
    }
    printf("Extra runs given by %s\n", team2);
    scanf("%d", &extra2);
    s1 += extra2; // total runs scored by the batters of team 1
    s2 += extra1; // total runs scored by the batters of team 2
    i1l = (t1c > t2bc) ? t1c : t2bc;
    i2l = (t2c > t1bc) ? t2c : t1bc;
    fprintf(fp, "                          Batters of %s                                |                      Bowlers of %s\n", team1, team2);
    fprintf(fp, "===================================================================================================================================================\n");
    fprintf(fp, "        |              Name              |     Runs Scored     |               |          Name            |    Overs   |   Wickets   |    Runs    |\n");
    for (int i = 0; i < i1l; i++)
    {
        fprintf(fp, "---------------------------------------------------------------------------------------------------------------------------------------------------\n");
        if (t1c <= i)
            fprintf(fp, "        |                                |                 |               | %24s | %10d | %11d | %10d |\n", t2b[i].name, t2b[i].overs, t2b[i].wickets, t2b[i].runs);
        else if (t2bc <= i)
            fprintf(fp, "        |           %-20s |     %-10d      |               |                          |            |             |            |\n", t1[i].name, t1[i].run);
        else
            fprintf(fp, "        |           %-20s |     %-10d      |               | %24s | %10d | %11d | %10d |\n", t1[i].name, t1[i].run, t2b[i].name, t2b[i].overs, t2b[i].wickets, t2b[i].runs);
    }
    fprintf(fp, "===================================================================================================================================================\n");
    fprintf(fp, "                          Batters of %s                                |                      Bowlers of %s\n", team2, team1);
    fprintf(fp, "===================================================================================================================================================\n");
    fprintf(fp, "        |              Name              |     Runs Scored     |               |          Name            |    Overs   |   Wickets   |    Runs    |\n");
    for (int i = 0; i < i2l; i++)
    {
        fprintf(fp, "---------------------------------------------------------------------------------------------------------------------------------------------------\n");
        if (t2c <= i)
            fprintf(fp, "        |                                |                 |               | %24s | %10d | %11d | %10d |\n", t1b[i].name, t1b[i].overs, t1b[i].wickets, t1b[i].runs);
        else if (t1bc <= i)
            fprintf(fp, "        |           %-20s |     %-10d      |               |                          |            |             |            |\n", t2[i].name, t2[i].run);
        else
            fprintf(fp, "        |           %-20s |     %-10d      |               | %24s | %10d | %11d | %10d |\n", t2[i].name, t2[i].run, t1b[i].name, t1b[i].overs, t1b[i].wickets, t1b[i].runs);
    }
    fprintf(fp, "===================================================================================================================================================\n");
    fprintf(fp, "                                %s               %d-%d                                %s               %d-%d\n", team1, s1, w1, team2, s2, w2);
    fprintf(fp, "===================================================================================================================================================\n");
    if (s1 > s2)
        fprintf(fp, "                                                     |        %s Won the Match!!!       |\n", team1);
    else if (s2 > s1)
        fprintf(fp, "                                                     |        %s Won the Match!!!       |\n", team2);
    else
        fprintf(fp, "                                                     |         ~~~ DRAW ~~~       |\n");
    fprintf(fp, "===================================================================================================================================================\n");
    fclose(fp);
    printf("Scoreboard updated successfully!\n");
}

void view()
{
    char fname[128], ch;
    FILE *fp;
    printf("Enter the name of the file to view: ");
    scanf("%123s", fname);
    getchar();
    strcat(fname, ".txt");
    fp = fopen(fname, "r");
    if (fp == NULL)
    {
        printf("File does not exist.\n");
        return;
    }
    while ((ch = fgetc(fp)) != EOF)
        printf("%c", ch);
    fclose(fp);
}
