/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** command_handler
*/

#include "../include/server.h"

char *beautify_command(char *command)
{
    char *new_command = malloc(sizeof(char) * (strlen(command) + 1));
    int i = 0;

    if (command[0] == '/')
        command++;
    for (int j = 0; command[j] != '\0'; j++) {
        if (command[j] == ' ')
            break;
        if (command[j] != '\t' && command[j] != '\n') {
            new_command[i] = toupper((unsigned char) command[j]);
            i++;
        }
    }
    new_command[i] = '\0';
    return (new_command);
}

void command_handler(server_t *server, char *command)
{
    char **args;

    if (command == NULL || command[0] == '\0')
        return;
    args = args_parser(command);
    command = beautify_command(command);
    for (int i = 0; i < server->nbr_commands; i++) {
        if (strcmp(server->commands[i].name, command) == 0 &&
            !server->commands[i].is_graphic &&
            server->client_data[server->currentclient].id != -1) {
            server->commands[i].function(server, args);
            return;
        }
        if (strcmp(server->commands[i].name, command) == 0 &&
            server->commands[i].is_graphic &&
            server->client_data[server->currentclient].id == -1) {
            server->commands[i].function(server, args);
            return;
        }
    }
}

void traitement(server_t *server, int i)
{
    if (server->valread == 0) {
        close(server->client_socket[i]);
        server->client_socket[i] = 0;
    } else {
        if (server->client_data[i].team_name != NULL)
            command_handler(server, server->buffer);
        else
            enterteam(server, i, beautify_command(server->buffer));
    }
}

void manage_message(server_t *server, int i)
{
    server->currentclient = i;
    server->buffer = malloc(sizeof(char) * 1024);
    server->buffer = memset(server->buffer, 0, 1024);
    fcntl(server->client_socket[i], F_SETFL,
        fcntl(server->client_socket[i], F_GETFL, 0) | O_NONBLOCK);
    server->valread = my_recv(server->client_socket[i], server->buffer, 1024);
    if (server->valread == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        free(server->buffer);
        return;
    }
    if (server->client_data[server->currentclient].id == -1 ||
        server->client_data[server->currentclient].team_name == NULL)
        traitement(server, i);
    else
        if (server->client_data[server->currentclient].locked == false)
            add_waiting_command(server, server->buffer,
                server->currentclient);
    free(server->buffer);
}

void receive_message(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(server->client_socket[i], &server->readfds)) {
            manage_message(server, i);
            disconnection(server, i);
        }
    }
}
