#include <stdio.h>
#include <string.h>
#include "k.h"
#include "ui.h"
#include "hof.h"

int main(){
struct game game = {
    .board = {
        {'A', ' ', ' ', ' '},
        {'B', ' ', ' ', 'B'},
        {'C', 'C', 'C', ' '},
        {'D', 'D', 'D', 'D'}
    },
    .score = 1
};
printf("MAIN START\n");
struct player list[10] = {
    {.score=  547, .name="John"},
    {.score=  421, .name="Samuel"}
};
struct player player = {.name="Samuel", .score=734};
int size = 2;
printf("MAIN START LOAD\n");
//size = load(list);
printf("%s  %d\n", player.name, player.score);
printf("size:%d\n", size);
for (int i = 0; i < size; i++){
printf("%s %d\n", list[i].name, list[i].score);
}
printf("\n\n");
bool result1 = add_player(list, &size, player);
for (int i = 0; i < size; i++){
        printf("%s %d\n", list[i].name, list[i].score);
}
printf("size:%d  res: %d\n", size, result1);
size = load(list);
printf("RESULT1 %d\n", result1);
for (int i = 0; i < size; i++){
        printf("%s %d\n", list[i].name, list[i].score);
}

printf("is won: %d\n", is_game_won(game));
printf("is move possible: %d\n", is_move_possible(game));
bool result = update(&game, 0, -1);
printf("update is: %d\n", result);
for(int i = 0; i < SIZE; i++){
for(int j = 0; j < SIZE; j++){
printf("%c ", game.board[i][j]);
}
printf("\n");
}
add_random_tile(&game);
save(list, size);
render(game);
return 0;
}
