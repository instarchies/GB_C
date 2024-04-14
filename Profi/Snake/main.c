#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define WIDTH 40
#define HEIGHT 20
// добавил типо яблочка, ибо просто змейка скучно)
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
// нужна была функция kbhit, но в стандартной библиотеки ее нет((, поэтому я взял с инета ее и добавил для змейки ;)

void Setup() {
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    dir = STOP;
}

void Draw() {
    system("clear");
    for (int i = 0; i < WIDTH+2; i++)
        printf("#");
    printf("\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("@");
            else if (i == fruitY && j == fruitX)
                printf("*");
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("*");
                        print = 1;
                    }
                }
                if (print == 0)
                    printf(" ");
            }
                
            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH+2; i++)
        printf("#");
    printf("\n");
    printf("Score:%d\n", score);
}

void Input() {
    if (kbhit()) {
        char input = getchar();
        switch (input) {
        case 'a':
            if (dir != RIGHT) 
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) 
                dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) 
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'x':
            exit(0);
            break;
        case 'A':
            if (dir != RIGHT) 
                dir = LEFT;
            break;
        case 'D':
            if (dir != LEFT) 
                dir = RIGHT;
            break;
        case 'W':
            if (dir != DOWN) 
                dir = UP;
            break;
        case 'S':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'X':
            exit(0);
            break;
        }
        
        
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= WIDTH) x = 0; else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0; else if (y < 0) y = HEIGHT - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            exit(0);

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

int main() {
    srand(time(NULL));
    Setup();
    while (1) {
        Draw();
        Input();
        Logic();
        usleep(100000); 
    }
    return 0;
}
