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
    food_pos_x = rand() % (WIDTH - 3) + 1;   // ���������� �᫮ �� 1 �� WIDTH - 3
    food_pos_y = rand() % (HEIGHT - 2) + 1;  // ���������� �᫮ �� 1 �� HEIGHT - 2
}

int main() {
    snake_pos_x[0] = WIDTH / 2;
    snake_pos_y[0] = HEIGHT / 2;
    generate_food();
    auto time = (double) clock() / CLOCKS_PER_SEC;
    while (is_active) {

        if (_kbhit()) {
            int ch = _getch(); // ���뢠��� ������

            if (ch == 224) { // �᫨ �뫠 ����� ᯥ樠�쭠� ������ (��५�� ��� ��㣠�)
                int arrow = _getch(); // ���뢠�� ᫥���騩 ᨬ��� ��� ��।������ ���ࠢ�����

                switch (arrow) {
                    case 72:  // ��५�� �����
                        snake_dir = UP;
                        break;
                    case 75:  // ��५�� �����
                        snake_dir = LEFT;
                        break;
                    case 80:  // ��५�� ����
                        snake_dir = DOWN;
                        break;
                    case 77:  // ��५�� ��ࠢ�
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
                    case 'q':  // �������⥫쭠� ������ ��� ��室�
                    case 'Q':
                        is_active = false;
                        break;
                }
            }
        }

        if ((double) clock() / CLOCKS_PER_SEC - time >= 1.0 / fps) {
            time = (double) clock() / CLOCKS_PER_SEC;

            system(CLEAR);

            ///����頥� ���� �� �����
            for (int i = 0; i < snake_length; i++) {
                map[snake_pos_y[i] * WIDTH + snake_pos_x[i]] = snake;
            }

            map[food_pos_y * WIDTH + food_pos_x] = food;

            ///�뢮��� �����
            cout << map;

            cout << "Score: " << snake_length - 1 << endl;

            ///���⪠ ᮤ�ন���� ��� ��६����� �����
            for (int i = 0; i < snake_length; i++) {
                map[snake_pos_y[i] * WIDTH + snake_pos_x[i]] = ' ';
            }

            ///������� ������
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