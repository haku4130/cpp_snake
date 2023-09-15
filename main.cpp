#include <iostream>
#include <Windows.h>

using namespace std;


void gotoxy(int x, int y) {
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

char map[] = "################################################\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "#                                              #\n"
             "################################################\n";

const int WIDTH = 50;
const int HEIGHT = 19;
const int MAX_SNAKE_SIZE = (WIDTH - 3) * (HEIGHT - 2);
bool is_active = true;
int snake_pos_x[MAX_SNAKE_SIZE] = {0};
int snake_pos_y[MAX_SNAKE_SIZE] = {0};
int snake_length = 1;
char snake = 'o';
int fps = 1;
const int UP = 0;
const int LEFT = 1;
const int DOWN = 2;
const int RIGHT = 3;
int snake_dir = UP;

int main() {
    snake_pos_x[0] = WIDTH / 2;
    snake_pos_y[0] = HEIGHT / 2;
    int time = clock();
    while (is_active) {
        if ((clock() - time) / CLOCKS_PER_SEC >= 1 / fps) {
            gotoxy(0, 0);
//            for (int i = snake_length; i != 0; i--) {
//                snake_pos_y[i] = snake_pos_y[i - 1];
//                snake_pos_x[i] = snake_pos_x[i - 1];
//            }
//            if (snake_dir == UP) {
//                snake_pos_y[0]--;
//            }
//            if (snake_dir == LEFT) {
//                snake_pos_x[0]--;
//            }
//            if (snake_dir == DOWN) {
//                snake_pos_y[0]++;
//            }
//            if (snake_dir == RIGHT) {
//                snake_pos_x[0]++;
//            }
            for (int i = 0; i < snake_length; i++) {
                map[snake_pos_y[i] * HEIGHT + snake_pos_x[i]] = snake;
            }
            cout << map;
            for (int i = 0; i < snake_length; i++) {
                map[snake_pos_y[i] * HEIGHT + snake_pos_x[i]] = ' ';
            }
        }
    }

    return 0;
}