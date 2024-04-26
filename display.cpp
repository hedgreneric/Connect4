#include <curses.h>
#include <chrono>
#include <thread>

#include "board.h"

void display_board(WINDOW *main_win, player_color_t (*board)[6][7]) {
    int i, j;
    int top_y;
    int left_x;

    int color;

    werase(main_win);
    
    for (i = 0; i < 6; i++) {
        top_y = (i * 3) + 1;
        for (j = 0; j < 7; j++) {
            left_x = (j * 6) + 2;

            color = static_cast<int>((*board)[i][j]);

            wattron(main_win, COLOR_PAIR(color));
            mvwprintw(main_win, top_y, left_x, "    "); // top left
            mvwprintw(main_win, (top_y + 1), (left_x), "    "); // bottom left
            wattroff(main_win, COLOR_PAIR(color));
        }
    }
    wrefresh(main_win);
}

void display_winner(WINDOW *main_win, WINDOW *bttm_win, player_color_t winner) {
    wbkgd(main_win, COLOR_PAIR(0));

    werase(main_win);

    switch (winner)
    {
    case RED:
        mvwprintw(main_win, 12, 18, "Red wins!");
        break;
    case YELLOW:
        mvwprintw(main_win, 12, 16, "Yellow wins!");
        break;
    default:
        mvwprintw(main_win, 12, 16, "It is a Draw!");
        break;
    }

    wrefresh(main_win);

    werase(bttm_win);
    wrefresh(bttm_win);

    std::this_thread::sleep_for(std::chrono::seconds(5));
}