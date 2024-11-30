/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-steven.deffontaine [WSL : Ubuntu]
** File description:
** map
*/

#include "../include/server.h"

void display_map(server_t *server)
{
    for (int i = 0; i < server->height; i++) {
        for (int j = 0; j < server->width; j++) {
            printf("%c", server->map[i][j].c);
        }
        printf("\n");
    }
}

void malloc_map(server_t *server)
{
    server->map = malloc(sizeof(char *) * server->height);
    for (int i = 0; i < server->height; i++)
        server->map[i] = malloc(sizeof(char) * server->width);
    for (int i = 0; i < server->height; i++) {
        for (int j = 0; j < server->width; j++) {
            server->map[i][j].c = '.';
        }
    }
}

void free_map(server_t *server)
{
    for (int i = 0; i < server->height; i++)
        free(server->map[i]);
    free(server->map);
}

void map_size(server_t *server, char **args)
{
    char map_size_str[256];
    int arg_count = 0;

    while (args[arg_count] != NULL)
        arg_count++;
    if (arg_count != 0) {
        send(getclientsocket(server), "sbp\n", 4, 0);
        return;
    }
    sprintf(map_size_str, "msz %d %d\n", server->width, server->height);
    send(getclientsocket(server), map_size_str, strlen(map_size_str), 0);
}
