#include <iostream>
#include <conio.h>

using namespace std;

#define CLEAR "cls"

char map[] = "#################################################\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#                                               #\n"
             "#################################################\n";

const int WIDTH = 50;
const int HEIGHT = 20;
const int MAX_SNAKE_SIZE = (WIDTH - 3) * (HEIGHT - 2);
bool is_active = true;
int snake_pos_x[MAX_SNAKE_SIZE] = {0};
int snake_pos_y[MAX_SNAKE_SIZE] = {0};
int snake_length = 1;
char snake = 'o';

const int UP = 0;
const int LEFT = 1;
const int DOWN = 2;
const int RIGHT = 3;

int food_pos_x;
int food_pos_y;
char food = '*';

int snake_dir = UP;

unsigned int fps = 5;

void generate_food() {
    srand(time(nullptr));
    food_pos_x = rand() % (WIDTH - 3) + 1;   // Генерируется число от 1 до WIDTH - 3
    food_pos_y = rand() % (HEIGHT - 2) + 1;  // Генерируется число от 1 до HEIGHT - 2
}

int main() {
    snake_pos_x[0] = WIDTH / 2;
    snake_pos_y[0] = HEIGHT / 2;
    generate_food();
    auto time = (double) clock() / CLOCKS_PER_SEC;
    while (is_active) {

        if (_kbhit()) {
            int ch = _getch(); // Считывание клавиши

            if (ch == 224) { // Если была нажата специальная клавиша (стрелка или другая)
                int arrow = _getch(); // Считываем следующий символ для определения направления

                switch (arrow) {
                    case 72:  // стрелка вверх
                        snake_dir = UP;
                        break;
                    case 75:  // стрелка влево
                        snake_dir = LEFT;
                        break;
                    case 80:  // стрелка вниз
                        snake_dir = DOWN;
                        break;
                    case 77:  // стрелка вправо
                        snake_dir = RIGHT;
                        break;
                }
            } else {
                switch (ch) {
                    case 'w':
                    case 'W':
                        snake_dir = UP;
                        break;
                    case 'a':
                    case 'A':
                        snake_dir = LEFT;
                        break;
                    case 's':
                    case 'S':
                        snake_dir = DOWN;
                        break;
                    case 'd':
                    case 'D':
                        snake_dir = RIGHT;
                        break;
                    case 'q':  // Дополнительная клавиша для выхода
                    case 'Q':
                        is_active = false;
                        break;
                }
            }
        }

        if ((double) clock() / CLOCKS_PER_SEC - time >= 1.0 / fps) {
            time = (double) clock() / CLOCKS_PER_SEC;

            system(CLEAR);

            ///Помещаем змею на карту
            for (int i = 0; i < snake_length; i++) {
                map[snake_pos_y[i] * WIDTH + snake_pos_x[i]] = snake;
            }

            map[food_pos_y * WIDTH + food_pos_x] = food;

            ///Выводим карту
            cout << map;

            cout << "Score: " << snake_length - 1 << endl;

            ///Очистка содержимого для переменной карты
            for (int i = 0; i < snake_length; i++) {
                map[snake_pos_y[i] * WIDTH + snake_pos_x[i]] = ' ';
            }

            ///Двигаем змейку
            for (int i = snake_length; i != 0; i--) {
                snake_pos_y[i] = snake_pos_y[i - 1];
                snake_pos_x[i] = snake_pos_x[i - 1];
            }
            if (snake_dir == UP) {
                snake_pos_y[0]--;
            }
            if (snake_dir == LEFT) {
                snake_pos_x[0]--;
            }
            if (snake_dir == DOWN) {
                snake_pos_y[0]++;
            }
            if (snake_dir == RIGHT) {
                snake_pos_x[0]++;
            }

            if (snake_pos_x[0] == food_pos_x && snake_pos_y[0] == food_pos_y) {
                snake_length++;
                generate_food();
            }

            if (snake_pos_x[0] == 0 || snake_pos_x[0] == WIDTH - 2
                || snake_pos_y[0] == 0 || snake_pos_y[0] == HEIGHT - 1) {
                is_active = false;
            }

            for (int i = 1; i < snake_length; i++) {
                if (snake_pos_x[0] == snake_pos_x[i] && snake_pos_y[0] == snake_pos_y[i]) {
                    is_active = false;
                }
            }
        }
    }

    cout << "You lose :( Thank you for the game." << endl;

    return 0;
}