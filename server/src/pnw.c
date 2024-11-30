/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** pnw
*/

#include "../include/server.h"

void pnw(server_t *server, int current_client)
{
    int n = server->client_data[current_client].id;
    int X = server->client_data[current_client].position.x;
    int Y = server->client_data[current_client].position.y;
    int L = server->client_data[current_client].elevation;
    int O = server->client_data[current_client].direction + 1;
    char *N = server->client_data[current_client].team_name;
    char *format = malloc(256);

    sprintf(format, "pnw %d %d %d %d %d %s\n", n, X, Y, O, L, N);
    send_msg_graphic(server, format);
    free(format);
}
