##
## EPITECH PROJECT, 2024
## B-NWP-400-MAR-4-1-myteams-meddi.gueran
## File description:
## Makefile
##

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
RESET=\033[0m

SRC	=	src/server/*.c \
		src/server/usage/*.c \
		src/server/command/*.c \
		src/server/list_chaine/*.c \
		src/utils/*.c

FLAGS	=	-luuid -L./libs/myteams -lmyteams

all:
	make myteams_server
	make myteam_cli

myteams_server:
	@echo "${YELLOW}Compiling server...${RESET}"
	gcc -o myteams_server ${SRC} ${FLAGS}
	@echo "${GREEN}Done.${RESET}"

myteam_cli:
	@echo "${CYAN}Compiling client...${RESET}"
	gcc -o myteams_cli src/client/*.c src/utils/*.c ${FLAGS}
	@echo "${GREEN}Done.${RESET}"

clean:
	rm -f myteams_cli
	rm -f myteams_server

fclean: clean

re: clean all
