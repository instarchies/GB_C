#include "field.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

struct Pumpkin field[WIDTH][HEIGHT];

void setupField() {
    srand(time(NULL));
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            field[i][j].x = i;
            field[i][j].y = j;
            field[i][j].isRipe = 0;
        }
    }
    for (int i = 0; i < 3; i++) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        field[x][y].isRipe = 1;
    }
}

void drawField() {
    for (int i = 0; i < WIDTH + 2; i++) {
        mvprintw(0, i, "#");
        mvprintw(HEIGHT + 1, i, "#");
    }
    for (int i = 0; i < HEIGHT + 2; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH + 1, "#");
    }
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (field[i][j].isRipe) {
                mvprintw(j + 1, i + 1, "P");
            } else {
                mvprintw(j + 1, i + 1, ".");
            }
        }
    }
}

void updateField() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (rand() % 10 == 0) {
                field[i][j].isRipe = 1;
            }
        }
    }
}
