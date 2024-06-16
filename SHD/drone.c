#include "drone.h"
#include "field.h"
#include <ncurses.h>
#include <stdlib.h>

struct Drone drones[MAX_DRONES];
int droneCount;

void setupDrones(int count) {
    droneCount = count;
    for (int i = 0; i < count; i++) {
        drones[i].x = WIDTH / 2;
        drones[i].y = HEIGHT / 2;
        drones[i].dir = 4;
        drones[i].nTail = 0;
        drones[i].score = 0;
    }
}

void drawDrones() {
    for (int i = 0; i < droneCount; i++) {
        mvprintw(drones[i].y + 1, drones[i].x + 1, "D");
        for (int j = 0; j < drones[i].nTail; j++) {
            mvprintw(drones[i].tailY[j] + 1, drones[i].tailX[j] + 1, "o");
        }
    }
}

void manualInput(int *mode) {
    int c = getch();
    switch(c) {
        case 'w': drones[0].dir = 1; break;
        case 's': drones[0].dir = 2; break;
        case 'a': drones[0].dir = 3; break;
        case 'd': drones[0].dir = 4; break;
        case 'x': endGame(); break;
        case 'e': endGame(); break;
        case 'l': *mode = (*mode == 0) ? 1 : 0; break;
    }
}

void autoPilot() {
    struct Drone *drone = &drones[0];
    int closestX = -1, closestY = -1;
    int minDist = WIDTH * HEIGHT;
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            if (field[i][j].isRipe) {
                int dist = abs(drone->x - i) + abs(drone->y - j);
                if (dist < minDist) {
                    minDist = dist;
                    closestX = i;
                    closestY = j;
                }
            }
        }
    }
    if (closestX != -1 && closestY != -1) {
        if (drone->x < closestX) drone->dir = 4; 
        else if (drone->x > closestX) drone->dir = 3; 
        else if (drone->y < closestY) drone->dir = 2; 
        else if (drone->y > closestY) drone->dir = 1; 
    }
}

void logicDrones() {
    for (int i = 0; i < droneCount; i++) {
        struct Drone *drone = &drones[i];
        for (int j = drone->nTail - 1; j > 0; j--) {
            drone->tailX[j] = drone->tailX[j - 1];
            drone->tailY[j] = drone->tailY[j - 1];
        }
        if (drone->nTail > 0) {
            drone->tailX[0] = drone->x;
            drone->tailY[0] = drone->y;
        }

        switch(drone->dir) {
            case 1: drone->y--; break;
            case 2: drone->y++; break;
            case 3: drone->x--; break;
            case 4: drone->x++; break;
        }
        if (drone->x >= WIDTH) { drone->x = WIDTH - 1; drone->dir = 3; } 
        if (drone->x < 0) { drone->x = 0; drone->dir = 4; } 
        if (drone->y >= HEIGHT) { drone->y = HEIGHT - 1; drone->dir = 1; } 
        if (drone->y < 0) { drone->y = 0; drone->dir = 2; } 
        for (int k = 0; k < drone->nTail; k++) {
            if (drone->tailX[k] == drone->x && drone->tailY[k] == drone->y) {
                endGame();
            }
        }

        if (field[drone->x][drone->y].isRipe) {
            drone->nTail++;
            drone->score += 1; 
            field[drone->x][drone->y].isRipe = 0;
            int newX, newY;
            do {
                newX = rand() % WIDTH;
                newY = rand() % HEIGHT;
            } while (field[newX][newY].isRipe);

            field[newX][newY].isRipe = 1;
        }
    }
}
