/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-steven.deffontaine [WSL : Ubuntu]
** File description:
** init_server
*/

#include "../include/server.h"

void *bind_socket(server_t *server)
{
    if (bind(server->socket, (struct sockaddr *)&server->address,
        sizeof(server->address)) < 0) {
        perror("bind failed");
        exit(84);
    }
    if (listen(server->socket, 3) < 0) {
        perror("listen failed");
        exit(84);
    }
    return server;
}

server_t *init_server(server_t *server)
{
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    server->client_nbr = 0;
    if (server->socket == 0) {
        perror("socket failed");
        exit(84);
    }
    server->last_time = (struct timespec){0, 0};
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    server->id_increment = 0;
    server->winned = false;
    bind_socket(server);
    server->addrlen = sizeof(server->address);
    generate_resources(server, true);
    printf("Server started on port %d\n", server->port);
    return server;
}

void connection_socket(server_t *server)
{
    for (server->currentclient = 0; server->currentclient < FD_SETSIZE;
        server->currentclient++) {
        if (getclientsocket(server) == 0) {
            server->client_socket[server->currentclient] =
                accept(server->socket, (struct sockaddr *)&server->address,
                (socklen_t *)&server->addrlen);
            printf("🌐 New connection, socket fd : %d, ip : %s, port : %d\n",
                getclientsocket(server),
                inet_ntoa(server->address.sin_addr),
                ntohs(server->address.sin_port));
            send(getclientsocket(server), "WELCOME\n", 8, 0);
            FD_SET(getclientsocket(server), &server->readfds);
            server->client_nbr++;
            printf("Number of connections : %d\n", server->client_nbr);
            break;
        }
    }
}

void loop_socket(server_t *server)
{
    FD_ZERO(&server->readfds);
    FD_ZERO(&server->writefds);
    FD_SET(server->socket, &server->readfds);
    for (int i = 0; i < FD_SETSIZE; i++)
        if (server->client_socket[i] > 0) {
            FD_SET(server->client_socket[i], &server->readfds);
            FD_SET(server->client_socket[i], &server->writefds);
        }
    server->activity = select(FD_SETSIZE, &server->readfds,
        &server->writefds, NULL, NULL);
    if (get_time_diff(server) >= 1.0 / server->freq) {
        clock_gettime(CLOCK_REALTIME, &server->last_time);
        check_waiting_commands(server);
        world_clock(server);
    }
    if (FD_ISSET(server->socket, &server->readfds))
        connection_socket(server);
    receive_message(server);
}

void create_socket(server_t *server)
{
    while (1) {
        if (server->winned == true)
            continue;
        loop_socket(server);
    }
    close(server->socket);
    free(server);
}
