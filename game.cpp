#include "board.h"

#include <algorithm>

#define col_in_bounds(c) (0 <= c && c < 7)
#define row_in_bounds(r) (0 <= r && r < 6)


bool valid_move(int col, player_color_t (*board)[6][7])
{
    return (*board)[0][col] == NONE;
}

bool is_draw(player_color_t (*board)[6][7])
{
    int i;

    for (i = 0; i < 7; i++)
    {
        if ((*board)[0][i] == NONE)
        {
            return false;
        }
    }
    return true;
}

void place_token(player_color_t color, int col, player_color_t (*board)[6][7]) {
    int i;

    for (i = 5; i >= 0; i--)
    {
        if ((*board)[i][col] == NONE)
        {
            (*board)[i][col] = color;
            return;
        }
    }
}

bool is_win(player_color_t color, int start_col, player_color_t (*board)[6][7]) {
    int start_row, i, r, c, highest_count;;
    int count;

    for (i = 0; i < 7; i++) {
        if ((*board)[i][start_col] == color)
        {
            start_row = i;
            break;
        }
    }
    
    // check horizontal
    r = start_row;
    c = start_col;
    count = 0;

    while(col_in_bounds(c) && (*board)[r][c] == color)
    {
        count++;
        c++;
    }

    c = start_col - 1;
    while(col_in_bounds(c) && (*board)[r][c] == color)
    {
        count++;
        c--;
    }
    highest_count = count;


    // check vertical
    r = start_row;
    c = start_col;
    count = 0;

    while(row_in_bounds(r) && (*board)[r][c] == color)
    {
        count++;
        r++;
    }

    r = start_row - 1;
    while(row_in_bounds(r) && (*board)[r][c] == color)
    {
        count++;
        r--;
    }
    highest_count = std::max(highest_count, count);


    // check bottom-up diagonal
    r = start_row;
    c = start_col;
    count = 0;

    while(row_in_bounds(r) && col_in_bounds(c) && (*board)[r][c] == color)
    {
        count++;
        r--;
        c++;
    }

    r = start_row + 1;
    c = start_col - 1;
    while(row_in_bounds(r) && col_in_bounds(c) && (*board)[r][c] == color)
    {
        count++;
        r++;
        c--;
    }
    highest_count = std::max(highest_count, count);


    // check top-down diagonal
    r = start_row;
    c = start_col;
    count = 0;

    while(row_in_bounds(r) && col_in_bounds(c) && (*board)[r][c] == color)
    {
        count++;
        r++;
        c++;
    }

    r = start_row - 1;
    c = start_col - 1;
    while(row_in_bounds(r) && col_in_bounds(c) && (*board)[r][c] == color)
    {
        count++;
        r--;
        c--;
    }
    highest_count = std::max(highest_count, count);


    return highest_count >= 4;
}

player_color_t play_game(WINDOW *main_win, WINDOW *bttm_win, player_color_t (*board)[6][7])
{
    bool gameOver = false;
    int input, col;
    player_color_t color_turn  = RED;
    
    display_board(main_win, board);

    while (!gameOver) {
        if (is_draw(board)) return NONE;

        col = 3;
        while(1) {
            werase(bttm_win);

            wattron(bttm_win, COLOR_PAIR(SELECT));
            mvwprintw(bttm_win, 0, (col * 6) + 2, "    ");
            wattroff(bttm_win, COLOR_PAIR(SELECT));

            switch (color_turn)
            {
            case RED:
                mvwprintw(bttm_win, 1, 18, "Red's turn");
                break;
            case YELLOW:
                mvwprintw(bttm_win, 1, 18, "Yellow's turn");
            default:
                break;
            }

            wrefresh(bttm_win);

            input = wgetch(bttm_win);

            if (input == 27)
            {
                return NONE;
            }
            else if(input == KEY_RIGHT && col < 6)
            {
                col++;
            }
            else if(input == KEY_LEFT && col > 0)
            {
                col--;
            }
            else if (input == '\n' && valid_move(col, board))
            {
                break;
            }
        }

        place_token(color_turn, col, board);

        display_board(main_win, board);

        if (is_win(color_turn, col, board)) return color_turn;

        switch (color_turn )
        {
        case RED:
            color_turn = YELLOW;
            break;
        case YELLOW:
            color_turn = RED;
        default:
            break;
        }
    }

    return NONE;
}