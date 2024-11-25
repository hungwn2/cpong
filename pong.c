#include <ncurses.h>
#include <unistd.h> // For usleep

#define DELAY 30000 // Ball speed (microseconds)

//ball pos and dir
int ball_x, ball_y;
int ball_dir_x = 1, ball_dir_y = 1;

// paddle pos
int paddle_left_y, paddle_right_y;
int max_y, max_x;

void init() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // Non-blocking input
    getmaxyx(stdscr, max_y, max_x);
    paddle_left_y = paddle_right_y = max_y / 2;
    ball_x = max_x / 2;
    ball_y = max_y / 2;
}


void draw() {
    clear();
    mvprintw(paddle_left_y - 1, 2, "|");
    mvprintw(paddle_left_y, 2, "|");
    mvprintw(paddle_left_y + 1, 2, "|");

    mvprintw(paddle_right_y - 1, max_x - 3, "|");
    mvprintw(paddle_right_y, max_x - 3, "|");
    mvprintw(paddle_right_y + 1, max_x - 3, "|");
    mvprintw(ball_y, ball_x, "O");
    refresh();
}

void move_ball() {
ball_x += ball_dir_x;
ball_y += ball_dir_y;

    if (ball_y <= 0 || ball_y >= max_y - 1) {
        ball_dir_y *= -1;
    }

    if (ball_x == 3 && (ball_y == paddle_left_y || ball_y == paddle_left_y - 1 || ball_y == paddle_left_y + 1)) {
        ball_dir_x *= -1;
    }
    if (ball_x == max_x - 4 && (ball_y == paddle_right_y || ball_y == paddle_right_y - 1 || ball_y == paddle_right_y + 1)) {
        ball_dir_x *= -1;
    }

    if (ball_x <= 0 || ball_x >= max_x - 1) {
        ball_x = max_x / 2;
        ball_y = max_y / 2;
        ball_dir_x *= -1; 
    }
}

void move_paddle(int ch) {
    if (ch == 'w' && paddle_left_y > 1) {
        paddle_left_y--;
    } else if (ch == 's' && paddle_left_y < max_y - 2) {
        paddle_left_y++;
    }

    if (ch == KEY_UP && paddle_right_y > 1) {
        paddle_right_y--;
    } else if (ch == KEY_DOWN && paddle_right_y < max_y - 2) {
        paddle_right_y++;
    }
}

int main() {
    init();

    int ch;

    while (1) {
        ch = getch();
        move_paddle(ch);
        move_ball();
        draw();
        usleep(DELAY); 
    }

    endwin();
    return 0;
}
