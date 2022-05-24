#include "backpack.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct backpack* create_backpack(const int capacity) {
    printf("create backpack\n");
    struct backpack* new_backpack = calloc(1, sizeof(struct backpack));
    new_backpack->size = 0;
    new_backpack->capacity = capacity;
    printf("end of creation backpack\n");
    return new_backpack;
}

struct backpack* destroy_backpack(struct backpack* backpack) {
    if (backpack == NULL) {
        return NULL;
    }
    backpack->items = NULL;

    free(backpack);
    backpack = NULL;

    return backpack;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item) {
    printf("\nAdd item to backpack\n");
    if (backpack == NULL) {
        return false;
    }
    if (item == NULL) {
        return false;
    }
    bool returned_value = true;
    int movable = item->properties & MOVABLE;
    struct container *pointer = backpack->items;
    if (backpack == NULL || backpack->size >= backpack->capacity) {
        printf("0\n");
        returned_value =  false;
    }
    if (returned_value) {
        if (item == NULL) {
            returned_value =  false;
            printf("1\n");
        }
        if (returned_value) {
            
            if (movable != 1) {
                returned_value =  false;
                printf("2\n");
            }
            if (returned_value) {
                
                if (pointer == NULL) {
                    printf("if before create_container()\n");
                    backpack->items = create_container(backpack->items, ITEM, item);
                    backpack->size++; 
                    printf("if after create_container()\n");
                }
                else {
                    printf("else before create_container()\n");
                    create_container(backpack->items, ITEM, item);
                    backpack->size++;
                    printf("else after create_container()\n");
                }
            }
        }
    }
    return returned_value;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item) {
    if (backpack ==  NULL) {
        return;
    }
    if (item == NULL) {
        return;
    }

    struct container* pointer = backpack->items;
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
                backpack->items = NULL;
            }
            free(pointer);
            pointer = NULL;
            backpack->size -= 1;
            break;
        }
        step_back = pointer;
        pointer = pointer->next;
    }
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name) {
    if (backpack == NULL || name == NULL) {
        return NULL;
    }
    if (strlen(name) == 0) {
        return NULL;
    }
    struct container* pointer = backpack->items;
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
