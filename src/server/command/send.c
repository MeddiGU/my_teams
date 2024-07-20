/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** send
*/

#include "../../../include/my.h"

int send_message(server_s *server, char *uuid, char **tab)
{
    char *msg = remove_char_quote(tab[2]);
    char *uuid_sender = server->current->uuid;
    int sock = server->current->socket;
    client_info *current = server->client_head;

    while (current != NULL) {
        if (strcmp(current->uuid, uuid) == 0) {
            write_db(current->uuid, tab[2], uuid_sender);
            server_event_private_message_sended(uuid_sender, uuid, msg);
            dprintf(current->socket, "251 %s %s\n\r",
                uuid_sender, msg);
            return 0;
        }
        current = current->next;
    }
    return 1;
}

void write_db(char *uuid_receive, char *msg, char *uuid)
{
    FILE *file = fopen("database/messages.txt", "a");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *date = malloc(sizeof(char) * 100);

    date = strcpy(date, asctime(&tm));
    date[strlen(date) - 1] = '\0';
    if (file == NULL)
        return;
    fprintf(file, "%s::%s::%s::%s\n", uuid_receive, uuid, msg, date);
    fclose(file);
}

void send_main(server_s *server, char *buffer)
{
    char **tab = strtok_tab_spe(buffer, " \t\n\r", 0, 0);
    char *uuid;

    server->check = 1;
    if (server->current->is_logged == false) {
        dprintf(server->current->socket, "530\n");
        return;
    }
    if (tab[1] == NULL) {
        dprintf(server->current->socket, "550\n");
        return;
    }
    uuid = remove_char_quote(tab[1]);
    if (send_message(server, uuid, tab) == 1) {
        dprintf(server->current->socket, "550\n");
    }
}

void remove_quotes(char **cmd)
{
    for (int i = 1; cmd[i] != NULL; i++) {
        if (cmd[i][0] == '"' && cmd[i][strlen(cmd[i]) - 1] == '"') {
            cmd[i]++;
            cmd[i][strlen(cmd[i]) - 1] = '\0';
        }
    }
}