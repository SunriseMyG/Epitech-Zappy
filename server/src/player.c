/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** player
*/

#include "../include/server.h"

char get_player_orientation(server_t *server, int player_id)
{
    char orientation;

    if (server->client_data[player_id].direction == 0)
        orientation = 'N';
    if (server->client_data[player_id].direction == 1)
        orientation = 'E';
    if (server->client_data[player_id].direction == 2)
        orientation = 'S';
    if (server->client_data[player_id].direction == 3)
        orientation = 'W';
    return orientation;
}

void player_position(server_t *server, char **args)
{
    char player_position[1024];
    int player_nb_int = atoi(args[0]);
    int playerid = getclientsocketbyid(server, player_nb_int);

    if (player_nb_int > server->client_nbr || player_nb_int <= 0
        || playerid == -1) {
        send(getclientsocket(server), "ko\n", 3, 0);
        return;
    }
    sprintf(player_position, "ppo %d %d %d %d\n",
            server->client_data[playerid].id,
            server->client_data[playerid].position.x,
            server->client_data[playerid].position.y,
            server->client_data[playerid].direction + 1);
    send(getclientsocket(server), player_position, strlen(player_position), 0);
}

void player_level(server_t *server, char **args)
{
    char player_level[1024];
    int player_nb_int = atoi(args[0]);
    int playerid = getclientsocketbyid(server, player_nb_int);

    if (player_nb_int > server->client_nbr || player_nb_int <= 0 ||
        playerid == -1) {
        send(getclientsocket(server), "ko\n", 3, 0);
        return;
    }
    sprintf(player_level, "plv %d %d\n", player_nb_int,
            server->client_data[playerid].elevation);
    send(getclientsocket(server), player_level, strlen(player_level), 0);
}
