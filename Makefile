##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

all:    build

build:
	@make -C server/
	@make -C ia/

clean:
	@make clean -C server/
	@make clean -C ia/
	@rm -rf build/
	@rm -f zappy_gui

fclean:    clean
	@make fclean -C server/
	@make fclean -C ia/

re:    fclean build

coding-style:
	@coding-style . .
	@clear
	@cat coding-style-reports.log
	@rm -f coding-style-reports.log

.PHONY: all build clean fclean re coding-style