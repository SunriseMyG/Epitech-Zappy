/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** time
*/

#include "../include/server.h"

float get_time_diff(server_t *server)
{
    struct timespec current_time;
    double diff_in_seconds;

    clock_gettime(CLOCK_REALTIME, &current_time);
    diff_in_seconds = (current_time.tv_sec - server->last_time.tv_sec) +
        (current_time.tv_nsec - server->last_time.tv_nsec) / 1e9;
    return (float)diff_in_seconds;
}
