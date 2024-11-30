/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** mouvement
*/

#include "../include/server.h"

void move_forward_2(server_t *server, int x, int y)
{
    if (x < 0)
        x = server->width - 1;
    if (y < 0)
        y = server->height - 1;
    if (x >= server->width)
        x = 0;
    if (y >= server->height)
        y = 0;
    server->client_data[server->currentclient].position.x = x;
    server->client_data[server->currentclient].position.y = y;
    printf("x: %d y: %d\n", x, y);
    send(server->client_data[server->currentclient].socket, "ok\n", 3, 0);
}

void move_forward(server_t *server, char **args)
{
    int x = server->client_data[server->currentclient].position.x;
    int y = server->client_data[server->currentclient].position.y;
    int dir = server->client_data[server->currentclient].direction;

    (void)args;
    if (dir == N)
        y--;
    if (dir == E)
        x++;
    if (dir == S)
        y++;
    if (dir == W)
        x--;
    move_forward_2(server, x, y);
}

void move_right(server_t *server, char **args)
{
    int dir = server->client_data[server->currentclient].direction;

    (void)args;
    dir++;
    if (dir > 3)
        dir = 0;
    server->client_data[server->currentclient].direction = dir;
    direction_dump(server, server->currentclient);
    send(server->client_data[server->currentclient].socket, "ok\n", 3, 0);
}

void move_left(server_t *server, char **args)
{
    int dir = server->client_data[server->currentclient].direction;

    (void)args;
    dir--;
    if (dir < 0)
        dir = 3;
    server->client_data[server->currentclient].direction = dir;
    direction_dump(server, server->currentclient);
    send(server->client_data[server->currentclient].socket, "ok\n", 3, 0);
}
