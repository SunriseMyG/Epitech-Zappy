##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile for Zappy
##

SERVER    =    ./src/main.c \
            ./src/get_server_input.c \
            ./src/help.c \
            ./src/init_server.c \
            ./src/get_client_socket.c \
            ./src/command_handler.c \
            ./src/my_recv.c \
            ./src/strtrim.c \
            ./src/command_init.c \
            ./src/map.c \
            ./src/resources.c \
            ./src/elevation.c \
            ./src/elevation_one_to_two.c \
            ./src/elevation_two_to_three.c \
            ./src/elevation_three_to_four.c \
            ./src/elevation_four_to_five.c \
            ./src/elevation_five_to_six.c \
            ./src/elevation_six_to_seven.c \
            ./src/elevation_seven_to_eight.c \
            ./src/mouvement.c \
            ./src/inventory.c \
            ./src/player.c \
            ./src/team.c \
            ./src/time_unit.c \
            ./src/args_parser.c \
            ./src/disconnection.c \
            ./src/pnw.c \
            ./src/bct.c \
            ./src/allocate_map.c \
            ./src/eject.c \
            ./src/vision.c \
            ./src/send_msg_graphic.c \
            ./src/getplayerbyid.c \
            ./src/get_resources.c \
            ./src/take_object.c \
            ./src/set_object.c \
            ./src/resource_number.c \
            ./src/broadcast.c \
            ./src/egg.c \
            ./src/waiting_commands.c \
            ./src/fork.c \
            ./src/time.c \
            ./src/world.c \
            ./src/resources_checker.c \

DEBUG_FLAGS = -std=gnu17 -Wall -Wextra -g3

SERVER_EXECUTABLE_NAME =    ../zappy_server

all:    build

build:
	@gcc $(SERVER) $(DEBUG_FLAGS) -o $(SERVER_EXECUTABLE_NAME) -lm

clean:
	@rm -rf *.o

fclean:    clean
	@rm -rf $(SERVER_EXECUTABLE_NAME)

re:    fclean build

coding-style:
	@coding-style . .
	@clear
	@cat coding-style-reports.log
	@rm -f coding-style-reports.log

.PHONY: all build clean fclean re coding-style