/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** team
*/

#include "../include/server.h"

void all_team_name(server_t *server, char **args)
{
    int arg_count = 0;

    while (args[arg_count] != NULL)
        arg_count++;
    if (arg_count != 0) {
        send(getclientsocket(server), "sbp\n", 4, 0);
        return;
    }
    for (int i = 0; i < server->count_team; i++) {
        send(getclientsocket(server), "tna ", 4, 0);
        send(getclientsocket(server), server->teams[i].name,
            strlen(server->teams[i].name), 0);
        send(getclientsocket(server), "\n", 1, 0);
    }
}

void jointeam(server_t *server, int i, int j)
{
    egg_t *egg = get_egg_by_team(server, server->teams[j].name);
    char response[256];

    server->client_data[i].team_name = server->teams[j].name;
    server->id_increment = server->id_increment + 1;
    server->client_data[i].id = server->id_increment;
    server->client_data[i].position.x = egg->position.x;
    server->client_data[i].position.y = egg->position.y;
    sprintf(response, "ebo %d\n", egg->id);
    send_msg_graphic(server, response);
    remove_egg(server, egg);
    server->teams[j].clients_nb++;
    dprintf(server->client_socket[i], "%d\n",
        server->teams[j].clients_max - server->teams[j].clients_nb);
    dprintf(server->client_socket[i], "%d %d\n", server->width,
        server->height);
    pnw(server, i);
}

void normalteam(server_t *server, int i, char *buffer)
{
    char name_upper[256];

    for (int j = 0; j < server->count_team; j++) {
        strcpy(name_upper, server->teams[j].name);
        for (int k = 0; name_upper[k]; k++)
            name_upper[k] = toupper(name_upper[k]);
        if (server->teams[j].clients_max - server->teams[j].clients_nb <= 0)
            continue;
        if (strcmp(name_upper, buffer) == 0) {
            init_client(server, getclientsocket(server));
            jointeam(server, i, j);
            client_dump(server, getclientsocket(server));
            return;
        }
    }
}

void enterteam(server_t *server, int i, char *buffer)
{
    if (strcmp(buffer, "GRAPHIC") != 0)
        normalteam(server, i, buffer);
    else {
        server->client_data[i].team_name = "GRAPHIC";
        server->client_data[i].socket = getclientsocket(server);
        server->client_data[i].id = -1;
        send_egg_pos(server, getclientsocket(server));
    }
}

void connect_nbr(server_t *server, char **args)
{
    char result[256];

    (void)args;
    snprintf(result, 256, "%d\n", server->teams->clients_max -
        server->teams->clients_nb);
    send(getclientsocket(server), result, strlen(result), 0);
}
