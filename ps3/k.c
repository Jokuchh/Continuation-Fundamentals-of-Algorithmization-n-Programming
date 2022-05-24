#include <stdlib.h>
#include <math.h>
#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game) {
    int m, n;
    for (m = 0; m < SIZE; m++){
        for (n = 0; n < SIZE; n++){
            if (game.board[m][n] == 'K'){
                return true;
            }
        }
    }
    return false;
}

bool is_move_possible(const struct game game) {
    int m, n;
    for (m = 0; m < SIZE; m++)
        for (n = 0; n < SIZE; n++) {
            if((game.board[m][n] == game.board[m][n+1] && n != SIZE-1) || (game.board[m][n] == game.board[m+1][n] && m != SIZE-1)) {
                return true;
            }
            if(game.board[m][n] == ' ') {
                return true;
            }
        }
    return false;
}


bool move_up(struct game *game) {
    bool res = false;
    int board_ind;
    for(int n = 0; n < SIZE; n++) {
        for(int m = 1; m < SIZE; m++) {
            if(game->board[m][n] != ' ') {
                for(board_ind = m; board_ind != SIZE*0 && game->board[board_ind-1][n] == ' '; board_ind--) {
                    game->board[board_ind-1][n] = game->board[board_ind][n];
                    game->board[board_ind][n] = ' ';
                    res = true;
                }
                if(board_ind != SIZE*0 && game->board[board_ind-1][n] != ' ')
                    if( game->board[board_ind-1][n] == game->board[board_ind][n]) {
                        game->board[board_ind-1][n] = (char)(game->board[board_ind-1][n] + 1);
                        game->board[board_ind][n] = ' ';
                        res = true;
                        game->score += (int)pow(2, game->board[board_ind-1][n] - 64);
                    }
            }
        }
    }
    return res;
}


bool move_down(struct game *game) {
    bool res = false;
    int board_ind;
    for(int n = 0; n < SIZE; n++) {
        for(int m = SIZE-2; m >= 0; m--) {
            if(game->board[m][n] != ' ') {
                for(board_ind = m; board_ind != SIZE-1 && game->board[board_ind+1][n] == ' '; board_ind++) {
                    game->board[board_ind+1][n] = game->board[board_ind][n];
                    game->board[board_ind][n] = ' ';
                    res = true;
                }
                if(board_ind != SIZE-1 && game->board[board_ind+1][n] != ' ')
                    if(game->board[board_ind+1][n] == game->board[board_ind][n]) {
                        game->board[board_ind+1][n] = (char)(game->board[board_ind+1][n] + 1);
                        game->board[board_ind][n] = ' ';
                        res = true;
                        game->score += (int)pow(2, game->board[board_ind+1][n] - 64);

                    }
            }
        }
    }
    return res;
}

bool move_left(struct game *game){
    bool res = false;
    int board_ind;
    for(int m = 0; m < SIZE; m++) {
        for(int n = 1; n < SIZE; n++) {
            if(game->board[m][n] != ' ') {
                for(board_ind = n; board_ind != 0 && game->board[m][board_ind-1] == ' '; board_ind--) {
                    game->board[m][board_ind-1] = game->board[m][board_ind];
                    game->board[m][board_ind] = ' ';
                    res = true;
                }
                if(board_ind != 0 && game->board[m][board_ind-1] != ' ')
                    if(game->board[m][board_ind-1] == game->board[m][board_ind]) {
                        game->board[m][board_ind-1] = (char)(game->board[m][board_ind-1] + 1);
                        game->board[m][board_ind] = ' ';
                        res = true;
                        game->score += (int)pow(2, game->board[m][board_ind-1] - 64);

                    }
            }
        }
    }
    return res;
}


bool move_right(struct game *game) {
    bool res = false;
    int board_ind;
    for(int m = 0; m < SIZE; m++) {
        for(int n = SIZE-2; n >= 0; n--) {
            if(game->board[m][n] != ' ') {
                for(board_ind = n; board_ind != SIZE-1 && game->board[m][board_ind+1] == ' '; board_ind++) {
                    game->board[m][board_ind+1] = game->board[m][board_ind];
                    game->board[m][board_ind] = ' ';
                    res = true;
                }
                if(board_ind != SIZE-1 && game->board[m][board_ind+1] != ' ')
                    if(game->board[m][board_ind+1] == game->board[m][board_ind]) {
                        game->board[m][board_ind+1] = (char)(game->board[m][board_ind+1] + 1);
                        game->board[m][board_ind] = ' ';
                        res = true;
                        game->score += (int)pow(2, game->board[m][board_ind+1] - 64);
                    }
            }
        }
    }
    return res;
}

bool update(struct game *game, int dy, int dx) {
    if( (dy != 0 && dy != -1 && dy != 1) || (dx != 0 && dx != -1 && dx != 1) || (dy != 0 && dx !=0) || (dy == 0 && dx == 0) ) {return false;}
    bool updated_b = false;
    if(dy == -1) updated_b = move_up(game);
    if(dy == 1) updated_b = move_down(game);
    if(dx == -1) updated_b = move_left(game);
    if(dx == 1) updated_b = move_right(game);
    return updated_b;
}
