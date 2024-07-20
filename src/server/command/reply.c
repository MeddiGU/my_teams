/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** thread
*/

#include "../../../include/my.h"

void create_reply(server_s *server, char **tab)
{
    char *reply_desc = remove_char_quote(tab[1]);

    write_reply_db(reply_desc, server);
    server_event_reply_created(server->current->current_thread,
        server->current->uuid, reply_desc);
    dprintf(server->current->socket, "265 %s %s %s\n\r",
        server->current->current_thread, server->current->uuid,
        tab[1]);
}

void write_reply_db(char *reply_desc, server_s *server)
{
    FILE *file;
    char *path = malloc(sizeof(char) * 100);

    strcpy(path, "database/reply/");
    strcat(path, server->current->uuid);
    strcat(path, ".txt");
    file = fopen(path, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s::%s::%s\n", server->current->uuid,
        server->current->current_thread, reply_desc);
    fclose(file);
}

void reply_all(server_s *server, char *reply_desc)
{
    client_info *current = server->client_head;

    while (current != NULL) {
        if (strcmp(current->current_channel, server->current->current_channel)
            == 0 && current->socket != server->current->socket) {
            dprintf(current->socket, "265 %s %s %s\n\r",
                server->current->current_thread, server->current->uuid,
                reply_desc);
        }
        current = current->next;
    }
}

void send_user(server_s *server, char **tab, char *uuid)
{
    dprintf(server->current->socket, "261 %s %s\n\r",
        server->current->uuid, tab[2]);
    server_event_user_subscribed(uuid, server->current->uuid);
}