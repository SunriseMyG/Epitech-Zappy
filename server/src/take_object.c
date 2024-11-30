/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** strtrim
*/

#include "../include/server.h"

void add_object_to_client2(server_t *server, tile_t *tile, char *object)
{
    char response[256];
    inventory_t *client_inventory =
        server->client_data[server->currentclient].inv;

    if (tile->resources.mendiane > 0 && strcmp(object, "MENDIANE") == 0) {
        tile->resources.mendiane--;
        client_inventory->mendiane++;
    }
    if (tile->resources.phiras > 0 && strcmp(object, "PHIRAS") == 0) {
        tile->resources.phiras--;
        client_inventory->phiras++;
    }
    if (tile->resources.thystame > 0 && strcmp(object, "THYSTAME") == 0) {
        tile->resources.thystame--;
        client_inventory->thystame++;
    }
    sprintf(response, "pgt %d %d\n",
        server->client_data[server->currentclient].id,
        get_resource_number(object));
    send_msg_graphic(server, response);
}

void add_object_to_client(server_t *server, tile_t *tile, char *object)
{
    inventory_t *client_inventory =
        server->client_data[server->currentclient].inv;

    if (tile->resources.food > 0 && strcmp(object, "FOOD") == 0) {
        tile->resources.food--;
        client_inventory->food++;
    }
    if (tile->resources.linemate > 0 && strcmp(object, "LINEMATE") == 0) {
        tile->resources.linemate--;
        client_inventory->linemate++;
    }
    if (tile->resources.deraumere > 0 && strcmp(object, "DERAUMERE") == 0) {
        tile->resources.deraumere--;
        client_inventory->deraumere++;
    }
    if (tile->resources.sibur > 0 && strcmp(object, "SIBUR") == 0) {
        tile->resources.sibur--;
        client_inventory->sibur++;
    }
    add_object_to_client2(server, tile, object);
}

bool verif_capacity_take(tile_t *tile, char *object)
{
    if (strcmp(object, "FOOD") == 0 && tile->resources.food > 0)
        return true;
    if (strcmp(object, "LINEMATE") == 0 && tile->resources.linemate > 0)
        return true;
    if (strcmp(object, "DERAUMERE") == 0 && tile->resources.deraumere > 0)
        return true;
    if (strcmp(object, "SIBUR") == 0 && tile->resources.sibur > 0)
        return true;
    if (strcmp(object, "MENDIANE") == 0 && tile->resources.mendiane > 0)
        return true;
    if (strcmp(object, "PHIRAS") == 0 && tile->resources.phiras > 0)
        return true;
    if (strcmp(object, "THYSTAME") == 0 && tile->resources.thystame > 0)
        return true;
    return false;
}

void take_object(server_t *server, char **args)
{
    int x = server->client_data[server->currentclient].position.x;
    int y = server->client_data[server->currentclient].position.y;
    tile_t *tile = &server->map[y][x];

    if (args[0] == NULL) {
        dprintf(getclientsocket(server), "ko\n");
        return;
    }
    args[0] = strtrim(args[0]);
    for (int i = 0; args[0][i]; i++)
        args[0][i] = toupper(args[0][i]);
    if (verif_capacity_take(tile, args[0])) {
        add_object_to_client(server, tile, args[0]);
        dprintf(getclientsocket(server), "ok\n");
    } else
        dprintf(getclientsocket(server), "ko\n");
}
