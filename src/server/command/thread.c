/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** thread
*/

#include "../../../include/my.h"

void create_thread(server_s *server, char **tab)
{
    char *thread_name = remove_char_quote(tab[1]);
    char *thread_desc = remove_char_quote(tab[2]);
    uuid_t new_uuid_bin;
    char thread_uuid[37];

    uuid_generate(new_uuid_bin);
    uuid_unparse(new_uuid_bin, thread_uuid);
    write_channel_db(thread_name, thread_desc, thread_uuid);
    server_event_thread_created(server->current->current_channel, thread_uuid,
        server->current->uuid, thread_name, thread_desc);
    dprintf(server->current->socket, "264 %s %s %s %s\n\r",
        thread_uuid, server->current->uuid, tab[1], tab[2]);
}

void write_thread_db(char *team_name, char *team_desc, char *team_uuid)
{
    FILE *file;
    char *path = malloc(sizeof(char) * 100);

    strcpy(path, "database/thread/");
    strcat(path, team_uuid);
    strcat(path, ".txt");
    file = fopen(path, "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s::%s::%s\n", team_name, team_desc, team_uuid);
    fclose(file);
}
