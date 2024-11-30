/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** elevation_one_to_two
*/

#include "../include/server.h"

void check_player_elevation_two(server_t *server, int i,
    int *elevation_success)
{
    if (i != server->currentclient &&
        server->client_data[i].elevation == 1 &&
        server->client_data[i].position.x ==
        server->client_data[server->currentclient].position.x &&
        server->client_data[i].position.y ==
        server->client_data[server->currentclient].position.y &&
        server->client_data[i].inv->linemate >= 1) {
        server->client_data[i].inv->linemate--;
        server->client_data[i].elevation = 2;
        *elevation_success = 1;
    }
}

void manage_elevation_one_to_two(server_t *server)
{
    int elevation_success = 0;

    if (server->client_data[server->currentclient].elevation == 1 &&
        server->client_data[server->currentclient].inv->linemate >= 1) {
        server->client_data[server->currentclient].inv->linemate--;
        for (int i = 0; i < server->client_nbr; i++)
            check_player_elevation_two(server, i, &elevation_success);
        if (elevation_success
            || server->client_data[server->currentclient].elevation == 1) {
            server->client_data[server->currentclient].elevation = 2;
            elevation_success = 1;
            result_incantation_server_ok(server);
        } else {
            result_incantation_server_ko(server);
        }
    } else
        result_incantation_server_ko(server);
}
