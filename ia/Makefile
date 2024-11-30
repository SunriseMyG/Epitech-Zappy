##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME    = zappy_ai
SRC_DIR = $(shell pwd)
SRC     = $(wildcard $(SRC_DIR)/*.py) 

all: $(NAME)

$(NAME): $(SRC)
	@echo '#!/usr/bin/env python3' > $(NAME)
	@echo 'import sys' >> $(NAME)
	@echo "sys.path.insert(0, '$(SRC_DIR)')" >> $(NAME)
	@cat $(SRC) | grep -v "__name__ == '__main__'" >> $(NAME)
	@chmod +x $(NAME)
	@mv $(NAME) ../$(NAME)

clean:
	@rm -f ../$(NAME)

fclean: clean

re: fclean all