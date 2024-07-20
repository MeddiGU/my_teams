/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** logout
*/

#include "../../../include/my.h"

void logout(server_s *server, char *buffer)
{
    server->check = 1;
    if (server->current->is_logged == false) {
        dprintf(server->current->socket, "530\n");
        return;
    }
    if (server->current->username == NULL) {
        dprintf(server->current->socket, "530\n");
        return;
    }
    send_logout(server);
    dprintf(server->current->socket, "231 %s %s\n\r",
        server->current->uuid, server->current->username);
    server_event_user_logged_out(server->current->uuid);
    close(server->current->socket);
    deletenodeatposition(server);
    server->logout = 1;
}

void send_logout(server_s *server)
{
    client_info *current = server->client_head;

    for (; current != NULL; current = current->next) {
        if (current->is_logged == true &&
            current->socket != server->current->socket) {
            dprintf(current->socket, "234 %s %s\n\r",
                server->current->uuid, server->current->username);
        }
    }
}