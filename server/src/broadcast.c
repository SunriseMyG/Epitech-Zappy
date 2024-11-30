/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** boardcast
*/

#include "../include/server.h"
#include <math.h>

int get_player_id_from_position(server_t *server, int x, int y)
{
    for (int i = 0; i < server->client_nbr; i++) {
        if (server->client_data[i].position.x == x
            && server->client_data[i].position.y == y)
            return server->client_data[i].id;
    }
    return -1;
}

void send_message_to_player(server_t *server, int player_index,
    int direction, char *text)
{
    char message[1024];
    char response[1024];
    char temp[1024];

    sprintf(temp, "message %d, %s", direction, text);
    strncpy(message, temp, sizeof(message) - 1);
    message[sizeof(message) - 1] = '\0';
    send(server->client_data[player_index].socket, message,
        strlen(message), 0);
    sprintf(response, "pbc %d %s\n",
        server->client_data[server->currentclient].id, text);
    send_msg_graphic(server, response);
}

int get_direction(int dx, int dy)
{
    if (dx == 0 && dy < 0)
        return 1;
    if (dx > 0 && dy < 0)
        return 2;
    if (dx > 0 && dy == 0)
        return 3;
    if (dx > 0 && dy > 0)
        return 4;
    if (dx == 0 && dy > 0)
        return 5;
    if (dx < 0 && dy > 0)
        return 6;
    if (dx < 0 && dy == 0)
        return 7;
    if (dx < 0 && dy < 0)
        return 8;
    return -1;
}

void broadcast_to_all_players(server_t *server, char *message)
{
    int x = server->client_data[server->currentclient].position.x;
    int y = server->client_data[server->currentclient].position.y;
    int dx;
    int dy;
    int direction;

    for (int i = 0; i < server->client_nbr; i++) {
        if (i == server->currentclient)
            continue;
        dx = server->client_data[i].position.x - x;
        dy = server->client_data[i].position.y - y;
        direction = get_direction(dx, dy);
        send_message_to_player(server, i, direction, message);
    }
    send(server->client_data[server->currentclient].socket, "ok\n", 3, 0);
}

void broadcast(server_t *server, char **args)
{
    int total_length = 0;
    char *message;

    for (int i = 0; args[i] != NULL; i++)
        total_length += strlen(args[i]) + 1;
    message = malloc(total_length * sizeof(char));
    if (message == NULL)
        return;
    message[0] = '\0';
    for (int i = 0; args[i] != NULL; i++) {
        strcat(message, args[i]);
        if (args[i + 1] != NULL) {
            strcat(message, " ");
        }
    }
    broadcast_to_all_players(server, message);
    free(message);
}
