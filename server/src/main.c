/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-steven.deffontaine [WSL : Ubuntu]
** File description:
** main
*/

#include "../include/server.h"

void generate_team_egg(server_t *server)
{
    for (int i = 0; i < server->count_team; i++)
        for (int j = 0; j < server->teams[i].clients_max; j++)
            generate_egg(server, server->teams[i].name, -1, -1);
}

int main(int argc, char **argv)
{
    server_t *server = malloc(sizeof(server_t));

    if (argc == 2 && strcmp(argv[1], "-h") == 0)
        print_help();
    srand(time(NULL));
    parse_server_input(argc, argv, server);
    generate_team_egg(server);
    init_server(server);
    command_init(server);
    init_table_commands_time(server);
    create_socket(server);
    return 0;
}
