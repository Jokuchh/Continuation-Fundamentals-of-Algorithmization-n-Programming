#include "parser.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

struct parser* create_parser() {
    struct parser* new_parser_parser = calloc(1, sizeof(struct parser));   
    new_parser_parser->history = NULL;
    struct command *new_command = create_command("SEVER", "S", "(SEVER)", 1);
    new_parser_parser->commands = create_container(new_parser_parser->commands, COMMAND, new_command);
    if (get_from_container_by_name(new_parser_parser->commands, "KONIEC") == NULL) {
        new_command = create_command("KONIEC", "End", "(KONIEC)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "RESTART") == NULL) {
        new_command = create_command("RESTART", "F", "(RESTART)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "PRIKAZY") == NULL) {
        new_command = create_command("PRIKAZY", "all commands", "(PRIKAZY)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "VERZIA") == NULL) {
        new_command = create_command("VERZIA", "some info", "(VERZIA)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "JUH") == NULL) {
        new_command = create_command("JUH", "J", "(JUH)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "ROZHLIADNI SA") == NULL) {
        new_command = create_command("ROZHLIADNI SA", "now look at this", "(ROZHLIADNI SA)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "POLOZ") == NULL) {
        new_command = create_command("POLOZ", "Drop it", "(POLOZ)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "VEZMI") == NULL) {
        new_command = create_command("VEZMI", "Take it", "(VEZMI)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "INVENTAR") == NULL) {
        new_command = create_command("INVENTAR", "inventory", "(INVENTAR)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "VYCHOD") == NULL) {
        new_command = create_command("VYCHOD", "V", "(VYCHOD)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "POUZI") == NULL) {
        new_command = create_command("POUZI", "Use", "(POUZI)( *)([A-Z])?", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "O HRE") == NULL) {
        new_command = create_command("O HRE", "Lore", "(O HRE)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "PRESKUMAJ") == NULL) {
        new_command = create_command("PRESKUMAJ", "Mmm...", "(PRESKUMAJ)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "ULOZ") == NULL) {
        new_command = create_command("ULOZ", "Nahraj", "(ULOZ)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "NAHRAJ") == NULL) {
        new_command = create_command("NAHRAJ", "Ulozi", "(NAHRAJ)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "ZAPAD") == NULL) {
        new_command = create_command("ZAPAD", "Z", "(ZAPAD)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    if (get_from_container_by_name(new_parser_parser->commands, "SEVER") == NULL) {
        new_command = create_command("SEVER", "Z", "(SEVER)", 1);
        create_container(new_parser_parser->commands, COMMAND, new_command);
    }
    return new_parser_parser;
}

struct parser* destroy_parser(struct parser* parser) {
    if (parser == NULL) {
        return NULL;
    }
    parser->commands = destroy_containers(parser->commands);
    parser->history = destroy_containers(parser->history);
    free(parser);
    parser = NULL;
    return NULL;
}

struct command* parse_input(struct parser* parser, char* input) {
    if (parser == NULL || input == NULL) {
        return NULL;
    }
    if (strlen(input) == 0) {
        return NULL;
    }
    struct container *pointer = parser->commands;
    while (pointer != NULL) {
        if (regexec(&pointer->command->preg, input, 0, NULL, 0) != REG_NOMATCH) {
            return pointer->command;
        }
        pointer = pointer->next;
    }
    return NULL;
}
