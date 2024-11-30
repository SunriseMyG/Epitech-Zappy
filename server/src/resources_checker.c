/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** resouces checker
*/

#include "../include/server.h"

void checknbroffoodinmap(server_t *server, int *food)
{
    int nbr_food = 0;

    for (int y = 0; y < server->height; y++)
        for (int x = 0; x < server->width; x++)
            nbr_food += server->map[y][x].resources.food;
    *food = *food - nbr_food;
    printf("%d Food Generated | Food on map : %d\n", *food, nbr_food);
}

void checknbrofresourcesinmap(server_t *server, int *nb_linemate,
    int *nb_deraumere, int *nb_sibur)
{
    int nbr_linemate = 0;
    int nbr_deraumere = 0;
    int nbr_sibur = 0;

    for (int y = 0; y < server->height; y++)
        for (int x = 0; x < server->width; x++) {
            nbr_linemate += server->map[y][x].resources.linemate;
            nbr_deraumere += server->map[y][x].resources.deraumere;
            nbr_sibur += server->map[y][x].resources.sibur;
        }
    *nb_linemate = *nb_linemate - nbr_linemate;
    *nb_deraumere = *nb_deraumere - nbr_deraumere;
    *nb_sibur = *nb_sibur - nbr_sibur;
    printf("%d Linemate Generated | Linemate on map : %d\n",
        *nb_linemate, nbr_linemate);
    printf("%d Deraumere Generated | Deraumere on map : %d\n",
        *nb_deraumere, nbr_deraumere);
    printf("%d Sibur Generated | Sibur on map : %d\n",
        *nb_sibur, nbr_sibur);
}

void checknbrofresourcesinmap2(server_t *server, int *nb_mendiane,
    int *nb_phiras, int *nb_thystame)
{
    int nbr_mendiane = 0;
    int nbr_phiras = 0;
    int nbr_thystame = 0;

    for (int y = 0; y < server->height; y++)
        for (int x = 0; x < server->width; x++) {
            nbr_mendiane += server->map[y][x].resources.mendiane;
            nbr_phiras += server->map[y][x].resources.phiras;
            nbr_thystame += server->map[y][x].resources.thystame;
        }
    *nb_mendiane = *nb_mendiane - nbr_mendiane;
    *nb_phiras = *nb_phiras - nbr_phiras;
    *nb_thystame = *nb_thystame - nbr_thystame;
    printf("%d Mendiane Generated | Mendiane on map : %d\n",
        *nb_mendiane, nbr_mendiane);
    printf("%d Phiras Generated | Phiras on map : %d\n",
        *nb_phiras, nbr_phiras);
    printf("%d Thystame Generated | Thystame on map : %d\n",
        *nb_thystame, nbr_thystame);
}
