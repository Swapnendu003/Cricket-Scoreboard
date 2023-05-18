#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hw.h"
#include <ncurses.h>
#include <form.h>

void newentry();
void view();

int main()
{
    int n;
    do
    {
        style();
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
            printf("THANK YOU \n");
            break;
        default:
            printf("Wrong choice! Try again");
        }
    } while (n != 3);

    return 0;
}

void newentry()
{
    clear();
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

    initscr();            // Initialize ncurses
    cbreak();             // Line buffering disabled
    keypad(stdscr, TRUE); // Enable function keys

    printw("Enter Scoreboard File name: ");
    refresh();
    getnstr(fname, sizeof(fname) - 1);
    strcat(fname, ".txt");

    printw("Enter the date: ");
    refresh();
    getnstr(date, sizeof(date) - 1);

    printw("Enter the venue: ");
    refresh();
    getnstr(venue, sizeof(venue) - 1);

    printw("Enter name of team 1: ");
    refresh();
    getnstr(team1, sizeof(team1) - 1);

    printw("Enter name of team 2: ");
    refresh();
    getnstr(team2, sizeof(team2) - 1);

    clear(); // Clear the screen

    fp = fopen(fname, "w");
    if (fp == NULL)
    {
        printw("Error opening file.\n");
        refresh();
        fclose(fp);
        endwin();
        return;
    }

    fprintf(fp, "===================================================================================================================================================\n");
    fprintf(fp, "                                                     |        %s vs %s        |\n", team1, team2);
    fprintf(fp, "===================================================================================================================================================\n");
    fprintf(fp, "                                                   ####Date: %s     Venue: %s####\n", date, venue);
    fprintf(fp, "===================================================================================================================================================\n");

    printw("Enter the details of the batters of %s\n", team1);
    while (f != 0)
    {
        printw("Enter name, runs: ");
        refresh();
        getnstr(t1[t1c].name, sizeof(t1[t1c].name) - 1);
        scanw("%d", &t1[t1c].run);
        s1 += t1[t1c].run;
        t1c++;

        printw("Enter 1 for next batter or enter 0 to enter bowlers: ");
        refresh();
        scanw("%d", &f);
        clear();
    }

    f = 1;
    clear();

    printw("Enter the details of the bowlers of %s\n", team1);
    while (f != 0)
    {
        printw("Enter name, overs, wickets, runs given: ");
        refresh();
        getnstr(t1b[t1bc].name, sizeof(t1b[t1bc].name) - 1);
        scanw("%d %d %d", &t1b[t1bc].overs, &t1b[t1bc].wickets, &t1b[t1bc].runs);
        w2 += t1b[t1bc].wickets;
        t1bc++;
        printw("Enter 1 for next bowler or enter 0 to enter batsman details of %s: ", team2);
        refresh();
        scanw("%d", &f);
        clear();
    }
    printw("Extra runs given by %s\n", team1);
    scanw("%d", &extra1);
    f = 1;
    clear();

    printw("Enter the details of the batters of %s\n", team2);
    while (f != 0)
    {
        printw("Enter name, runs: ");
        refresh();
        getnstr(t2[t2c].name, sizeof(t2[t2c].name) - 1);
        scanw("%d", &t2[t2c].run);
        s2 += t2[t2c].run;
        t2c++;

        printw("Enter 1 for next batter or enter 0 to enter bowlers: ");
        refresh();
        scanw("%d", &f);
        clear();
    }

    f = 1;
    clear();

    printw("Enter the details of the bowlers of %s\n", team2);
    while (f != 0)
    {
        printw("Enter name, overs, wickets, runs given: ");
        refresh();
        getnstr(t2b[t2bc].name, sizeof(t2b[t2bc].name) - 1);
        scanw("%d %d %d", &t2b[t2bc].overs, &t2b[t2bc].wickets, &t2b[t2bc].runs);
        w1 += t2b[t2bc].wickets;
        t2bc++;
        printw("Enter 1 for next bowler or enter 0 to print scoreboard: ");
        refresh();
        scanw("%d", &f);
        clear();
    }
    printw("Extra runs given by %s\n", team2);
    scanw("%d", &extra2);
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
    for (int i = 0; i < t2c; i++)
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
    printw("Scoreboard saved successfully in the file: %s\n", fname);
    refresh();
    getch();  // Wait for user input
    endwin(); // End ncurses
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
