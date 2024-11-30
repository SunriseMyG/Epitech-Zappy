/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** egg
*/

#include "../include/server.h"

void dump_egg(egg_t *egg)
{
    printf("egg: %s | id : %d\n", egg->team_name, egg->id);
    printf("position: %d %d\n", egg->position.x, egg->position.y);
}

void add_egg(server_t *server, egg_t *egg)
{
    egg_t **new_eggs = malloc(sizeof(egg_t *) * (server->count_eggs + 1));

    for (int i = 0; i < server->count_eggs; i++)
        new_eggs[i] = server->eggs[i];
    new_eggs[server->count_eggs] = egg;
    server->count_eggs++;
    free(server->eggs);
    server->eggs = new_eggs;
    dump_egg(egg);
}

void remove_egg(server_t *server, egg_t *egg)
{
    egg_t **new_eggs = malloc(sizeof(egg_t *) * (server->count_eggs - 1));
    int j = 0;

    for (int i = 0; i < server->count_eggs; i++) {
        if (server->eggs[i] != egg) {
            new_eggs[j] = server->eggs[i];
            j++;
        }
    }
    server->count_eggs--;
    free(server->eggs);
    server->eggs = new_eggs;
}

egg_t *get_egg_by_team(server_t *server, char *team_name)
{
    for (int i = 0; i < server->count_eggs; i++)
        if (strcmp(server->eggs[i]->team_name, team_name) == 0)
            return server->eggs[i];
    return NULL;
}

void generate_egg(server_t *server, char *team_name, int x, int y)
{
    egg_t *egg = malloc(sizeof(egg_t));
    char response[256];

    if (x == -1)
        x = rand() % server->width;
    if (y == -1)
        y = rand() % server->height;
    egg->position.x = x;
    egg->position.y = y;
    egg->team_name = team_name;
    egg->id = server->egg_id;
    server->egg_id++;
    sprintf(response, "enw %d %d %d %d\n", egg->id,
        server->client_data[server->currentclient].id, x, y);
    send_msg_graphic(server, response);
    add_egg(server, egg);
}
