#include "item.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct item* create_item(char* name, char* description, unsigned int properties) {
    printf("create item\n");
    if (name != NULL && description != NULL) {
        if (strlen(name) == 0 || strlen(description) == 0) {
            return NULL;
        }
    }
    else {
        return NULL;
    }
    struct item* new_item = calloc(1, sizeof(struct item));
    new_item->name = calloc(1, strlen(name) + 1);
    new_item->properties = properties;
    new_item->description = calloc(1, strlen(description) + 1);
    strcpy(new_item->name, name);
    strcpy(new_item->description, description);
    printf("end of ITEM creation\n");
    return new_item;
}

struct item* destroy_item(struct item* item) {
    if (item == NULL) {
        return NULL;
    }
    if (item->description != NULL) {
        free(item->description);
    }
    if (item->name != NULL) {
        free(item->name);
    }
    free(item);
    item = NULL;
    return item;
}
