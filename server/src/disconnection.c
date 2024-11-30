/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** disconnection
*/

#include "../include/server.h"

void disconnection(server_t *server, int i)
{
    if (server->valread == 0) {
        printf("Client %d disconnected\n", server->client_socket[i]);
        close(server->client_socket[i]);
        server->client_nbr--;
    }
}
