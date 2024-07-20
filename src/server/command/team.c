/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** team
*/

#include "../../../include/my.h"

void create_team(server_s *server, char **tab)
{
    char *team_name = remove_char_quote(tab[1]);
    char *team_desc = remove_char_quote(tab[2]);
    uuid_t new_uuid_bin;
    char team_uuid[37];

    uuid_generate(new_uuid_bin);
    uuid_unparse(new_uuid_bin, team_uuid);
    write_team_db(team_name, team_desc, team_uuid);
    server_event_team_created(team_uuid, team_name, server->current->uuid);
    dprintf(server->current->socket, "260 %s %s %s\n\r",
        team_uuid, tab[1], tab[2]);
}

void write_team_db(char *team_name, char *team_desc, char *team_uuid)
{
    FILE *file;
    char *path = malloc(sizeof(char) * 100);

    strcpy(path, "database/team/");
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

int check_file(char *path, char *team_name, DIR *dir)
{
    char line[4096];
    char **tab = NULL;
    FILE *file = fopen(path, "r");

    while (fgets(line, sizeof(line), file) != NULL) {
        tab = strtok_tab(line, "::");
        if (strstr(tab[0], team_name) != NULL) {
            fclose(file);
            closedir(dir);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void close_file(FILE *file, FILE *tmp)
{
    fclose(file);
    fclose(tmp);
}