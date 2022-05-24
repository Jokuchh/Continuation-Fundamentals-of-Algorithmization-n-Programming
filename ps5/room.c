#include "room.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct room* create_room(char *name, char *description) {
    if (name == NULL || description == NULL) {
        return NULL;
    }
    if (strlen(name) == 0 || strlen(description) == 0) {
        return NULL;
    }
    struct room* new_room = calloc(1, sizeof(struct room));
    new_room->name = calloc(1, strlen(name)+1);
    strcpy(new_room->name, name);
    new_room->description = calloc(1, strlen(description)+1);
    strcpy(new_room->description, description);
    return new_room;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west) {
    if (room == NULL) {
        return;
    }
    room->north = north;
    room->south = south;
    room->east = east;
    room->west = west;
}

void show_room(const struct room* room) {
    if (room == NULL) {
        return;
    }
    if (room->name == NULL || strlen(room->name) == 0) {
        return;
    }
    if (room->description == NULL || strlen(room->description) == 0) {
        return;
    }
    printf("%s\n%s", room->name, room->description);
}

struct room* destroy_room(struct room* room) {
    if (room == NULL) {
        return NULL;
    }
    if (room->name != NULL) {
        free(room->name);
    }
    if (room->description != NULL) {
        free(room->description);
    }
    free(room);
    room = NULL;
    return NULL;
}

void add_item_to_room(struct room* room, struct item* item) {
    if (room == NULL || item == NULL) {
        return;
    }
    if (item->name && item->description != NULL) {
        if (strlen(item->name) == 0 || strlen(item->description) == 0) {
            return;
        }
    }
    else {
        return;
    }
    if (room->items != NULL) {
        create_container(room->items, ITEM, item);
    }
    else {
        room->items = create_container(room->items, ITEM, item);
    }
}

void delete_item_from_room(struct room* room, struct item* item) {
    if (room == NULL || item == NULL) {
        return;
    }
    struct container* pointer = room->items;
    //struct container* remember = NULL;
    struct container* step_back = NULL;
    int compare;
    while (pointer != NULL) {
        compare = memcmp(pointer->item, item, sizeof(struct item));
        if (compare == 0) {
            pointer->item = NULL;
            if (step_back != NULL) {
                step_back->next = pointer->next;
            }
            else {
                room->items = NULL;
            }
            free(pointer);
            pointer = NULL;
            break;
        }
        step_back = pointer;
        pointer = pointer->next;
    }
}

struct item* get_item_from_room(const struct room* room, const char* name) {
    if (room == NULL || name == NULL) {
        return NULL;
    }
    if (strlen(name) == 0) {
        return NULL;
    }
    struct container* pointer = room->items;

    int found = 0;
    int compare = 0;
    void* entry = NULL;
    while (pointer != NULL && found == 0) {
        compare = strcmp(pointer->item->name, name);
        if (compare == 0) {
            found = 1;
            entry = pointer->item;
        }
        pointer = pointer->next;
    }
    return entry;
}
