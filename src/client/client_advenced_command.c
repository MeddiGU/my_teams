/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** client_advenced_command
*/

#include "../../include/client.h"

int send_function(client_s *client, char *msg, int i, time_t t)
{
    if (strncmp(client->cmd[0], "250", 3) == 0) {
        while (client->cmd[i] != NULL) {
            msg = remove_char_quote(client->cmd[i + 2]);
            t = get_date(client, i);
            client_private_message_print_messages(client->cmd[i + 1],
                t, msg);
            i += 7;
        }
        return 1;
    }
    if (strncmp(client->cmd[0], "251", 3) == 0) {
        msg = take_all_messages(client->cmd);
        client_event_private_message_received(client->cmd[1], msg);
        return 1;
    }
    return 0;
}

int user_function(client_s *client, int i)
{
    if (strncmp(client->cmd[0], "232", 3) == 0) {
        i = 1;
        while (client->cmd[i] != NULL) {
            client_print_users(client->cmd[i], client->cmd[i + 1],
                atoi(client->cmd[i + 2]));
            i += 3;
        }
        return 1;
    }
    if (strncmp(client->cmd[0], "233", 3) == 0) {
        client_print_users(client->cmd[1], client->cmd[2],
            atoi(client->cmd[3]));
        return 1;
    }
    return 0;
}

int team_function(client_s *client)
{
    char *name;
    char *desc;

    if (strncmp(client->cmd[0], "260", 3) == 0) {
        name = remove_char_quote(client->cmd[2]);
        desc = remove_char_quote(client->cmd[3]);
        client_print_team_created(client->cmd[1], name, desc);
        client_print_team(client->cmd[1], name, desc);
        client_event_team_created(client->cmd[1], name, desc);
        return 1;
    }
    if (strncmp(client->cmd[0], "261", 3) == 0) {
        client_print_subscribed(client->cmd[1], client->cmd[2]);
        return 1;
    }
    if (strncmp(client->cmd[0], "262", 3) == 0) {
        client_print_unsubscribed(client->cmd[1], client->cmd[2]);
        return 1;
    }
    return 0;
}

int error_team(client_s *client)
{
    if (strncmp(client->cmd[0], "600", 3) == 0) {
        client_error_already_exist();
        return 1;
    }
    if (strncmp(client->cmd[0], "601", 3) == 0) {
        client_error_unknown_team(client->cmd[1]);
        return 1;
    }
    if (strncmp(client->cmd[0], "500", 3) == 0) {
        write(1, "", 1);
        return 1;
    }
    return 0;
}

int channel(client_s *client)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *name;
    char *desc;

    if (strncmp(client->cmd[0], "263", 3) == 0) {
        name = remove_char_quote(client->cmd[2]);
        desc = remove_char_quote(client->cmd[3]);
        client_print_channel_created(client->cmd[1], name, desc);
        client_team_print_channels(client->cmd[1], name, desc);
        return 1;
    }
    if (thread_reply(client, t) == 1)
        return 1;
    return 0;
}
