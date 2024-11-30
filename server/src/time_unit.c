/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** time_unit
*/

#include "../include/server.h"

void get_time_unit(server_t *server, char **args)
{
    char time_unit_str[32];

    (void)args;
    sprintf(time_unit_str, "sgt %d\n", server->freq);
    send(getclientsocket(server), time_unit_str, strlen(time_unit_str), 0);
}

void update_time_unit(server_t *server, char **args)
{
    char time_unit_str[32];
    int time_unit = atoi(args[0]);

    if (time_unit < 0) {
        send(getclientsocket(server), "ko\n", 3, 0);
        return;
    }
    server->freq = time_unit;
    sprintf(time_unit_str, "sst %d\n", server->freq);
    send(getclientsocket(server), time_unit_str, strlen(time_unit_str), 0);
}
