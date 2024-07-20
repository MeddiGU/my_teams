/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** handle_time
*/

#include "../../include/client.h"

time_t get_date(client_s *client, int i)
{
    struct tm tm;
    time_t t;
    char *date = malloc(sizeof(char) * 100);

    date = strcpy(date, client->cmd[i + 5]);
    date[strlen(date) - 1] = '\0';
    strptime(date, "%a %b %d %H:%M:%S %Y", &tm);
    t = mktime(&tm);
    return t;
}

void get_username(client_s *client)
{
    for (int i = 1; client->cmd[i] != NULL; i++) {
        if (client->cmd[i][0] == '"' &&
            client->cmd[i][strlen(client->cmd[i]) - 1] == '"') {
            client->cmd[i]++;
            client->cmd[i][strlen(client->cmd[i]) - 1] = '\0';
        }
    }
}

void check_quote(char *token, int *in_quotes)
{
    for (int j = 0; token[j] != '\0'; j++) {
        if (token[j] == '"')
            *in_quotes = !*in_quotes;
    }
}

char **strtok_tab_spe(char *str, char *tok, int i, int in_quotes)
{
    char **tab = malloc(sizeof(char *) * 4096);
    char *token = strtok(str, tok);
    size_t prev_len;

    while (token != NULL) {
        if (!in_quotes) {
            tab[i] = strdup(token);
            i++;
        } else {
            prev_len = strlen(tab[i - 1]);
            tab[i - 1] = realloc(tab[i - 1], prev_len + strlen(token) + 2);
            strcat(tab[i - 1], " ");
            strcat(tab[i - 1], token);
        }
        check_quote(token, &in_quotes);
        str = NULL;
        token = strtok(str, tok);
    }
    tab[i] = NULL;
    return tab;
}