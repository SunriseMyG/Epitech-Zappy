/*
** EPITECH PROJECT, 2024
** zappy [WSLÂ: Ubuntu]
** File description:
** vision
*/

#include "../include/server.h"

void get_position(server_t *server, int j, int i)
{
    switch (server->client_data[server->currentclient].direction) {
        case N:
            server->x += j;
            server->y -= i;
            break;
        case E:
            server->x += i;
            server->y += j;
            break;
        case S:
            server->x += j;
            server->y += i;
            break;
        case W:
            server->x -= i;
            server->y += j;
            break;
    }
}

void init_vision(server_t *server)
{
    server->player_x = server->client_data[server->currentclient].position.x;
    server->player_y = server->client_data[server->currentclient].position.y;
}

void end_vision(server_t *server, char *vision)
{
    int final_vision_size = strlen(vision) + 4;
    char *final_vision = malloc(final_vision_size);

    vision[strlen(vision)] = '\0';
    if (final_vision == NULL) {
        free(vision);
        return;
    }
    snprintf(final_vision, final_vision_size, "[%s]\n", vision);
    send(server->client_socket[server->currentclient], final_vision,
        strlen(final_vision), 0);
    free(final_vision);
}

void manage_vision(server_t *server, char *vision, int i, int j)
{
    get_position(server, j, i);
    server->player_on_tile = (server->x == server->player_x
        && server->y == server->player_y);
    server->ressource = get_ressource_from_tile(server, server->x, server->y);
    if (i > 0 || j > -i)
        strncat(vision, ",", 4096 - strlen(vision) - 1);
    if (server->player_on_tile) {
        strncat(vision, "player", 4096 - strlen(vision) - 1);
        if (strlen(server->ressource) > 0)
            strncat(vision, " ", 4096 - strlen(vision) - 1);
    }
    strncat(vision, server->ressource, 4096 - strlen(vision) - 1);
    free(server->ressource);
}

static void manage_s_and_w_vision(server_t *server, int i, char *vision)
{
    for (int j = i; j >= -i; j--) {
        server->x = server->player_x;
        server->y = server->player_y;
        manage_vision(server, vision, i, j);
    }
}

static void manage_n_and_e_vision(server_t *server, int i, char *vision)
{
    for (int j = -i; j <= i; j++) {
        server->x = server->player_x;
        server->y = server->player_y;
        manage_vision(server, vision, i, j);
    }
}

void vision(server_t *server, char **args)
{
    char *vision = malloc(4096 * sizeof(char));
    int elevation = server->client_data[server->currentclient].elevation;
    int direction = server->client_data[server->currentclient].direction;

    (void)args;
    if (vision == NULL)
        return;
    init_vision(server);
    vision[0] = '\0';
    for (int i = 0; i <= elevation; i++) {
        if (direction == S || direction == W)
            manage_s_and_w_vision(server, i, vision);
        else
            manage_n_and_e_vision(server, i, vision);
    }
    end_vision(server, vision);
    free(vision);
}
