/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** client_command
*/

#include "../../include/client.h"

void get_command(client_s *client)
{
    char *buffer = malloc(sizeof(char) * 1024);

    fill_buffer(buffer, client);
    if (buffer[0] == '\0')
        return;
    if (strncmp("260", buffer, 3) == 0 || strncmp("263", buffer, 3) == 0
        || strncmp("264", buffer, 3) == 0 || strncmp("250", buffer, 3) == 0 ||
        strncmp("265", buffer, 3) == 0) {
        client->cmd = strtok_tab_spe(buffer, " \t\n\r", 0, 0);
    } else {
        client->cmd = strtok_tab(buffer, "  \t\n\r");
    }
    call_function(client);
    free(buffer);
}

void call_function(client_s *client)
{
    int i = 0;
    time_t t;
    char *msg = malloc(sizeof(char) * 1024);

    if (basic_function(client) == 1)
        return;
    if (error_function(client) == 1)
        return;
    if (send_function(client, msg, i, t) == 1)
        return;
    if (user_function(client, i) == 1)
        return;
    if (team_function(client) == 1)
        return;
    if (error_team(client) == 1)
        return;
    if (channel(client) == 1)
        return;
}

int basic_function(client_s *client)
{
    int i = 0;

    if (strncmp(client->cmd[0], "230", 3) == 0) {
        client_event_logged_in(client->cmd[1], client->cmd[2]);
        return 1;
    }
    if (strncmp(client->cmd[0], "231", 3) == 0) {
        client_event_logged_out(client->cmd[1], client->cmd[2]);
        close(client->sockFd);
        return 1;
    }
    if (strncmp(client->cmd[0], "234", 3) == 0) {
        client_event_logged_out(client->cmd[1], client->cmd[2]);
        return 1;
    }
    if (strncmp(client->cmd[0], "214", 3) == 0) {
        write(1, "Help:\n", 6);
        return 1;
    }
    return 0;
}

int error_function(client_s *client)
{
    if (strncmp(client->cmd[0], "530", 3) == 0) {
        write(1, "Please login.\n", 15);
        return 1;
    }
    if (strncmp(client->cmd[0], "550", 3) == 0) {
        write(1, "Unknown command.\n", 17);
        return 1;
    }
    if (strncmp(client->cmd[0], "531", 3) == 0) {
        write(1, "Invalid command.\n", 17);
        return 1;
    }
    if (strncmp(client->cmd[0], "532", 3) == 0) {
        write(1, "Error file.\n", 12);
        return 1;
    }
    return 0;
}

void fill_buffer(char *buffer, client_s *tmp)
{
    char c;
    int i = 0;

    for (i; read(tmp->sockFd, &c, 1) > 0; i++){
        buffer[i] = c;
        if (c == '\r')
            break;
    }
    buffer[i] = '\0';
}
