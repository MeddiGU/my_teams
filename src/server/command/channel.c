/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** team
*/

#include "../../../include/my.h"

void create_channel(server_s *server, char **tab)
{
    char *channel_name = remove_char_quote(tab[1]);
    char *channel_desc = remove_char_quote(tab[2]);
    uuid_t new_uuid_bin;
    char channel_uuid[37];

    uuid_generate(new_uuid_bin);
    uuid_unparse(new_uuid_bin, channel_uuid);
    write_channel_db(channel_name, channel_desc, channel_uuid);
    server_event_channel_created(server->current->current_team,
        channel_uuid, channel_name);
    dprintf(server->current->socket, "263 %s %s %s\n\r",
        channel_uuid, tab[1], tab[2]);
}

void write_channel_db(char *team_name, char *team_desc, char *team_uuid)
{
    FILE *file;
    char *path = malloc(sizeof(char) * 100);

    strcpy(path, "database/channel/");
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
