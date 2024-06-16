#ifndef DRONE_H
#define DRONE_H

#define MAX_DRONES 5
#define WIDTH 40
#define HEIGHT 20
#define DELAY 300000 

struct Drone {
    int x, y;
    int dir;
    int tailX[100], tailY[100];
    int nTail;
    int score;
};

extern struct Drone drones[MAX_DRONES]; 

void setupDrones(int count);
void drawDrones();
void manualInput(int *mode);
void autoPilot();
void logicDrones();
void endGame(); 

#endif 
