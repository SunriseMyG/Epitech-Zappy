/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** resources
*/

#include "../include/server.h"

int calcul_density(float density, server_t *server)
{
    float result = 0;

    result = (density * server->height * server->width);
    return (int)result;
}

void place_resource(server_t *server, char *resource)
{
    int x = rand() % server->width;
    int y = rand() % server->height;

    if (strcmp(resource, "food") == 0)
        server->map[y][x].resources.food += 1;
    if (strcmp(resource, "linemate") == 0)
        server->map[y][x].resources.linemate += 1;
    if (strcmp(resource, "deraumere") == 0)
        server->map[y][x].resources.deraumere += 1;
    if (strcmp(resource, "sibur") == 0)
        server->map[y][x].resources.sibur += 1;
    if (strcmp(resource, "mendiane") == 0)
        server->map[y][x].resources.mendiane += 1;
    if (strcmp(resource, "phiras") == 0)
        server->map[y][x].resources.phiras += 1;
    if (strcmp(resource, "thystame") == 0)
        server->map[y][x].resources.thystame += 1;
}

void generate_resources_2(server_t *server)
{
    int nb_mendiane = calcul_density(0.1, server);
    int nb_phiras = calcul_density(0.08, server);
    int nb_thystame = calcul_density(0.05, server);

    checknbrofresourcesinmap2(server, &nb_mendiane, &nb_phiras, &nb_thystame);
    for (int i = 0; i < nb_mendiane; i++)
        place_resource(server, "mendiane");
    for (int i = 0; i < nb_phiras; i++)
        place_resource(server, "phiras");
    for (int i = 0; i < nb_thystame; i++)
        place_resource(server, "thystame");
}

void set_resources_zeros(server_t *server)
{
    allocate_map(server);
    for (int y = 0; y < server->height; y++) {
        for (int x = 0; x < server->width; x++) {
            server->map[y][x].resources.food = 0;
            server->map[y][x].resources.linemate = 0;
            server->map[y][x].resources.deraumere = 0;
            server->map[y][x].resources.sibur = 0;
            server->map[y][x].resources.mendiane = 0;
            server->map[y][x].resources.phiras = 0;
            server->map[y][x].resources.thystame = 0;
        }
    }
}

void generate_resources(server_t *server, bool reset_map)
{
    int nb_food = calcul_density(0.5, server);
    int nb_linemate = calcul_density(0.3, server);
    int nb_deraumere = calcul_density(0.15, server);
    int nb_sibur = calcul_density(0.1, server);

    srand(time(NULL));
    if (reset_map == true)
        set_resources_zeros(server);
    checknbroffoodinmap(server, &nb_food);
    checknbrofresourcesinmap(server, &nb_linemate,
        &nb_deraumere, &nb_sibur);
    for (int i = 0; i < nb_food; i++)
        place_resource(server, "food");
    for (int i = 0; i < nb_linemate; i++)
        place_resource(server, "linemate");
    for (int i = 0; i < nb_deraumere; i++)
        place_resource(server, "deraumere");
    for (int i = 0; i < nb_sibur; i++)
        place_resource(server, "sibur");
    generate_resources_2(server);
}
