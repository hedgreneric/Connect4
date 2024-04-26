#include <curses.h>

#define BOARD_COLOR 10
#define SELECT 11

typedef enum player_color{
    NONE = 12,
    RED,
    YELLOW,
} player_color_t;

void display_board(WINDOW *main, player_color_t (*board)[6][7]);
