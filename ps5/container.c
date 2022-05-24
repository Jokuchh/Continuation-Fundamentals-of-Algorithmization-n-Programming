#include "container.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct container* create_container(struct container* first, enum container_type type, void* entry) {
    if (entry == NULL) {
        return NULL;
    }
    if (entry == NULL) {
        printf("ProverOCKA\n");
    }
    printf("\nbefore container calloc\n");
    struct container* new_container = calloc(1, sizeof(struct container));
    printf("\nafter container calloc\n");
    new_container->type = type;
    if (first == NULL) {
        first = new_container;
        if (type == ROOM) {
            new_container->room = entry;
            if (entry == NULL) {
                printf("Tut?\n");
            }
        }
        else if (type == ITEM) {
            if (entry == NULL) {
                printf("Alo\n");
            }
            printf("set item entry\n");
            new_container->item = entry;
        }
        else if (type == COMMAND) {
            if (entry == NULL) {
                printf("Alebo tu?\n");
            }
            new_container->command = entry;
        }
        else if (type == TEXT) {
            new_container->text = entry;
        }
        return new_container;
    }
    else if (first->type != type) {
        free(new_container);
        new_container = NULL;
        return NULL;
    }
    if (type == ROOM) {
        new_container->room = entry;
    }
    else if (type == ITEM) {
        if (entry == NULL) {
            printf("Ne tu, urcite\n");
        }
        new_container->item = entry;
    }
    else if (type == COMMAND) {
        new_container->command = entry;
    }
    else if (type == TEXT) {
        new_container->text = entry;
        if (entry == NULL) {
            printf("Ne tu, urcite\n");
        }
    }

    struct container* pointer = first;
    while (pointer->next != NULL) {
        pointer = pointer->next;
    }
    pointer->next = new_container;
    return new_container;
}

void* get_from_container_by_name(struct container *first, const char *name) {
    if (first == NULL || name == NULL) {
        return NULL;
    }

    struct container* pointer = first;
    enum container_type type = first->type;
    int found = 0;
    int compare = 0;
    void* entry = NULL;

    while (pointer != NULL && found == 0) {
        if (type == ROOM) {
            compare = strcmp(pointer->room->name, name);
            if (compare == 0) {
                found = 1;
                entry = pointer->room;
            }
        }
        else if (type == ITEM) {
            compare = strcmp(pointer->room->name, name);
            if (compare == 0) {
                found = 1;
                entry = pointer->item;
            }
            if (name == NULL) {
                printf("tu, urcite\n");
            }
        }
        else if (type == COMMAND) {
            compare = strcmp(pointer->room->name, name);
            if (compare == 0) {
                found = 1;
                entry = pointer->command;
            }
        }
        else if (type == TEXT) {
            compare = strcmp(pointer->text, name);
            if (compare == 0) {
                found = 1;
                entry = pointer->text;
            }
        }
        pointer = pointer->next;
    }
    return entry;
}

struct container* remove_container(struct container *first, void *entry) {
    if (first == NULL || entry == NULL) {
        return first;    // alebo FIRST
    }
    struct container* pointer = first;
    int compare;
    
    enum container_type type = first->type;
    struct container* step_back = NULL;
    while (pointer != NULL) {
        if (type == ROOM) {
            compare = memcmp(pointer->room, entry, sizeof(struct room));
            if (compare == 0) {
                pointer->room = NULL;
                if (step_back != NULL) {
                    step_back->next = pointer->next;
                }
                else {
                    first = NULL;
                }
                free(pointer);
                pointer = NULL;
                return first;
            }
        }
        else if (type == ITEM) {
            compare = memcmp(pointer->item, entry, sizeof(struct item));
            if (compare == 0) {
                pointer->item = NULL;
                if (step_back != NULL) {
                    step_back->next = pointer->next;
                }
                else {
                    first = NULL;
                }
                free(pointer);
                pointer = NULL;
                return first;
            }
        }
        else if (type == COMMAND) {
            compare = memcmp(pointer->command, entry, sizeof(struct room));
            if (compare == 0) {
                pointer->command = NULL;
                if (step_back != NULL) {
                    step_back->next = pointer->next;
                }
                else {
                    first = NULL;
                }
                free(pointer);
                pointer = NULL;
                return first;
            }
        }
        else if (type == TEXT) {
            compare = strcmp(pointer->text, entry);
            if (compare == 0) {
                pointer->text = NULL;
                if (step_back != NULL) {
                    step_back->next = pointer->next;
                }
                else {
                    first = NULL;
                }
                free(pointer);
                pointer = NULL;
                return first;
            }
        }
        step_back = pointer;
        pointer = pointer->next;
    }
    return first;
}

struct container* destroy_containers(struct container* first) {
    if (first == NULL) {
        return NULL;
    }
    struct container* pointer = first;
    struct container* pointer_next = NULL;
    enum container_type type = first->type;
    while (pointer != NULL) {
        pointer_next = pointer->next;
        if (type == ROOM) {
            pointer->room = destroy_room(pointer->room);
            pointer->next = NULL;
            free(pointer);
        }
        else if (type == TEXT) {
            free(pointer->text);
            pointer->next = NULL;
            free(pointer);
        }
        if (type == COMMAND) {
            pointer->command = destroy_command(pointer->command);
            pointer->next = NULL;
            free(pointer);
        }
        if (type == ITEM) {
            pointer->item = destroy_item(pointer->item);
            pointer->next = NULL;
            free(pointer);
        }
        pointer = pointer_next;
    }
    return NULL;
}
