/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-steven.deffontaine
** File description:
** eject
*/

#include "../include/server.h"

void send_eject(server_t *server, char *message, int i)
{
    char response[256];

    send(server->client_socket[i], message, strlen(message), 0);
    sprintf(response, "pex %d\n", server->client_data[i].id);
    send_msg_graphic(server, response);
}

void case_eject_players(server_t *server, char orientation, int i,
    char *message)
{
    switch (orientation) {
    case 'N':
        server->client_data[i].position.y -= 1;
        sprintf(message, "eject: %c\n", 'N');
        break;
    case 'E':
        server->client_data[i].position.x += 1;
        sprintf(message, "eject: %c\n", 'E');
        break;
    case 'S':
        server->client_data[i].position.y += 1;
        sprintf(message, "eject: %c\n", 'S');
        break;
    case 'W':
        server->client_data[i].position.x -= 1;
        sprintf(message, "eject: %c\n", 'W');
        break;
    }
    send_eject(server, message, i);
}

void break_egg_msg(server_t *server, int id)
{
    char response[256];

    sprintf(response, "edi %d\n", id);
    send_msg_graphic(server, response);
}

void break_egg(server_t *server, int x, int y)
{
    for (int i = 0; i < server->count_eggs; i++) {
        if (server->eggs[i]->position.x == x &&
            server->eggs[i]->position.y == y) {
            break_egg_msg(server, server->eggs[i]->id);
            remove_egg(server, server->eggs[i]);
        }
    }
}

void eject_players(server_t *server, char **args)
{
    char orientation = get_player_orientation(server, server->currentclient);
    char message[256];

    (void)args;
    for (int i = 0; i < server->client_nbr; i++) {
        if (i == server->currentclient)
            continue;
        if (server->client_data[i].position.x ==
            server->client_data[server->currentclient].position.x &&
            server->client_data[i].position.y ==
            server->client_data[server->currentclient].position.y) {
            case_eject_players(server, orientation, i, message);
        }
    }
    break_egg(server, server->client_data[server->currentclient].position.x,
        server->client_data[server->currentclient].position.y);
}
