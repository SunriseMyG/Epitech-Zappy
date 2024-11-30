/*
** EPITECH PROJECT, 2024
** zappy [WSLÂ: Ubuntu]
** File description:
** world time
*/

#include "../include/server.h"

void world_clock(server_t *server)
{
    server->world_clock++;
    if (server->world_clock % 20 == 0)
        generate_resources(server, false);
    if (server->world_clock % 126 == 0)
        manage_life_for_player(server);
}

void death_msg(server_t *server, int i)
{
    char message[256];

    sprintf(message, "pdi %d\n", server->client_data[i].id);
    server->client_data[i].id = -1;
    send_msg_graphic(server, message);
}

void manage_life_for_player(server_t *server)
{
    for (int i = 0; i < server->client_nbr; i++) {
        if (server->client_data[i].team_name == NULL ||
            server->client_data[i].id == -1)
            continue;
        if (server->client_data[i].life <= 10
            && server->client_data[i].inv->food < 1)
            server->client_data[i].life -= 1;
        if (server->client_data[i].life < 10
            && server->client_data[i].inv->food > 1) {
            server->client_data[i].inv->food -= 1;
            server->client_data[i].life += 1;
        }
        if (server->client_data[i].life == 0) {
            death_msg(server, i);
            server->client_data[i].locked = false;
            server->client_data[i].id = -1;
        }
    }
}
