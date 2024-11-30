/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-steven.deffontaine [WSL : Ubuntu]
** File description:
** get_client_socket
*/

#include "../include/server.h"

int getclientsocket(server_t *server)
{
    return server->client_socket[server->currentclient];
}

void init_client(server_t *server, int client_socket)
{
    srand(time(NULL));
    server->client_data[server->currentclient].socket = client_socket;
    server->client_data[server->currentclient].inv =
        malloc(sizeof(inventory_t));
    server->client_data[server->currentclient].inv->food = 0;
    server->client_data[server->currentclient].inv->linemate = 0;
    server->client_data[server->currentclient].inv->deraumere = 0;
    server->client_data[server->currentclient].inv->sibur = 0;
    server->client_data[server->currentclient].inv->mendiane = 0;
    server->client_data[server->currentclient].inv->phiras = 0;
    server->client_data[server->currentclient].inv->thystame = 0;
    server->client_data[server->currentclient].direction = rand() % 4;
    server->client_data[server->currentclient].elevation = 1;
    server->client_data[server->currentclient].life = 10;
    server->client_data[server->currentclient].locked = false;
}

void direction_dump(server_t *server, int client_socket)
{
    int dir = server->client_data[client_socket].direction;

    if (dir == 0)
        printf("NORTH\n");
    if (dir == 1)
        printf("EAST\n");
    if (dir == 2)
        printf("SOUTH\n");
    if (dir == 3)
        printf("WEST\n");
}

void client_dump(server_t *server, int client_socket)
{
    for (int i = 0; i <= server->client_nbr; i++) {
        if (server->client_socket[i] == client_socket) {
            printf("currentclient: %d\n", server->currentclient);
            printf("socket: %d\n", server->client_data[i].socket);
            printf("life: %d\n", server->client_data[i].life);
            printf("elevation: %d\n", server->client_data[i].elevation);
            printf("inventory:\n");
            printf("food: %d\n", server->client_data[i].inv->food);
            printf("linemate: %d\n", server->client_data[i].inv->linemate);
            printf("deraumere: %d\n", server->client_data[i].inv->deraumere);
            printf("sibur: %d\n", server->client_data[i].inv->sibur);
            printf("mendiane: %d\n", server->client_data[i].inv->mendiane);
            printf("phiras: %d\n", server->client_data[i].inv->phiras);
            printf("thystame: %d\n", server->client_data[i].inv->thystame);
            printf("position: %d %d\n", server->client_data[i].position.x,
                server->client_data[i].position.y);
            printf("team_name: %s\n", server->client_data[i].team_name);
            direction_dump(server, i);
        }
    }
}
