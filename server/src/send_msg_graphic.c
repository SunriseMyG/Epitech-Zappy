/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** send_msg_graphic
*/

#include "../include/server.h"

void send_msg_graphic(server_t *server, char *data)
{
    for (int i = 0; i < server->client_nbr; i++)
        if (server->client_data[i].id == -1 &&
            strcmp(server->client_data[i].team_name, "GRAPHIC") == 0)
            send(server->client_socket[i], data, strlen(data), 0);
}

void send_egg_pos(server_t *server, int socket)
{
    char response[2048] = "";
    char egg_data[256];

    for (int i = 0; i < server->count_eggs; i++) {
        egg_data[0] = '\0';
        snprintf(egg_data, sizeof(egg_data), "enw %d 0 %d %d\n",
            server->eggs[i]->id,
            server->eggs[i]->position.x, server->eggs[i]->position.y);
        if (strlen(response) + strlen(egg_data) < sizeof(response)) {
            strcat(response, egg_data);
        } else {
            break;
        }
    }
    send(socket, response, strlen(response), 0);
}
