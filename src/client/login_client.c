/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** login_client
*/

#include "../../include/client.h"

char *login_client(client_s *client, char *buffer)
{
    if (strncmp(buffer, "/login", 6) == 0) {
        client->cmd = strtok_tab(buffer, "  \t\n\r");
        if (client->cmd[1] == NULL || client->cmd[1][0] != '"'
            && client->cmd[1][strlen(client->cmd[1]) - 1] != '"') {
            return buffer;
        } else {
            get_username(client);
            client->username = strdup(client->cmd[1]);
            check_client(client);
            strcat(buffer, " ");
            strcat(buffer, client->uuid);
            strcat(buffer, " ");
            strcat(buffer, client->username);
        }
    }
    return buffer;
}

void check_client(client_s *client)
{
    FILE *file = fopen("database/client/client_user.txt", "r");

    if (file != NULL) {
        get_uuid(client, file);
        return;
    } else {
        generate_client(client);
        return;
    }
}

void create_client(client_s *client)
{
    uuid_t new_uuid_bin;
    char new_uuid[37];
    FILE *file = fopen("database/client/client_user.txt", "a");

    if (file == NULL) {
        printf("Error file.\n");
        return;
    }
    uuid_generate(new_uuid_bin);
    uuid_unparse(new_uuid_bin, new_uuid);
    fprintf(file, "%s:%s\n", new_uuid, client->cmd[1]);
    client->uuid = strdup(new_uuid);
    fclose(file);
}

void generate_client(client_s *client)
{
    char new_uuid[37];
    uuid_t new_uuid_bin;
    FILE *file;

    uuid_generate(new_uuid_bin);
    uuid_unparse(new_uuid_bin, new_uuid);
    client->uuid = strdup(new_uuid);
    file = fopen("database/client/client_user.txt", "w");
    if (file == NULL) {
        printf("Error file.\n");
        return;
    }
    fprintf(file, "%s:%s\n", client->uuid, client->cmd[1]);
    fclose(file);
}

void get_uuid(client_s *client, FILE *file)
{
    char buffer[4096];
    char **tab = NULL;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        tab = strtok_tab(buffer, ":");
        if (strncmp(client->cmd[1], tab[1], strlen(client->cmd[1])) == 0) {
            client->uuid = strdup(tab[0]);
            return;
        }
    }
    fclose(file);
    if (client->uuid == NULL) {
        create_client(client);
    }
}