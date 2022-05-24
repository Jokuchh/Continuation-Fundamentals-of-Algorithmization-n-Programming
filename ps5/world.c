#include "world.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

struct container* create_world() {
    struct room *room = create_room("zero", "0");
    struct container *world = NULL;
    struct item *item = create_item("first", "first item", 0);
    add_item_to_room(room, item);
    world = create_container(world, ROOM, room);
    room = create_room("one", "1");

    item = create_item("second", "second item", 0);
    add_item_to_room(room, item);
    item = create_item("third", "third item", 0); add_item_to_room(room, item);
    item = create_item("fourth", "fourth item", 0); add_item_to_room(room, item);
    item = create_item("fifth", "fifth item", 0); add_item_to_room(room, item);

    create_container(world, ROOM, room); room = create_room("two", "2"); 
    create_container(world, ROOM, room); room = create_room("three", "3");
    create_container(world, ROOM, room); room = create_room("four", "4");
    create_container(world, ROOM, room); room = create_room("five", "5");
    create_container(world, ROOM, room); room = create_room("six", "6");
    create_container(world, ROOM, room); room = create_room("seven", "7");
    create_container(world, ROOM, room); room = create_room("eight", "8");
    create_container(world, ROOM, room); room = create_room("nine", "9");
    create_container(world, ROOM, room); room = create_room("ten", "10");
    create_container(world, ROOM, room); room = create_room("eleven", "11");
    create_container(world, ROOM, room); room = create_room("twelve", "12");
    create_container(world, ROOM, room); room = create_room("thirteen", "13");
    create_container(world, ROOM, room); room = create_room("fourteen", "14");
    create_container(world, ROOM, room);
    return world;
}

struct container* add_room_to_world(struct container* world, struct room* room) {
    if (room == NULL) {
        return NULL;
    }
    struct container *new_room;
    if (get_from_container_by_name(world, room->name)) {
        return NULL;
    }
    else {
        new_room = create_container(world, ROOM, room);
    }
    return new_room;
}

struct room* get_room(struct container* world, char* name) {
    if (name == NULL) {
        return NULL;
    }
    if (strlen(name) == 0) {
        return NULL;
    }
    struct container* pointer = world;
    int found = 0;
    int compare = 0;
    struct room* entry = NULL;
    while (pointer != NULL && found == 0) {
        compare = strcmp(pointer->room->name, name);
        if (compare == 0) {
            found = 1;
            entry = pointer->room;
        }
        pointer = pointer->next;
    }
    return entry;
}

struct container* destroy_world(struct container* world) {
    if (world == NULL) {
        return NULL;
    }
    struct container* pointer = world;
    struct container* pointer_next = NULL;
    enum container_type type = ROOM;
    while (pointer != NULL) {
        pointer_next = pointer->next;
        if (type == ROOM) {
            pointer->room = destroy_room(pointer->room);
            pointer->next = NULL;
            free(pointer);
        }
        pointer = pointer_next;
    }
    world = NULL;
    return world;
}
