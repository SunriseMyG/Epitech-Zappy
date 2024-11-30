/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** set_object
*/

#include "../include/server.h"

void remove_object_to_client2(server_t *server, tile_t *tile, char *object)
{
    char response[256];
    inventory_t *inv =
        server->client_data[server->currentclient].inv;

    if (inv->mendiane > 0 && strcmp(object, "MENDIANE") == 0) {
        tile->resources.mendiane++;
        inv->mendiane--;
    }
    if (inv->phiras > 0 && strcmp(object, "PHIRAS") == 0) {
        tile->resources.phiras++;
        inv->phiras--;
    }
    if (inv->thystame > 0 && strcmp(object, "THYSTAME") == 0) {
        tile->resources.thystame++;
        inv->thystame--;
    }
    sprintf(response, "pdr %d %d\n",
        server->client_data[server->currentclient].id,
        get_resource_number(object));
    send_msg_graphic(server, response);
}

void remove_object_to_client(server_t *server, tile_t *tile, char *object)
{
    inventory_t *inv =
        server->client_data[server->currentclient].inv;

    if (inv->food > 0 && strcmp(object, "FOOD") == 0) {
        tile->resources.food++;
        inv->food--;
    }
    if (inv->linemate > 0 && strcmp(object, "LINEMATE") == 0) {
        tile->resources.linemate++;
        inv->linemate--;
    }
    if (inv->deraumere > 0 && strcmp(object, "DERAUMERE") == 0) {
        tile->resources.deraumere++;
        inv->deraumere--;
    }
    if (inv->sibur > 0 && strcmp(object, "SIBUR") == 0) {
        tile->resources.sibur++;
        inv->sibur--;
    }
    remove_object_to_client2(server, tile, object);
}

bool verif_capacity_set(server_t *server, char *object)
{
    inventory_t *client_inventory =
        server->client_data[server->currentclient].inv;

    if (strcmp(object, "FOOD") == 0 && client_inventory->food > 0)
        return true;
    if (strcmp(object, "LINEMATE") == 0 && client_inventory->linemate > 0)
        return true;
    if (strcmp(object, "DERAUMERE") == 0 && client_inventory->deraumere > 0)
        return true;
    if (strcmp(object, "SIBUR") == 0 && client_inventory->sibur > 0)
        return true;
    if (strcmp(object, "MENDIANE") == 0 && client_inventory->mendiane > 0)
        return true;
    if (strcmp(object, "PHIRAS") == 0 && client_inventory->phiras > 0)
        return true;
    if (strcmp(object, "THYSTAME") == 0 && client_inventory->thystame > 0)
        return true;
    return false;
}

void set_object(server_t *server, char **args)
{
    int x = server->client_data[server->currentclient].position.x;
    int y = server->client_data[server->currentclient].position.y;
    tile_t *tile = &server->map[y][x];

    if (args[0] == NULL)
        return;
    args[0] = strtrim(args[0]);
    for (int i = 0; args[0][i]; i++)
        args[0][i] = toupper(args[0][i]);
    if (verif_capacity_set(server, args[0])) {
        remove_object_to_client(server, tile, args[0]);
        dprintf(getclientsocket(server), "ok\n");
    } else
        dprintf(getclientsocket(server), "ko\n");
}
