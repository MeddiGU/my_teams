/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** init_client
*/

#include "../../include/client.h"

void myteams_cli(char *ip, int port)
{
    client_s *client = malloc(sizeof(client_s));
    struct sockaddr_in server_address;

    client->sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->sockFd == -1) {
        perror("socket");
        exit(84);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip);
    if (connect(client->sockFd, (struct sockaddr *)&server_address,
        sizeof(server_address)) == -1) {
            perror("connect");
            exit(84);
        }
    loop_client(client);
    close(client->sockFd);
}

void loop_client(client_s *client)
{
    fd_set current_sock;
    fd_set ready_sock;
    char *line = NULL;
    size_t size;

    set_fd(client, &current_sock);
    while (1) {
        ready_sock = current_sock;
        if (select(client->sockFd + 1, &ready_sock, NULL, NULL, NULL) < 0) {
            exit(84);
        }
        if (FD_ISSET(client->sockFd, &ready_sock)) {
            get_command(client);
        }
        if (FD_ISSET(0, &ready_sock)) {
            line = NULL;
            getline(&line, &size, stdin);
            send_msg(client, line);
        }
    }
}

void set_fd(client_s *client, fd_set *current_sock)
{
    FD_ZERO(current_sock);
    FD_SET(client->sockFd, current_sock);
    FD_SET(0, current_sock);
}

void send_msg(client_s *client, char *line)
{
    line = login_client(client, line);
    send(client->sockFd, line, strlen(line), 0);
}
