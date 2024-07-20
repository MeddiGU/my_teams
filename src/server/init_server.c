/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-meddi.gueran
** File description:
** init_server
*/

#include "../../include/my.h"

void init_serv(server_s *server)
{
    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    error_socket(server);
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    server->server_addr.sin_port = htons(server->port);
    server->client_head = NULL;
    server->logout = 0;
    sameport(server);
    if (bind(server->server_socket, (struct sockaddr *)&(server->server_addr),
        sizeof(server->server_addr)) < 0) {
        perror("Binding failed");
        close(server->server_socket);
        exit(84);
    }
    if (listen(server->server_socket, 10) < 0) {
        perror("Listening failed");
        close(server->server_socket);
        exit(84);
    }
}

void init_fd(server_s *server)
{
    FD_ZERO(&server->read_fds);
    FD_ZERO(&server->tmp_fds);
    FD_SET(server->server_socket, &server->read_fds);
}

void sameport(server_s *server)
{
    int reuseaddr = 1;

    if (setsockopt(server->server_socket, SOL_SOCKET, SO_REUSEADDR,
        &reuseaddr, sizeof(int)) == -1) {
        perror("setsockopt failed");
        close(server->server_socket);
        exit(EXIT_FAILURE);
    }
}

void error_socket(server_s *server)
{
    if (server->server_socket == -1) {
        perror("Failed to create socket");
        exit(84);
    }
}
