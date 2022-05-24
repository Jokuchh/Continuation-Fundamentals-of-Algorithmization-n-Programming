#include "command.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch) {
    if (name != NULL && description != NULL) {
        if (strlen(name) == 0 || strlen(description) == 0) {
            return NULL;
        }
    }
    else {
        return NULL;
    }
    struct command* new_command = calloc(1, sizeof(struct command));
    new_command->name = calloc(1, strlen(name) + 1);  
    new_command->description = calloc(1, strlen(description) + 1);
    strcpy(new_command->name, name);
    strcpy(new_command->description, description);
    if (pattern == NULL || strlen(pattern) == 0) {
        new_command->nmatch = 0;
    }
    if (pattern != NULL && strlen(pattern) >= 1) {
        regcomp(&new_command->preg, pattern, REG_EXTENDED | REG_ICASE);
    }
    new_command->nmatch = nmatch;
    return new_command;
}

struct command* destroy_command(struct command* command) {
    if (command == NULL) {
        return NULL;
    }
    
    if (command->description != NULL) {
        free(command->description);
    }
    if (&command->preg != NULL) {
        regfree(&command->preg); 
    }
    else {
        if (command->description != NULL) {
            command->description = NULL;
        }
    }
    if (command->name != NULL) {
        free(command->name);
    }
    free(command);
    command = NULL;
    return command;
}
