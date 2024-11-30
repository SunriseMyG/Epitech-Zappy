/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** bct
*/

#include "../include/server.h"

bool check_args_bct(server_t *server, char **args)
{
    int arg_count = 0;

    while (args[arg_count] != NULL)
        arg_count++;
    if (arg_count != 2) {
        send(getclientsocket(server), "sbp\n", 4, 0);
        return false;
    }
    if (args[0][0] > '9' || args[0][0] < '0'
        || args[1][0] > '9' || args[1][0] < '0') {
        send(getclientsocket(server), "sbp\n", 4, 0);
        return false;
    }
    return true;
}

void bct(server_t *server, char **args)
{
    int x;
    int y;

    if (!check_args_bct(server, args))
        return;
    x = atoi(args[0]);
    y = atoi(args[1]);
    if (x < 0 || x >= server->width || y < 0 || y >= server->height) {
        send(getclientsocket(server), "ko\n", 3, 0);
        return;
    }
    dprintf(getclientsocket(server), "bct %d %d %d %d %d %d %d %d %d\n",
            x, y, server->map[y][x].resources.food,
            server->map[y][x].resources.linemate,
            server->map[y][x].resources.deraumere,
            server->map[y][x].resources.sibur,
            server->map[y][x].resources.mendiane,
            server->map[y][x].resources.phiras,
            server->map[y][x].resources.thystame);
}

void mct(server_t *server, char **args)
{
    int arg_count = 0;

    while (args[arg_count] != NULL)
        arg_count++;
    if (arg_count != 0) {
        send(getclientsocket(server), "sbp\n", 4, 0);
        return;
    }
    for (int y = 0; y < server->height; y++)
        for (int x = 0; x < server->width; x++)
            dprintf(getclientsocket(server),
                "bct %d %d %d %d %d %d %d %d %d\n",
                x, y, server->map[y][x].resources.food,
                server->map[y][x].resources.linemate,
                server->map[y][x].resources.deraumere,
                server->map[y][x].resources.sibur,
                server->map[y][x].resources.mendiane,
                server->map[y][x].resources.phiras,
                server->map[y][x].resources.thystame);
}
