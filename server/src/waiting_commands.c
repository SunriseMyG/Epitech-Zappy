/*
** EPITECH PROJECT, 2024
** zappy [WSLÂ: Ubuntu]
** File description:
** waiting command
*/

#include "../include/server.h"

void init_table_commands_time(server_t *server)
{
    static const command_time_t default_command_times[] = {
        {"FORWARD", 7}, {"RIGHT", 7}, {"LEFT", 7}, {"LOOK", 7},
        {"INVENTORY", 1}, {"BRODCAST", 7}, {"CONNECT_NUMBER", 0},
        {"FORK", 42}, {"EJECT", 7}, {"TAKE", 7}, {"SET", 7},
        {"INCANTATION", 300}
    };

    server->nbr_waiting_commands =
        sizeof(default_command_times) / sizeof(command_time_t);
    server->command_time = malloc(sizeof(default_command_times));
    for (int i = 0; i < server->nbr_waiting_commands; i++) {
        server->command_time[i] = default_command_times[i];
    }
}

int get_command_time(server_t *server, char *command)
{
    for (int i = 0; i < server->nbr_waiting_commands; i++) {
        if (strcmp(server->command_time[i].command, command) == 0) {
            return server->command_time[i].time;
        }
    }
    return 0;
}

void add_waiting_command(server_t *server, char *command, int currentclient)
{
    waiting_command_t *new_command = malloc(sizeof(waiting_command_t));
    waiting_command_t *tmp = server->waiting_commands;

    server->client_data[server->currentclient].locked = true;
    new_command->command = strdup(command);
    new_command->time_remaining = get_command_time(server,
        beautify_command(command));
    new_command->currentclient = currentclient;
    new_command->next = NULL;
    if (strcmp(beautify_command(command), "INCANTATION") == 0)
        start_msg_incantation(server);
    if (strcmp(beautify_command(command), "FORK") == 0)
        start_msg_fork(server);
    if (tmp == NULL) {
        server->waiting_commands = new_command;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_command;
}

void checker_prev_null(waiting_command_t *prev, waiting_command_t *tmp,
    server_t *server)
{
    if (prev == NULL)
        server->waiting_commands = tmp->next;
    else
        prev->next = tmp->next;
}

void check_waiting_commands(server_t *server)
{
    waiting_command_t *tmp = server->waiting_commands;
    waiting_command_t *prev = NULL;

    while (tmp != NULL) {
        tmp->time_remaining--;
        if (tmp->time_remaining <= 0) {
            server->currentclient = tmp->currentclient;
            server->client_data[server->currentclient].locked = false;
            command_handler(server, tmp->command);
            checker_prev_null(prev, tmp, server);
            free(tmp->command);
            free(tmp);
            tmp = prev == NULL ? server->waiting_commands : prev->next;
        } else {
            prev = tmp;
            tmp = tmp->next;
        }
    }
}
