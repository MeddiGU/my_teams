/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** unsubscribe
*/

#include "../../../include/my.h"

void unsubscribe(server_s *server, char *buffer)
{
    char **tab = strtok_tab(buffer, " \t\n\r");

    remove_quotes(tab);
    if (tab[1] == NULL) {
        dprintf(server->current->socket, "550\n\r");
    }
    check_team(server, tab[1]);
}

int check_team(server_s *server, char *team_uuid)
{
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];
    int value = 0;

    dir = opendir("database/team");
    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du dossier");
        return 1;
    }
    while (1) {
        entry = readdir(dir);
        if (entry == NULL)
            break;
        if (entry->d_type == DT_REG) {
            snprintf(path, sizeof(path), "database/team/%s", entry->d_name);
            value = find_team_to_unsub(path, team_uuid, server);
        }
    }
    return value;
}

int find_team_to_unsub(char *path, char *team_uuid, server_s *server)
{
    FILE *file;
    FILE *tmp;
    char line[4096];
    char **tab = NULL;

    if (verif_namefile(path, team_uuid) == 1);
        return 1;
    file = fopen(path, "r");
    tmp = fopen("database/team/tmp.txt", "w");
    while (fgets(line, sizeof(line), file) != NULL) {
        tab = strtok_tab(line, "\n");
        if (strcmp(server->current->uuid, tab[0]) == 0 ||
            strncmp(tab[0], server->current->username, strlen(tab[0])) == 0)
            continue;
        fputs(line, tmp);
    }
    fprintf(tmp, "\n");
    close_file(file, tmp);
    clear_and_send(path, server, team_uuid);
    return 0;
}

int verif_namefile(char *path, char *uuid)
{
    char *verif = malloc(sizeof(char) * 100);

    strcpy(verif, "database/team/");
    strcat(verif, uuid);
    strcat(verif, ".txt");
    if (strcmp(path, verif) != 0)
        return 1;
    return 0;
}

void clear_and_send(char *path, server_s *server, char *team_uuid)
{
    remove(path);
    rename("database/team/tmp.txt", path);
    dprintf(server->current->socket, "262 %s %s\n\r",
        server->current->uuid, team_uuid);
    server_event_user_unsubscribed(team_uuid, server->current->uuid);
}