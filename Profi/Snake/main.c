#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define WIDTH 40
#define HEIGHT 20
#define INITIAL_DELAY 100000 // Изначальная задержка 100000 микросекунд (0.1 секунды)

struct Snake {
    int x, y;
    int tailX[100], tailY[100];
    int nTail;
    int dir;
};

struct Apple {
    int x, y;
};

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

void Setup(struct Snake *snake, struct Apple *apple) {
    snake->x = WIDTH / 2;
    snake->y = HEIGHT / 2;
    apple->x = rand() % WIDTH;
    apple->y = rand() % HEIGHT;
    snake->dir = 0;
    snake->nTail = 0;
}

void Draw(struct Snake snake, struct Apple apple, int score) {
    system("clear");
    for (int i = 0; i < WIDTH+2; i++)
        printf("#");
    printf("\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");
            if (i == snake.y && j == snake.x)
                printf("@");
            else if (i == apple.y && j == apple.x)
                printf("*");
            else {
                int print = 0;
                for (int k = 0; k < snake.nTail; k++) {
                    if (snake.tailX[k] == j && snake.tailY[k] == i) {
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
    printf("Your score:%d\n", score);
    printf("Press 'P' to pause.\n");
}

void Input(struct Snake *snake, int *paused) {
    if (kbhit()) {
        char input = getchar();
        switch (input) {
        case 'a':
        case 'A':
            if (snake->dir != 2) 
                snake->dir = 1;
            break;
        case 'd':
        case 'D':
            if (snake->dir != 1) 
                snake->dir = 2;
            break;
        case 'w':
        case 'W':
            if (snake->dir != 4) 
                snake->dir = 3;
            break;
        case 's':
        case 'S':
            if (snake->dir != 3)
                snake->dir = 4;
            break;
        case 'x':
        case 'X':
            exit(0);
            break;
        case 'p':
        case 'P':
            *paused = !(*paused); // Переключаем состояние паузы
            break;
        }
    }
}

void Logic(struct Snake *snake, struct Apple *apple, int *score, int *delay) {
    int prevX = snake->tailX[0];
    int prevY = snake->tailY[0];
    int prev2X, prev2Y;
    snake->tailX[0] = snake->x;
    snake->tailY[0] = snake->y;
    for (int i = 1; i < snake->nTail; i++) {
        prev2X = snake->tailX[i];
        prev2Y = snake->tailY[i];
        snake->tailX[i] = prevX;
        snake->tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (snake->dir) {
    case 1: // LEFT
        snake->x--;
        break;
    case 2: // RIGHT
        snake->x++;
        break;
    case 3: // UP
        snake->y--;
        break;
    case 4: // DOWN
        snake->y++;
        break;
    default:
        break;
    }
    if (snake->x >= WIDTH) snake->x = 0; else if (snake->x < 0) snake->x = WIDTH - 1;
    if (snake->y >= HEIGHT) snake->y = 0; else if (snake->y < 0) snake->y = HEIGHT - 1;

    for (int i = 0; i < snake->nTail; i++)
        if (snake->tailX[i] == snake->x && snake->tailY[i] == snake->y)
            exit(0);
            

    if (snake->x == apple->x && snake->y == apple->y) {
        snake->nTail++;
        *score += 10;
        apple->x = rand() % WIDTH;
        apple->y = rand() % HEIGHT;
        // Увеличиваем скорость змеи при достижении нового уровня
        *delay = *delay - 5000; // Уменьшаем задержку на 0.01 секунды (10000 микросекунд)
        if (*delay < 5000) // Ограничиваем минимальную задержку
            *delay = 5000;
    }
}

int main() {
    srand(time(NULL));
    struct Snake snake;
    struct Apple apple;
    int score = 0;
    int paused = 0;
    int delay = INITIAL_DELAY;
    int printPausedMessage = 1; // Флаг для проверки, нужно ли выводить сообщение о паузе

    Setup(&snake, &apple);
    while (1) {
        if (!paused) {
            printPausedMessage = 1; // Восстанавливаем флаг, чтобы сообщение о паузе могло быть выведено, если пользователь снова нажмет 'P'
            Draw(snake, apple, score);
            Input(&snake, &paused);
            Logic(&snake, &apple, &score, &delay);
        } else {
            if (printPausedMessage) {
                printf("Paused. Press 'P' to resume.\n");
                printPausedMessage = 0; // Устанавливаем флаг, чтобы сообщение о паузе не выводилось снова до тех пор, пока игра не продолжится
            }
            Input(&snake, &paused);
        }
        usleep(delay); 
    }
    return 0;
}
