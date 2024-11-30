/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** elevation
*/

#include "../include/server.h"

void result_incantation_server_ok(server_t *server)
{
    char message[256];

    sprintf(message, "pie %d %d %s\n",
        server->client_data[server->currentclient].position.x,
        server->client_data[server->currentclient].position.y, "ok");
    send_msg_graphic(server, message);
    for (int i = 0; i < server->client_nbr; i++) {
        if (server->client_data[i].position.x ==
            server->client_data[server->currentclient].position.x &&
            server->client_data[i].position.y ==
            server->client_data[server->currentclient].position.y &&
            server->client_data[i].id != -1) {
            server->client_data[i].locked = false;
        }
    }
    send(getclientsocket(server), "ok\n", 3, 0);
}

void result_incantation_server_ko(server_t *server)
{
    char message[256];

    sprintf(message, "pie %d %d %s\n",
        server->client_data[server->currentclient].position.x,
        server->client_data[server->currentclient].position.y, "ko");
    send_msg_graphic(server, message);
        for (int i = 0; i < server->client_nbr; i++) {
        if (server->client_data[i].position.x ==
            server->client_data[server->currentclient].position.x &&
            server->client_data[i].position.y ==
            server->client_data[server->currentclient].position.y &&
            server->client_data[i].id != -1) {
            server->client_data[i].locked = false;
        }
    }
    send(getclientsocket(server), "ko\n", 3, 0);
}

void incantation(server_t *server, char **args)
{
    (void)args;
    if (server->client_data[server->currentclient].elevation == 1) {
        manage_elevation_one_to_two(server);
        return;
    }
    if (server->client_data[server->currentclient].elevation == 2) {
        manage_elevation_two_to_three(server);
        return;
    }
    if (server->client_data[server->currentclient].elevation == 3) {
        manage_elevation_three_to_four(server);
        return;
    }
    if (server->client_data[server->currentclient].elevation == 4) {
        manage_elevation_four_to_five(server);
        return;
    }
    incantation_next(server);
}

void incantation_next(server_t *server)
{
    if (server->client_data[server->currentclient].elevation == 5) {
        manage_elevation_five_to_six(server);
        return;
    }
    if (server->client_data[server->currentclient].elevation == 6) {
        manage_elevation_six_to_seven(server);
        return;
    }
    if (server->client_data[server->currentclient].elevation == 7) {
        manage_elevation_seven_to_eight(server);
        return;
    }
}

void start_msg_incantation(server_t *server)
{
    char message[256];

    sprintf(message, "pic %d %d %d %d\n",
        server->client_data[server->currentclient].position.x,
        server->client_data[server->currentclient].position.y,
        server->client_data[server->currentclient].elevation,
        server->client_data[server->currentclient].id);
    for (int i = 0; i < server->client_nbr; i++) {
        if (server->client_data[i].position.x ==
            server->client_data[server->currentclient].position.x &&
            server->client_data[i].position.y ==
            server->client_data[server->currentclient].position.y &&
            server->client_data[i].id != -1) {
            server->client_data[i].locked = true;
        }
    }
    send_msg_graphic(server, message);
}
