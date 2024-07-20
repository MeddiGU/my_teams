/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** subscribed
*/

#include "../../../include/my.h"

void subscribed(server_s *server, char *buffer)
{
    char **tab = strtok_tab(buffer, " \t\n\r");

    remove_quotes(tab);
    server->check = 1;
    if (tab[1] == NULL) {
        dprintf(server->current->socket, "500\n\r");
        return;
    }
    find_file(server, tab);
}

int find_file(server_s *sever, char **tab)
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
            value = find_user_team(path, tab, dir, sever);
        }
    }
    return value;
}

int find_user_team(char *path, char **tab, DIR *dir, server_s *server)
{
    FILE *file;
    char line[4096];
    char **tab2;

    file = fopen(path, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    while (fgets(line, sizeof(line), file)) {
        tab2 = strtok_tab(line, "::");
        if (strstr(tab2[2], tab[1]) != NULL) {
            user_team(server, path);
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void user_team(server_s *server, char *path)
{
    FILE *file;
    char line[4096];
    char **tab;

    file = fopen(path, "r+");
    while (fgets(line, sizeof(line), file)) {
        tab = strtok_tab(line, "::\n");
        if (strcmp(tab[0], server->current->uuid) == 0) {
            user_logged(server, tab);
        } else {
            user_not_logged(server, tab);
        }
    }
    fclose(file);
}

void user_not_logged(server_s *server, char **tab2)
{
    FILE *file;
    char line[4096];
    char **tab;

    file = fopen("database/user.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    while (fgets(line, sizeof(line), file)) {
        tab = strtok_tab(line, ":");
        if (strcmp(tab[0], tab2[0]) == 0) {
            dprintf(server->current->socket, "232 %s %s %d\n\r",
                tab[0], tab[1], 0);
        }
    }
    fclose(file);
}