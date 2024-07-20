/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-meddi.gueran
** File description:
** command
*/

#include "../../../include/my.h"

void do_command(server_s *server, char *buffer)
{
    server->check = 0;
    if (basic_command(server, buffer) == 1)
        return;
    if (team_command(server, buffer) == 1)
        return;
    if (strncmp(buffer, "/messages", 9) == 0) {
        messages(server, buffer);
    }
    if (strncmp(buffer, "/send", 5) == 0) {
        send_main(server, buffer);
    }
    if (strncmp(buffer, "/users", 6) == 0) {
        users(server, buffer);
    } else if (strncmp(buffer, "/user", 5) == 0) {
        user(server, buffer);
    } else {
        use_command(server, buffer);
    }
    if (server->check == 0)
        dprintf(server->current->socket, "550 Invalid Command\n\r");
}

int basic_command(server_s *server, char *buffer)
{
    if (strncmp(buffer, "/login", 6) == 0) {
        login(server, buffer);
        dprintf(server->current->socket, "\r");
        return 1;
    }
    if (strncmp(buffer, "/logout", 7) == 0 || strlen(buffer) == 0) {
        logout(server, buffer);
        return 1;
    }
    if (strncmp(buffer, "/help", 5) == 0) {
        help(server);
        return 1;
    }
    return 0;
}

int team_command(server_s *server, char *buffer)
{
    if (strncmp(buffer, "/create", 7) == 0) {
        create(server, buffer);
        return 1;
    }
    if (strncmp(buffer, "/subscribed", 11) == 0) {
        subscribed(server, buffer);
        return 1;
    } else if (strncmp(buffer, "/subscribe", 10) == 0) {
        subscribe(server, buffer);
        return 1;
    }
    if (strncmp(buffer, "/unsubscribe", 12) == 0) {
        unsubscribe(server, buffer);
        return 1;
    }
    return 0;
}

int use_command(server_s *server, char *buffer)
{
    if (strncmp(buffer, "/use", 4) == 0) {
        use(server, buffer);
        return 1;
    }
    return 0;
}