/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-steven.deffontaine [WSL : Ubuntu]
** File description:
** get_server_input
*/

#include "../include/server.h"

client_data_t *getplayerbyid(server_t *server, int id)
{
    for (int i = 0; i < server->client_nbr; i++) {
        if (server->client_data[i].id == id)
            return &server->client_data[i];
    }
    return NULL;
}

int getclientsocketbyid(server_t *server, int id)
{
    for (int i = 0; i < server->client_nbr; i++) {
        if (server->client_data[i].id == id && server->client_socket[i] != -1)
            return i;
    }
    return -1;
}
