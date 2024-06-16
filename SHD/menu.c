#include "menu.h"
#include <ncurses.h>
#include <stdlib.h>

void startMenu(int *droneCount, int *mode) {
    const char *choices[] = {
        "Start Game",
        "Exit"
    };
    int n_choices = sizeof(choices) / sizeof(choices[0]);
    int highlight = 0;
    int choice = -1;
    int c;

    while (1) {
        clear();
        mvprintw(0, 0, "Welcome to Drone Control Program");
        for (int i = 0; i < n_choices; i++) {
            if (i == highlight)
                attron(A_REVERSE);
            mvprintw(i + 2, 2, "%s", choices[i]);  
            if (i == highlight)
                attroff(A_REVERSE);
        }
        refresh();

        c = getch();
        switch (c) {
            case KEY_UP:
                highlight = (highlight == 0) ? n_choices - 1 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == n_choices - 1) ? 0 : highlight + 1;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != -1) {
            if (choice == 0) {
                *mode = 0;
                return;
            } else if (choice == 1) {
                endwin();
                exit(0);
            }
            choice = -1;
        }
    }
}
