/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** resource_number
*/

#include "../include/server.h"

int get_resource_number(char *object)
{
    if (strcmp(object, "FOOD") == 0)
        return 0;
    if (strcmp(object, "LINEMATE") == 0)
        return 1;
    if (strcmp(object, "DERAUMERE") == 0)
        return 2;
    if (strcmp(object, "SIBUR") == 0)
        return 3;
    if (strcmp(object, "MENDIANE") == 0)
        return 4;
    if (strcmp(object, "PHIRAS") == 0)
        return 5;
    if (strcmp(object, "THYSTAME") == 0)
        return 6;
    return -1;
}
