/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-meddi.gueran
** File description:
** server
*/

#include "../../include/my.h"

void read_data(server_s *server)
{
    server->current = server->client_head;
    while (server->current != NULL) {
        if (FD_ISSET(server->current->socket, &server->tmp_fds)) {
            read_command(server);
        }
        if (server->logout != 1)
            server->current = server->current->next;
        server->logout = 0;
    }
}

void read_command(server_s *server)
{
    char buffer[1024];
    ssize_t bytes_read = read(server->current->socket, buffer, sizeof(buffer));

    if (bytes_read == -1) {
        perror("Failed to read data from client");
    } else {
        buffer[bytes_read] = '\0';
        do_command(server, buffer);
    }
}

int loop(server_s *server)
{
    int activity = 0;

    init_serv(server);
    init_fd(server);
    server->max_fds = server->server_socket;
    load_client(server);
    while (1) {
        server->tmp_fds = server->read_fds;
        add_client_queue(server);
        activity = select(server->max_fds + 1, &server->tmp_fds,
            NULL, NULL, NULL);
        if (activity == -1) {
            perror("Select failed");
            exit(EXIT_FAILURE);
        }
        handle_client(server);
        read_data(server);
    }
    close(server->server_socket);
    return 0;
}
