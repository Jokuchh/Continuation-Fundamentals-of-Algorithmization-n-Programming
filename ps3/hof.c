#include <stdio.h>
#include <string.h>
#include "hof.h"


int load(struct player list[]) {
    FILE *game_save;
    game_save = fopen(HOF_FILE, "r");
    if (game_save == NULL) {
    return -1;
    }
    int buff = 0, count;
    char chr_temp[100];
    for(count = 0; fscanf(game_save, "%s %d ", chr_temp, &buff) == 2; count++) {
        strcpy(list[count].name, chr_temp);
        list[count].score = buff;
    }
    fclose(game_save);
    if (count == 0) {return 0;}
    for (int n = 0; n < count - 1; n++) {
        for (int k = 0; k < count-n-1; k++) {
            if (list[k].score < list[k+1].score) {
                struct player tmp_pl_struct;
                strcpy(tmp_pl_struct.name, list[k].name);
                tmp_pl_struct.score = list[k].score;
                strcpy(list[k].name, list[k+1].name);
                list[k].score = list[k+1].score;
                strcpy(list[k+1].name, tmp_pl_struct.name);
                list[k+1].score = tmp_pl_struct.score;
            }
        }
    }      
    return count;
}
bool save(const struct player list[], const int size) {
    FILE *game_save;
    game_save = fopen(HOF_FILE, "w");
    for (int pl_index = 0; pl_index < size; pl_index ++) {
if (fprintf(game_save, "%s %d\n", list[pl_index].name, list[pl_index].score) == 0) {
fclose(game_save);
return false;
}
    }
    fclose(game_save);
    return true;
}

bool add_player(struct player list[], int* size, const struct player player) {
    bool success = false;
    int sorting_vr;
    if (*size == 0) {
        strcpy(list[0].name, player.name);
        list[0].score = player.score;
        *size = *size + 1;
        return true;
    }
    int pl_index = 0;
    while (pl_index < *size) {
        if (player.score >= list[pl_index].score) {
            if(*size != 10) {
            sorting_vr = *size;
            } else {
            sorting_vr = *size-1;
            }
            for(;sorting_vr > pl_index;) {
                    list[sorting_vr].score = list[sorting_vr-1].score;
                    strcpy(list[sorting_vr].name, list[sorting_vr-1].name);
                    sorting_vr = sorting_vr - 1;
            }
            list[pl_index].score = player.score;
            strcpy(list[pl_index].name, player.name);
            if (*size != 10) {
            *size = *size + 1;
            }
            success = true;
            break;
        }
        pl_index++;
    }
    if(*size != 10 && success != true) {
        strcpy(list[*size].name, player.name);
        list[*size].score = player.score;
        *size = *size + 1;
        success = true;
    }
    return success;
}


