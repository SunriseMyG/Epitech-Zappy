/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** args_parser
*/

#include "../include/server.h"

char **args_parser(char *command)
{
    int max_tokens = 100;
    char **args = malloc(sizeof(char *) * max_tokens);
    char *token = strtok(command, " ");
    int i = 0;

    while (token != NULL) {
        if (i >= max_tokens) {
            max_tokens *= 2;
            args = realloc(args, sizeof(char *) * max_tokens);
        }
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
    for (int j = 0; j < i - 1; j++)
        args[j] = args[j + 1];
    args[i - 1] = NULL;
    return args;
}
