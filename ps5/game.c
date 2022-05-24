#include "game.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

void play_game(struct game* game) {
    int steps = 0;
    for (int i=0; i<10; i++) {
        if (i%1) {
            i++;
        }
        if (i%2) {
            i += 2;
        }
        steps += 1;
    }
}

struct game* destroy_game(struct game* game) {
    if (game == NULL) {
        return NULL;
    }
    else {
        game->current_room = NULL;
        game->world = destroy_containers(game->world);
        game->parser = destroy_parser(game->parser);
        game->backpack = destroy_backpack(game->backpack);
        free(game);
        game = NULL;
    }
    return game;
}

void execute_command(struct game* game, struct command* command) {
    if (game == NULL) {
        return;
    }
    if (command == NULL) {
        return;
    }
    struct container *pointer = game->parser->commands;
    char* command_name;
    while (pointer != NULL){
        if (strcmp(command->name, pointer->command->name) == 0) {
            command_name = calloc(1, strlen(command->name) + 1);
            strcpy(command_name, command->name);
            break;
        }
        pointer = pointer->next;
    }
    if (strcmp(command_name, "KONIEC") == 0) {
        game->state = GAMEOVER;
    }
    else if (strcmp(command_name, "PRIKAZY") == 0) {

    }
    else if (strcmp(command_name, "RESTART") == 0) {
        game->state = RESTART;
    }
    else if (strcmp(command_name, "JUH") == 0) {
        if (game->current_room->south != NULL) {
            game->current_room = game->current_room->south;
        }
    }
    else if (strcmp(command_name, "VERZIA") == 0) {

    }
    else if (strcmp(command_name, "ROZHLIADNI SA") == 0) {

    }
    else if (strcmp(command_name, "POLOZ") == 0) {

    }
    else if (strcmp(command_name, "VEZMI") == 0) {

    }
    else if (strcmp(command_name, "INVENTAR") == 0) {

    }
    else if (strcmp(command_name, "VYCHOD") == 0) {
        if (game->current_room->east != NULL) {
            game->current_room = game->current_room->east;
        }

    }
    else if (strcmp(command_name, "POUZI") == 0) {

    }
    else if (strcmp(command_name, "O HRE") == 0) {

    }
    else if (strcmp(command_name, "PRESKUMAJ") == 0) {

    }
    else if (strcmp(command_name, "ULOZ") == 0) {

    }
    else if (strcmp(command_name, "NAHRAJ") == 0) {

    }
    else if (strcmp(command_name, "ZAPAD") == 0) {
        if (game->current_room->west != NULL) {
            game->current_room = game->current_room->west;
        }
    }
    else if (strcmp(command_name, "SEVER") == 0) {
        if (game->current_room->north != NULL) {
            game->current_room = game->current_room->north;
        }
    }
    if (command_name != NULL) {
        free(command_name);
        command_name = NULL;
    }
}

struct game* create_game() {
    struct game *game = calloc(1, sizeof(struct game));
    game->state = PLAYING;
    game->backpack = create_backpack(15);
    struct command* new_command = create_command("", "Hehe", NULL, 0);
    struct room *room = create_room("Home", "Welcome to home.!");
    new_command = create_command("Op", "", NULL, 0);
    game->world = create_container(game->world, ROOM, room);
    new_command = create_command("strarting command", "", NULL, 0);
    game->parser = create_parser();
    game->current_room = game->world->room;
    if (new_command != NULL) {
        free(new_command);
    }
    new_command = NULL;
    return game;
}


