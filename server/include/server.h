/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-steven.deffontaine [WSL : Ubuntu]
** File description:
** server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <getopt.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#ifndef INCLUDED_SERVER_H
    #define INCLUDED_SERVER_H

typedef struct server_t server_t;

typedef void (*command_function_t)(server_t *, char **);

enum direction {
    N = 0,
    E = 1,
    S = 2,
    W = 3
};

typedef struct waiting_command_s {
    char *command;
    int time_remaining;
    int currentclient;
    struct waiting_command_s *next;
} waiting_command_t;

typedef struct command_time_s {
    char *command;
    int time;
} command_time_t;

typedef struct position_s {
    int x;
    int y;
} position_t;

typedef struct egg_s {
    position_t position;
    char *team_name;
    int id;
} egg_t;

typedef struct inventory_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} inventory_t;

typedef struct {
    char *name;
    command_function_t function;
    bool is_graphic;
} command_t;

typedef struct client_data_s {
    int id;
    int socket;
    int life;
    int elevation;
    inventory_t *inv;
    enum direction direction;
    position_t position;
    char *team_name;
    bool locked;
} client_data_t;

typedef struct team_s {
    char *name;
    int clients_nb;
    int clients_max;
} team_t;

typedef struct resources_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} resources_t;


typedef struct tile_s {
    char c;
    resources_t resources;
} tile_t;

struct server_t {
    int port;
    int width;
    int height;
    team_t *teams;
    int count_team;
    int freq;
    // message received
    char *buffer;
    int valread;
    //socket
    int socket;
    int activity;
    int addrlen;
    fd_set readfds;
    fd_set writefds;
    struct sockaddr_in address;
    struct timespec last_time;
    //waiting command
    waiting_command_t *waiting_commands;
    command_time_t *command_time;
    int nbr_waiting_commands;
    //client
    client_data_t client_data[FD_SETSIZE];
    int client_socket[FD_SETSIZE];
    int currentclient;
    int client_nbr;
    int id_increment;
    bool winned;
    // command
    command_t *commands;
    int nbr_commands;
    //map
    tile_t **map;
    //temp
    int player_x;
    int player_y;
    int x;
    int y;
    int player_on_tile;
    char *ressource;
    //egg
    int count_eggs;
    int egg_id;
    egg_t **eggs;
    //world
    int world_clock;
};

void fill_team_name(server_t *server, char **argv);
void fill_server_input(server_t *server, int opt, char **argv);
void parse_server_input(int argc, char **argv, server_t *server);
void dump_input(server_t *server);
void client_dump(server_t *server, int client_socket);
void print_help(void);
void *bind_socket(server_t *server);
void create_socket(server_t *server);
int getclientsocket(server_t *server);
void init_client(server_t *server, int client_socket);
void receive_message(server_t *server);
void manage_message(server_t *server, int i);
void traitement(server_t *server, int i);
void command_handler(server_t *server, char *command);
void command_init(server_t *server);
char *strtrim(char *str);
ssize_t my_recv(int socket_fd, void *buf, size_t len);
server_t *init_server(server_t *server);
void direction_dump(server_t *server, int client_socket);
void get_time_unit(server_t *server, char **args);
void update_time_unit(server_t *server, char **args);
char **args_parser(char *command);
void disconnection(server_t *server, int i);
void pnw(server_t *server, int client_socket);
void bct(server_t *server, char **args);
void mct(server_t *server, char **args);
void allocate_map(server_t *server);
void generate_resources(server_t *server, bool reset_map);
void vision(server_t *server, char **args);
void send_msg_graphic(server_t *server, char *data);
int getclientsocketbyid(server_t *server, int id);
void take_object(server_t *server, char **args);
void set_object(server_t *server, char **args);
int get_resource_number(char *object);
void generate_egg(server_t *server, char *team_name, int x, int y);
egg_t *get_egg_by_team(server_t *server, char *team_name);
void remove_egg(server_t *server, egg_t *egg);
void add_waiting_command(server_t *server, char *command, int socket);
void check_waiting_commands(server_t *server);
char *beautify_command(char *command);
void init_table_commands_time(server_t *server);
void fork_cmd(server_t *server, char **args);
float get_time_diff(server_t *server);
void start_msg_incantation(server_t *server);
void start_msg_fork(server_t *server);
void send_egg_pos(server_t *server, int socket);
void world_clock(server_t *server);
void checknbroffoodinmap(server_t *server, int *food);
void checknbrofresourcesinmap(server_t *server, int *nb_linemate,
    int *nb_deraumere, int *nb_sibur);
void checknbrofresourcesinmap2(server_t *server, int *nb_mendiane,
    int *nb_phiras, int *nb_thystame);

// mouvement
void move_forward(server_t *server, char **args);
void move_right(server_t *server, char **args);
void move_left(server_t *server, char **args);
char get_player_orientation(server_t *server, int player_id);

// map
void malloc_map(server_t *server);
void display_map(server_t *server);
void free_map(server_t *server);
void map_size(server_t *server, char **args);

// inventory
void inventory(server_t *server, char **args);
void player_inventory(server_t *server, char **args);
void init_inventory(server_t *server);

// player & team
void player_position(server_t *server, char **args);
void all_team_name(server_t *server, char **args);
void player_level(server_t *server, char **args);
void eject_players(server_t *server, char **args);
void enterteam(server_t *server, int i, char *buffer);
void case_eject_players(server_t *server, char orientation,
    int i, char *message);
void connect_nbr(server_t *server, char **args);
void manage_life_for_player(server_t *server);

// incantation
void incantation(server_t *server, char **args);
void incantation_next(server_t *server);
void result_incantation_server_ok(server_t *server);
void result_incantation_server_ko(server_t *server);
void check_player_elevation_two(server_t *server, int i,
    int *elevation_success);
void manage_elevation_one_to_two(server_t *server);
int elevation_two_to_three(server_t *server);
void manage_elevation_two_to_three(server_t *server);
int elevation_three_to_four(server_t *server);
void manage_elevation_three_to_four(server_t *server);
int elevation_four_to_five(server_t *server);
void manage_elevation_four_to_five(server_t *server);
int elevation_five_to_six(server_t *server);
void manage_elevation_five_to_six(server_t *server);
int elevation_six_to_seven(server_t *server);
void manage_elevation_six_to_seven(server_t *server);
int elevation_seven_to_eight(server_t *server);
void manage_elevation_seven_to_eight(server_t *server);

// vision
char *get_ressource(server_t *server, char *ressource, int x, int y);
char *get_ressource_from_tile(server_t *server, int x, int y);
void get_position(server_t *server, int j, int i);
void init_vision(server_t *server);
void end_vision(server_t *server, char *vision);
void manage_vision(server_t *server, char *vision, int i, int j);
void vision(server_t *server, char **args);

// broadcast
void broadcast(server_t *server, char **args);

int check_win(server_t *server);

#endif // INCLUDED_SERVER_H
