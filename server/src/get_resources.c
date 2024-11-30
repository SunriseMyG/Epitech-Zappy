/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** get_resources
*/

#include "../include/server.h"

void get_player(server_t *server, char *ressource, int x, int y)
{
    for (int i = 0; i < server->client_nbr; i++)
        if (server->client_data[i].position.x == x
            && server->client_data[i].position.y == y
            && i != server->currentclient)
            strcat(ressource, "player ");
    for (int i = 0; i < server->count_eggs; i++)
        if (server->eggs[i]->position.x == x
            && server->eggs[i]->position.y == y)
            strcat(ressource, "egg ");
}

char *get_ressource(server_t *server, char *ressource, int x, int y)
{
    if (server->map[y][x].resources.food > 0)
        strcat(ressource, "food ");
    if (server->map[y][x].resources.linemate > 0)
        strcat(ressource, "linemate ");
    if (server->map[y][x].resources.deraumere > 0)
        strcat(ressource, "deraumere ");
    if (server->map[y][x].resources.sibur > 0)
        strcat(ressource, "sibur ");
    if (server->map[y][x].resources.mendiane > 0)
        strcat(ressource, "mendiane ");
    if (server->map[y][x].resources.phiras > 0)
        strcat(ressource, "phiras ");
    if (server->map[y][x].resources.thystame > 0)
        strcat(ressource, "thystame ");
    get_player(server, ressource, x, y);
    return ressource;
}

char *get_ressource_from_tile(server_t *server, int x, int y)
{
    char *ressource = malloc(sizeof(char) * 256);

    if (x < 0 || x >= server->width || y < 0 || y >= server->height)
        return strdup("");
    if (ressource == NULL)
        return NULL;
    ressource[0] = '\0';
    ressource = get_ressource(server, ressource, x, y);
    if (strlen(ressource) > 0 && ressource[strlen(ressource) - 1] == ' ')
        ressource[strlen(ressource) - 1] = '\0';
    return ressource;
}
