/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** elevation_seven_to_eight
*/

#include "../include/server.h"

int elevation_seven_to_eight(server_t *server)
{
    int count = 0;

    for (int i = 0; i < server->client_nbr; i++)
        if (server->client_data[i].elevation == 7
            && server->client_data[i].position.x ==
            server->client_data[server->currentclient].position.x
            && server->client_data[i].position.y ==
            server->client_data[server->currentclient].position.y)
            count++;
    return count;
}

void winned_elevation_height(server_t *server)
{
    char message[256];
    char *teamname = server->client_data[server->currentclient].team_name;

    sprintf(message, "seg %s\n", teamname);
    send_msg_graphic(server, message);
    server->winned = true;
    sleep(10);
    exit(0);
}

static bool check_player_position_elevation(server_t *server, int i)
{
    if (server->client_data[i].position.x ==
        server->client_data[server->currentclient].position.x &&
        server->client_data[i].position.y ==
        server->client_data[server->currentclient].position.y)
        return true;
    return false;
}

void check_player_elevation_eight(server_t *server, int i,
    int *elevation_success)
{
    int nb = elevation_seven_to_eight(server);

    if (i != server->currentclient && server->client_data[i].elevation == 7 &&
        check_player_position_elevation(server, i) &&
        server->client_data[i].inv->linemate >= 2 &&
        server->client_data[i].inv->phiras >= 2 &&
        server->client_data[i].inv->thystame >= 1 &&
        server->client_data[i].inv->mendiane >= 2 &&
        server->client_data[i].inv->sibur >= 2 && nb >= 6
        && server->client_data[i].inv->deraumere >= 2) {
        server->client_data[i].inv->linemate -= 2;
        server->client_data[i].inv->sibur -= 2;
        server->client_data[i].inv->phiras -= 2;
        server->client_data[i].inv->deraumere -= 2;
        server->client_data[i].inv->mendiane -= 2;
        server->client_data[i].inv->thystame--;
        server->client_data[i].elevation = 8;
        *elevation_success = 1;
    }
}

void remove_resources_elevation_seven(server_t *server)
{
    server->client_data[server->currentclient].inv->linemate -= 2;
    server->client_data[server->currentclient].inv->sibur -= 2;
    server->client_data[server->currentclient].inv->phiras -= 2;
    server->client_data[server->currentclient].inv->deraumere -= 2;
    server->client_data[server->currentclient].inv->mendiane -= 2;
    server->client_data[server->currentclient].inv->thystame--;
}

static void check_elevation_success(server_t *server, int elevation_success)
{
    if (elevation_success
        || server->client_data[server->currentclient].elevation == 7) {
        server->client_data[server->currentclient].elevation = 8;
        elevation_success = 1;
        result_incantation_server_ok(server);
    } else
        result_incantation_server_ko(server);
}

void manage_elevation_seven_to_eight(server_t *server)
{
    int elevation_success = 0;
    int nb = elevation_seven_to_eight(server);

    if (server->client_data[server->currentclient].elevation == 7 && nb >= 6
        && server->client_data[server->currentclient].inv->linemate >= 2 &&
        server->client_data[server->currentclient].inv->sibur >= 2 &&
        server->client_data[server->currentclient].inv->phiras >= 2 &&
        server->client_data[server->currentclient].inv->deraumere >= 2 &&
        server->client_data[server->currentclient].inv->mendiane >= 2 &&
        server->client_data[server->currentclient].inv->thystame >= 1) {
        remove_resources_elevation_seven(server);
        for (int i = 0; i < server->client_nbr; i++)
            check_player_elevation_eight(server, i, &elevation_success);
        check_elevation_success(server, elevation_success);
    } else
        result_incantation_server_ko(server);
}
