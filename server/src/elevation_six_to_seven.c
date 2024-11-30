/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** elevation_six_to_seven
*/

#include "../include/server.h"

int elevation_six_to_seven(server_t *server)
{
    int count = 0;

    for (int i = 0; i < server->client_nbr; i++)
        if (server->client_data[i].elevation == 6
            && server->client_data[i].position.x ==
            server->client_data[server->currentclient].position.x
            && server->client_data[i].position.y ==
            server->client_data[server->currentclient].position.y)
            count++;
    return count;
}

void check_player_elevation_seven(server_t *server, int i,
    int *elevation_success)
{
    int nb = elevation_six_to_seven(server);

    if (i != server->currentclient &&
        server->client_data[i].elevation == 6 &&
        server->client_data[i].position.x ==
        server->client_data[server->currentclient].position.x &&
        server->client_data[i].position.y ==
        server->client_data[server->currentclient].position.y &&
        server->client_data[i].inv->linemate >= 1 &&
        server->client_data[i].inv->phiras >= 1 &&
        server->client_data[i].inv->sibur >= 3 && nb >= 6
        && server->client_data[i].inv->deraumere >= 2) {
        server->client_data[i].inv->linemate--;
        server->client_data[i].inv->sibur -= 3;
        server->client_data[i].inv->phiras--;
        server->client_data[i].inv->deraumere -= 2;
        server->client_data[i].elevation = 7;
        *elevation_success = 1;
    }
}

void remove_resources_elevation_six(server_t *server)
{
    server->client_data[server->currentclient].inv->linemate--;
    server->client_data[server->currentclient].inv->sibur -= 3;
    server->client_data[server->currentclient].inv->phiras--;
    server->client_data[server->currentclient].inv->deraumere -= 2;
}

void manage_elevation_six_to_seven(server_t *server)
{
    int elevation_success = 0;
    int nb = elevation_six_to_seven(server);

    if (server->client_data[server->currentclient].elevation == 6 && nb >= 6
        && server->client_data[server->currentclient].inv->linemate >= 1 &&
        server->client_data[server->currentclient].inv->sibur >= 3 &&
        server->client_data[server->currentclient].inv->phiras >= 1 &&
        server->client_data[server->currentclient].inv->deraumere >= 2) {
        remove_resources_elevation_six(server);
        for (int i = 0; i < server->client_nbr; i++)
            check_player_elevation_seven(server, i, &elevation_success);
        if (elevation_success
            || server->client_data[server->currentclient].elevation == 6) {
            server->client_data[server->currentclient].elevation = 7;
            elevation_success = 1;
            result_incantation_server_ok(server);
        } else
            result_incantation_server_ko(server);
    } else
        result_incantation_server_ko(server);
}
