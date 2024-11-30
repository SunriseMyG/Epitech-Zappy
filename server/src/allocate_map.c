/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** allocate_map
*/

#include "../include/server.h"

void allocate_map(server_t *server)
{
    server->map = malloc(server->height * sizeof(tile_t *));
    for (int y = 0; y < server->height; y++) {
        server->map[y] = malloc(server->width * sizeof(tile_t));
        for (int x = 0; x < server->width; x++) {
            memset(&server->map[y][x].resources, 0, sizeof(resources_t));
        }
    }
}
