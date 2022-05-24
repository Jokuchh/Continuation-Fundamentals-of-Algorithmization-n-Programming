#include "backpack.h"
#include "command.h"
#include "container.h"
#include "game.h"
#include "item.h"
#include "parser.h"
#include "room.h"
#include "world.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    struct item* empty_item = NULL;

    struct parser* empty_parser = NULL;
    struct backpack* empty_backpack = NULL;
    struct room* empty_room = NULL;

    struct command* empty_command = NULL;
    struct container* empty_container = NULL;
    struct game* empty_game = NULL;

    empty_parser = create_parser();  
    empty_parser = destroy_parser(empty_parser);
    empty_container = create_container(empty_container, ROOM, NULL);
    empty_container = destroy_containers(empty_container);
    get_from_container_by_name(NULL, NULL);
    empty_container = remove_container(empty_container, NULL);
    printf("500\n");
    empty_command = create_command(NULL, NULL, NULL, 12);
    printf("600\n");
    empty_command = destroy_command(empty_command);
    empty_backpack = create_backpack(2);
    printf("750\n");
    empty_backpack = destroy_backpack(empty_backpack);
    printf("800\n");
    add_item_to_backpack(empty_backpack, NULL);
    printf("900\n");
    delete_item_from_backpack(empty_backpack, NULL);
    printf("1000\n");
    empty_item = get_item_from_backpack(empty_backpack, NULL);
    empty_container = create_world();
    empty_container = add_room_to_world(empty_container, NULL);
    empty_container = destroy_world(NULL);
    empty_room = get_room(NULL, NULL);
    printf("1500\n");
    empty_parser = create_parser();
    empty_room = create_room(NULL, NULL);
    empty_room = destroy_room(empty_room);
    set_exits_from_room(NULL, NULL, NULL, NULL, NULL);
    printf("1700\n");
    empty_item = create_item("name", NULL, 2);
    printf("1800\n");
    empty_item = destroy_item(empty_item);
    play_game(empty_game);
    printf("2000\n");
    empty_parser = destroy_parser(empty_parser);
    empty_command = parse_input(empty_parser, NULL);
    printf("2200\n");
    empty_game = create_game();
    printf("2300\n");
    show_room(empty_room);
    printf("2500\n");
    delete_item_from_room(empty_room, NULL);
    add_item_to_room(empty_room, NULL);
    printf("3000\n");
    empty_item = get_item_from_room(NULL, NULL);
    empty_game = destroy_game(empty_game);
    execute_command(empty_game, NULL);
}
