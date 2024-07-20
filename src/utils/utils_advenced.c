/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** utils_advenced
*/

#include "../../include/utils.h"

char **strtok_tab(char *str, char *tok)
{
    char *tmp = strtok(str, tok);
    char **tab = malloc(sizeof(char *) * 4096);
    int i = 0;

    for (; tmp != NULL; i++) {
        tab[i] = strdup(tmp);
        tab[i][strlen(tmp)] = '\0';
        tmp = strtok(NULL, tok);
    }
    tab[i] = NULL;
    return tab;
}

char **my_str_to_word_array(char *str, char separator)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char **tab = malloc(sizeof(char *) * (strlen(str) + 1));

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == separator) {
            tab[j] = malloc(sizeof(char) * (i - k + 1));
            tab[j] = strncpy(tab[j], &str[k], i - k);
            k = i + 1;
            j++;
        }
    }
    tab[j] = malloc(sizeof(char) * (i - k + 1));
    tab[j] = strncpy(tab[j], &str[k], i - k);
    tab[j + 1] = NULL;
    return tab;
}

char *my_itoa(int nb)
{
    char *str = malloc(sizeof(char) * 4096);
    int i = 0;

    for (; nb > 0; i++) {
        str[i] = (nb % 10) + 48;
        nb = nb / 10;
    }
    str[i] = '\0';
    return my_revstr(str);
}

char *take_all_messages(char **tab)
{
    int i = 2;
    int size = 0;
    char *msg;

    for (int j = 2; tab[j] != NULL; j++)
        size += strlen(tab[j]) + 1;
    msg = malloc(sizeof(char) * (size));
    msg[0] = '\0';
    while (tab[i] != NULL) {
        strcat(msg, tab[i]);
        if (tab[i + 1] != NULL)
            strcat(msg, " \0");
        i++;
    }
    msg = remove_char_quote(msg);
    return msg;
}

char *take_description(char **tab, int i)
{
    int size = 0;
    char *desc;

    for (int j = i; tab[j] != NULL; j++)
        size += strlen(tab[j]) + 1;
    desc = malloc(sizeof(char) * (size));
    desc[0] = '\0';
    while (tab[i] != NULL) {
        strcat(desc, tab[i]);
        if (tab[i + 1] != NULL)
            strcat(desc, " \0");
        i++;
    }
    desc = remove_char_quote(desc);
    return desc;
}