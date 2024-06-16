#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "drone.h"
#include "field.h"
#include "menu.h"

extern struct Drone drones[MAX_DRONES];

void endGame() {
    endwin();
    printf("Collected pumpkins: %d\n", drones[0].score);
    exit(0);
}

int main() {
    int droneCount = 1;
    int mode = 0;

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE); 
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); 
    init_pair(2, COLOR_BLUE, COLOR_BLACK); 
    init_pair(3, COLOR_GREEN, COLOR_BLACK); 
    nodelay(stdscr, FALSE);
    startMenu(&droneCount, &mode);
    nodelay(stdscr, TRUE);
    setupField();
    setupDrones(droneCount);
    while (1) {
        erase(); 
        drawField();
        drawDrones();
        if (mode == 0) {
            manualInput(&mode);
        } else if (mode == 1) {
            autoPilot();
        }
        logicDrones();
        mvprintw(HEIGHT + 2, 0, "Collected pumpkins: %d", drones[0].score);
        mvprintw(HEIGHT + 3, 0, "Press 'L' to toggle autopilot");
        mvprintw(HEIGHT + 4, 0, "Press 'E' to end the game");
        refresh();
        usleep(DELAY);
    }

    endGame();
    return 0;
}
