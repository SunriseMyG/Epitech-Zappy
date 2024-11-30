/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-steven.deffontaine
** File description:
** inventory
*/

#include "../include/server.h"

void inventory(server_t *server, char **args)
{
    char inventory_str[256];

    (void)args;
    sprintf(inventory_str, "[food %d, linemate %d, deraumere %d, "
        "sibur %d, mendiane %d, phiras %d, thystame %d]\n",
        server->client_data[server->currentclient].inv->food,
        server->client_data[server->currentclient].inv->linemate,
        server->client_data[server->currentclient].inv->deraumere,
        server->client_data[server->currentclient].inv->sibur,
        server->client_data[server->currentclient].inv->mendiane,
        server->client_data[server->currentclient].inv->phiras,
        server->client_data[server->currentclient].inv->thystame);
    send(getclientsocket(server), inventory_str, strlen(inventory_str), 0);
}

void player_inventory(server_t *server, char **args)
{
    char inventory_str[256];
    int player_nb_int = atoi(args[0]);
    int id = getclientsocketbyid(server, player_nb_int);

    if (player_nb_int > server->client_nbr || player_nb_int < 0 || id == -1) {
        send(getclientsocket(server), "ko\n", 3, 0);
        return;
    }
    sprintf(inventory_str, "pin %d %d %d %d %d %d %d %d %d %d\n",
        server->client_data[id].id, server->client_data[id].position.x,
        server->client_data[id].position.y,
        server->client_data[id].inv->food,
        server->client_data[id].inv->linemate,
        server->client_data[id].inv->deraumere,
        server->client_data[id].inv->sibur,
        server->client_data[id].inv->mendiane,
        server->client_data[id].inv->phiras,
        server->client_data[id].inv->thystame);
    send(getclientsocket(server), inventory_str, strlen(inventory_str), 0);
}
