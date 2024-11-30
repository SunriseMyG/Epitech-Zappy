/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-steven.deffontaine [WSL : Ubuntu]
** File description:
** get_server_input
*/

#include "../include/server.h"

void dump_input(server_t *server)
{
    int i = 0;

    printf("port: %d\n", server->port);
    printf("width: %d\n", server->width);
    printf("height: %d\n", server->height);
    printf("clients_nb_by_team: %d\n", server->teams[0].clients_max);
    for (i = 0; i < server->count_team; i++)
        printf("names: %s \n", server->teams[i].name);
    printf("freq: %d\n", server->freq);
}

void fill_team_name(server_t *server, char **argv)
{
    int count = 0;

    for (int i = 0; i < server->count_team; i++)
        free(server->teams[i].name);
    free(server->teams);
    server->teams = NULL;
    server->count_team = 0;
    while (argv[count + (optind - 1)] &&
        !strrchr(argv[count + (optind - 1)], '-')) {
        server->teams = realloc(server->teams, sizeof(team_t) *
            (server->count_team + 1));
        server->teams[server->count_team].name =
            strdup(argv[count + (optind - 1)]);
        server->teams[server->count_team].clients_nb = 0;
        server->teams[server->count_team].clients_max = 0;
        server->count_team++;
        count++;
    }
}

void fill_server_input(server_t *server, int opt, char **argv)
{
    if (opt == 'p')
        server->port = atoi(optarg);
    if (opt == 'x') {
        server->width = atoi(optarg);
        if (server->width <= 0)
            exit(84);
    }
    if (opt == 'y') {
        server->height = atoi(optarg);
        if (server->height <= 0)
            exit(84);
    }
    if (opt == 'c')
        for (int i = 0; i < server->count_team; i++)
            server->teams[i].clients_max = atoi(optarg);
    if (opt == 'n')
        fill_team_name(server, argv);
    if (opt == 'f')
        server->freq = atoi(optarg);
    return;
}

void create_default_team(server_t *server, int team_option_used)
{
    if (!team_option_used) {
        server->teams = malloc(2 * sizeof(team_t));
        if (!server->teams)
            exit(84);
        server->count_team = 2;
        server->teams[0].name = strdup("team1");
        server->teams[0].clients_max = 2;
        server->teams[1].name = strdup("team2");
        server->teams[1].clients_max = 2;
    }
}

void parse_server_input(int argc, char **argv, server_t *server)
{
    int opt = 0;
    int team_option_used = 0;

    server->freq = 100;
    server->port = 4242;
    server->width = 10;
    server->height = 10;
    while (opt != -1) {
        opt = getopt(argc, argv, "p:x:y:n:c:f:");
        if (opt == 'n') {
            team_option_used = 1;
            fill_team_name(server, argv);
        } else
            fill_server_input(server, opt, argv);
    }
    create_default_team(server, team_option_used);
    dump_input(server);
    return;
}
