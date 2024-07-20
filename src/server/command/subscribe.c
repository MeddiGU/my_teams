/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** subscribe
*/

#include "../../../include/my.h"

void subscribe(server_s *server, char *buffer)
{
    char **tab = strtok_tab(buffer, " \t\n\r");

    remove_quotes(tab);
    server->check = 1;
    if (tab[1] == NULL) {
        dprintf(server->current->socket, "500\n\r");
        return;
    }
    subscribe_to_team(server, tab[1]);
}

int subscribe_to_team(server_s *server, char *team_uuid)
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
            value = find_team(path, team_uuid, dir, server);
        }
    }
    return value;
}

int find_team(char *path, char *team_uuid, DIR *dir, server_s *server)
{
    FILE *file;
    char line[4096];
    char **tab;

    file = fopen(path, "r+");
    if (file == NULL)
        return 1;
    while (fgets(line, sizeof(line), file)) {
        tab = strtok_tab(line, "::");
        if (tab[2] == NULL)
            break;
        if (strstr(tab[2], team_uuid) != NULL) {
            send_user(server, tab, team_uuid);
            write_user_subscribed(server, path);
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

void write_user_subscribed(server_s *server, char *path)
{
    FILE *file;
    char line[4096];
    char **tab;

    file = fopen(path, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    while (fgets(line, sizeof(line), file)) {
        tab = strtok_tab(line, "\n");
        if (strcmp(tab[0], server->current->uuid) == 0) {
            fclose(file);
            return;
        }
    }
    fprintf(file, "%s\n%s",
        server->current->uuid, server->current->username);
    fclose(file);
}

void user_logged(server_s *server, char **tab)
{
    client_info *current = server->client_head;

    for (; current != NULL; current = current->next) {
        if (strcmp(current->uuid, tab[0]) == 0 && current->is_logged == true) {
            dprintf(server->current->socket, "232 %s %s %d\n\r",
                current->uuid, current->username, 1);
                return;
        }
    }
}