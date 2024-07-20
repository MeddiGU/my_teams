/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** main
*/

#include "../../include/client.h"

void usage_client(void)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip is the server ip address on which the");
    printf(" server socket listens\n");
    printf("\tport is the port number on which the server socket listens\n");
}

int main(int ac, char **av)
{
    if (ac < 3 || ac > 3) {
        return 84;
    } else if (ac == 2 && av[1] == "-help") {
        usage_client();
        return 0;
    } else {
        myteams_cli(av[1], atoi(av[2]));
    }
    return 0;
}
