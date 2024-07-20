/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** main
*/

#include "../../include/my.h"

int main(int ac, char **av)
{
    server_s *server = malloc(sizeof(server_s));

    if (ac > 2)
        return 84;
    if (ac < 2) {
        return 84;
    } else if (ac == 2 && strcmp(av[1], "-help") == 0) {
        usage_server();
        return 0;
    } else {
        server->port = atoi(av[1]);
        loop(server);
    }
    return 0;
}
