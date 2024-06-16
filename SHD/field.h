#ifndef FIELD_H
#define FIELD_H

#define WIDTH 40
#define HEIGHT 20

struct Pumpkin {
    int x, y;
    int isRipe;
};

void setupField();
void drawField();
void updateField();

extern struct Pumpkin field[WIDTH][HEIGHT];

#endif
