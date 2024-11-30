/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** elevation
*/

#include "../include/server.h"

void start_msg_fork(server_t *server)
{
    char response[1024];

    sprintf(response, "pfk %d\n",
        server->client_data[server->currentclient].id);
    send_msg_graphic(server, response);
}

void fork_cmd(server_t *server, char **args)
{
    (void)args;
    for (int i = 0; i < server->count_team; i++) {
        if (strcmp(server->teams[i].name,
            server->client_data[server->currentclient].team_name) == 0) {
            server->teams[i].clients_max++;
            generate_egg(server, server->teams[i].name,
                server->client_data[server->currentclient].position.x,
                server->client_data[server->currentclient].position.y);
            dprintf(server->client_socket[server->currentclient], "ok\n");
        }
    }
}
