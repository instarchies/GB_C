#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define WIDTH 40
#define HEIGHT 20
#define INITIAL_DELAY 100000

struct Snake {
    int x, y;
    int tailX[100], tailY[100];
    int nTail;
    int dir;
};

struct Apple {
    int x, y;
};


void setColor(int objectType){
    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(3));
    switch(objectType){
        case 1: 
            attron(COLOR_PAIR(1));
            break;
        case 2:
            attron(COLOR_PAIR(2));
            break;
        case 3: 
            attron(COLOR_PAIR(3));
            break;
    }
}

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

void Draw(struct Snake snake, struct Apple apple, int score, int snakeColor) {
    clear();
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(0, i, "#");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                mvprintw(i + 1, j, "#");
            if (i == snake.y && j == snake.x) {
                setColor(snakeColor); // Use selected snake color
                mvprintw(i + 1, j + 1, "@");
                setColor(0); 
            } else if (i == apple.y && j == apple.x) {
                setColor(3); 
                mvprintw(i + 1, j + 1, "*");
                setColor(0); 
            } else {
                int print = 0;
                for (int k = 0; k < snake.nTail; k++) {
                    if (snake.tailX[k] == j && snake.tailY[k] == i) {
                        setColor(snakeColor); // Use selected snake color
                        mvprintw(i + 1, j + 1, "*");
                        setColor(0); 
                        print = 1;
                    }
                }
                if (print == 0)
                    mvprintw(i + 1, j + 1, " ");
            }
            if (j == WIDTH - 1)
                mvprintw(i + 1, j + 1, "#");
        }
    }

    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(HEIGHT + 1, i, "#");
    mvprintw(HEIGHT + 2, 0, "Your score: %d", score);
    mvprintw(HEIGHT + 3, 0, "Press 'P' to pause.");
    refresh();
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
            *paused = !(*paused);
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
    case 1: 
        snake->x--;
        break;
    case 2:
        snake->x++;
        break;
    case 3:
        snake->y--;
        break;
    case 4: 
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
        *delay = *delay - 5000; 
        if (*delay < 5000) 
            *delay = 5000;
    }
}

void startMenu(int *snakeColor) {
    const char *choices[] = {
        "Start Game",
        "Choose Snake Color",
        "Exit"
    };
    const char *colorChoices[] = {
        "Red",
        "Blue",
        "Green"
    };
    int n_choices = sizeof(choices) / sizeof(choices[0]);
    int n_colorChoices = sizeof(colorChoices) / sizeof(colorChoices[0]);
    int highlight = 0;
    int colorHighlight = 0;
    int choice = -1;
    int c;

    while (1) {
        clear();
        mvprintw(0, 0, "Welcome to Snake Game");
        for (int i = 0; i < n_choices; i++) {
            if (i == highlight)
                attron(A_REVERSE);
            mvprintw(i + 2, 2, "%s", choices[i]);  // Use format string
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
            case 10:  // Enter key
                choice = highlight;
                break;
            default:
                break;
        }

        if (choice != -1) {
            if (choice == 0) {
                // Start Game
                return;
            } else if (choice == 1) {
                // Choose Snake Color
                while (1) {
                    clear();
                    mvprintw(0, 0, "Choose Snake Color");
                    for (int i = 0; i < n_colorChoices; i++) {
                        if (i == colorHighlight)
                            attron(A_REVERSE);
                        mvprintw(i + 2, 2, "%s", colorChoices[i]);  // Use format string
                        if (i == colorHighlight)
                            attroff(A_REVERSE);
                    }
                    refresh();

                    c = getch();
                    switch (c) {
                        case KEY_UP:
                            colorHighlight = (colorHighlight == 0) ? n_colorChoices - 1 : colorHighlight - 1;
                            break;
                        case KEY_DOWN:
                            colorHighlight = (colorHighlight == n_colorChoices - 1) ? 0 : colorHighlight + 1;
                            break;
                        case 10:  // Enter key
                            *snakeColor = colorHighlight + 1; // 1 for Red, 2 for Blue, 3 for Green
                            break;
                        default:
                            break;
                    }

                    if (c == 10)  // If Enter key was pressed
                        break;
                }
            } else if (choice == 2) {
                // Exit
                endwin();
                exit(0);
            }
            choice = -1; // Reset choice after handling
        }
    }
}

int main() {
    struct Snake snake1;
    struct Apple apple;
    int score = 0;
    int delay = INITIAL_DELAY;
    int paused = 0;
    int snakeColor = 1; // Default to Red

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE); // Enable arrow keys
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); // Color for Snake (Red)
    init_pair(2, COLOR_BLUE, COLOR_BLACK); // Color for Snake (Blue)
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // Color for Apple

    startMenu(&snakeColor); // Show start menu and set snake color

    Setup(&snake1, &apple);

    while (1) {
        Draw(snake1, apple, score, snakeColor); // Pass snakeColor to Draw function
        Input(&snake1, &paused);
        if (!paused) {
            Logic(&snake1, &apple, &score, &delay);
            usleep(delay);
        }
    }

    endwin();
    return 0;
}
