/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** client_thread_reply
*/

#include "../../include/client.h"

int thread_reply(client_s *client, time_t t)
{
    char *name;
    char *desc;

    if (strncmp(client->cmd[0], "264", 3) == 0) {
        name = remove_char_quote(client->cmd[3]);
        desc = remove_char_quote(client->cmd[4]);
        client_print_thread_created(client->cmd[1], client->cmd[2],
            t, name, desc);
        client_print_thread(client->cmd[1], client->cmd[2], t,
            name, desc);
        return 1;
    }
    if (strncmp(client->cmd[0], "265", 3) == 0) {
        desc = remove_char_quote(client->cmd[3]);
        client_print_reply_created(client->cmd[1], client->cmd[2],
        t, desc);
        return 1;
    }
    return 0;
}