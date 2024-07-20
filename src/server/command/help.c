/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** Help Command
*/

#include "../../../include/my.h"

void help(server_s *server)
{
    server->check = 1;
    if (server->current->is_logged == false) {
        dprintf(server->current->socket, "530\n\r");
        return;
    }
    dprintf(server->current->socket, "214\n\r");
}
