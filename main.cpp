#include <curses.h>

#include "board.h"

#define WIDTH 44
#define HEIGHT 19
// 3x3 space per token and one space in between tokens and edges

player_color_t play_game(WINDOW *main_win, WINDOW *bttm_win, player_color_t (*board)[6][7]);
void display_winner(WINDOW *main_win, WINDOW *bttm_win, player_color_t winner);

int main(int argc, char *argv[]) {

    player_color_t winner;
    player_color_t board[6][7];

    for (int i = 0; i < 6; i++) {
        for (int k = 0; k < 7; k++) {
            board[i][k] = NONE;
        }
    }

    initscr();
    raw();
    start_color();
    cbreak();
    noecho();
    curs_set(0);

    init_pair((int) RED, COLOR_RED, COLOR_RED);
    init_pair((int) YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair((int) NONE, COLOR_BLACK, COLOR_BLACK);
    init_pair(BOARD_COLOR, COLOR_BLACK, COLOR_BLUE);
    init_pair(SELECT, COLOR_WHITE, COLOR_WHITE);

    WINDOW *main_win = subwin(stdscr, HEIGHT, WIDTH, 0, 0);
    WINDOW *bttm_win = subwin(stdscr, 2, WIDTH, HEIGHT, 0);

    wbkgd(main_win, COLOR_PAIR(BOARD_COLOR));

    keypad(bttm_win, true);

    winner = play_game(main_win, bttm_win, &board);

    display_winner(main_win, bttm_win, winner);
    
    delwin(main_win);
    delwin(bttm_win);

    endwin();
    exit_curses(0);

    return 0;
}