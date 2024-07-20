/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-meddi.gueran
** File description:
** client
*/

#include "../../include/my.h"

void add_client_queue(server_s *server)
{
    server->current = server->client_head;
    while (server->current != NULL) {
        FD_SET(server->current->socket, &server->tmp_fds);
        if (server->current->socket > server->max_fds) {
            server->max_fds = server->current->socket;
        }
        server->current = server->current->next;
    }
}

void handle_client(server_s *server)
{
    socklen_t client_addr_len = sizeof(server->client_addr);

    server->current = server->client_head;
    if (FD_ISSET(server->server_socket, &server->tmp_fds)) {
        server->client_socket = accept(server->server_socket,
            (struct sockaddr *)&server->client_addr, &client_addr_len);
        if (server->client_socket == -1) {
            perror("Failed to accept connection");
            exit(84);
        } else {
            server->client_head = add_client(server->client_head,
                server->client_socket, server->client_addr, server);
            print_list(server->current);
            write(server->client_socket, "220\n\r", 5);
        }
    }
}

void load_client(server_s *server)
{
    FILE *file = fopen("database/user.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **tab = NULL;

    if (file == NULL)
        return;
    while (1) {
        read = getline(&line, &len, file);
        if (read == -1)
            break;
        tab = strtok_tab(line, ":\n");
        server_event_user_loaded(tab[0], tab[1]);
    }
    fclose(file);
}
