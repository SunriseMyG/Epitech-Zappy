/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** elevation_four_to_five
*/

#include "../include/server.h"

int elevation_four_to_five(server_t *server)
{
    int count = 0;

    for (int i = 0; i < server->client_nbr; i++)
        if (server->client_data[i].elevation == 4
            && server->client_data[i].position.x ==
            server->client_data[server->currentclient].position.x
            && server->client_data[i].position.y ==
            server->client_data[server->currentclient].position.y)
            count++;
    return count;
}

void check_player_elevation_five(server_t *server, int i,
    int *elevation_success)
{
    int nb = elevation_four_to_five(server);

    if (i != server->currentclient &&
        server->client_data[i].elevation == 4 &&
        server->client_data[i].position.x ==
        server->client_data[server->currentclient].position.x &&
        server->client_data[i].position.y ==
        server->client_data[server->currentclient].position.y &&
        server->client_data[i].inv->linemate >= 1 &&
        server->client_data[i].inv->sibur >= 2 &&
        server->client_data[i].inv->phiras >= 1 && nb >= 4
        && server->client_data[i].inv->deraumere >= 1) {
        server->client_data[i].inv->linemate--;
        server->client_data[i].inv->sibur -= 2;
        server->client_data[i].inv->phiras--;
        server->client_data[i].inv->deraumere--;
        server->client_data[i].elevation = 5;
        *elevation_success = 1;
    }
}

void remove_resources_elevation_four(server_t *server)
{
    server->client_data[server->currentclient].inv->linemate--;
    server->client_data[server->currentclient].inv->sibur -= 2;
    server->client_data[server->currentclient].inv->phiras--;
    server->client_data[server->currentclient].inv->deraumere--;
}

void manage_elevation_four_to_five(server_t *server)
{
    int elevation_success = 0;
    int nb = elevation_four_to_five(server);

    if (server->client_data[server->currentclient].elevation == 4 && nb >= 4
        && server->client_data[server->currentclient].inv->linemate >= 1 &&
        server->client_data[server->currentclient].inv->sibur >= 2 &&
        server->client_data[server->currentclient].inv->phiras >= 1 &&
        server->client_data[server->currentclient].inv->deraumere >= 1) {
        remove_resources_elevation_four(server);
        for (int i = 0; i < server->client_nbr; i++)
            check_player_elevation_five(server, i, &elevation_success);
        if (elevation_success
            || server->client_data[server->currentclient].elevation == 4) {
            server->client_data[server->currentclient].elevation = 5;
            elevation_success = 1;
            result_incantation_server_ok(server);
        } else
            result_incantation_server_ko(server);
    } else
        result_incantation_server_ko(server);
}
