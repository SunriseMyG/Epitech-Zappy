/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** my_recv
*/

#include "../include/server.h"

ssize_t my_recv(int socket_fd, void *buf, size_t len)
{
    ssize_t ret = read(socket_fd, buf, len);

    return ret;
}
