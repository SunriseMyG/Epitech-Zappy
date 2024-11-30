/*
** EPITECH PROJECT, 2024
** zappy [WSL : Ubuntu]
** File description:
** command_init
*/

#include "../include/server.h"

void help_cli(server_t *server, char **args)
{
    char *help = "This is a test\n";

    (void)args;
    send(getclientsocket(server), help, strlen(help), 0);
}

void temp_stuff(server_t *server, char **args)
{
    (void)args;
    server->client_data[server->currentclient].inv->linemate = 10;
    server->client_data[server->currentclient].inv->deraumere = 10;
    server->client_data[server->currentclient].inv->sibur = 10;
    server->client_data[server->currentclient].inv->mendiane = 10;
    server->client_data[server->currentclient].inv->phiras = 10;
    server->client_data[server->currentclient].inv->thystame = 10;
    server->client_data[server->currentclient].inv->food = 100;
    send(getclientsocket(server), "Inventory updated\n", 19, 0);
}

void command_init(server_t *server)
{
    command_t commands[] = {
        {"HELP", help_cli, false}, {"STUFF", temp_stuff, false}, {"SST",
        update_time_unit, true}, {"LEFT", move_left, false}, {"RIGHT",
        move_right, false}, {"FORWARD", move_forward, false}, {"INVENTORY",
        inventory, false}, {"MSZ", map_size, true}, {"PPO", player_position,
        true}, {"TNA", all_team_name, true}, {"SGT", get_time_unit, true},
        {"PLV", player_level, true}, {"PIN", player_inventory, true},
        {"INCANTATION", incantation, false}, {"BCT", bct, true}, {"MCT", mct,
        true}, {"EJECT", eject_players, false}, {"LOOK", vision, false},
        {"CONNECT_NBR", connect_nbr, false}, {"TAKE", take_object, false},
        {"SET", set_object, false}, {"BROADCAST", broadcast, false},
        {"FORK", fork_cmd, false}
    };

    server->nbr_commands = sizeof(commands) / sizeof(command_t);
    server->commands = malloc(sizeof(commands));
    for (int i = 0; i < server->nbr_commands; i++) {
        server->commands[i] = commands[i];
    }
    printf("🚀 %d Commands Loadeds\n", server->nbr_commands);
}
