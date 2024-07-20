/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-meddi.gueran
** File description:
** utils
*/

#include "../../include/utils.h"

char *my_revstr(char *str)
{
    int i = 0;
    int j = strlen(str) - 1;
    char tmp;

    while (i < j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
    return str;
}

char *replace_char(char *str, char c, char c2)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            str[i] = c2;
    }
    return str;
}

int my_strcmp(char *str, char *str2)
{
    if (str == NULL)
        return 0;
    for (int i = 0; str2[i] != '\0'; i++) {
        if (str[i] != str2[i])
            return 0;
    }
    return 1;
}

void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        free(tab[i]);
    }
    free(tab);
}

char *remove_char_quote(char *str)
{
    char *new_str = malloc(sizeof(char) * 4096);
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '"') {
            new_str[j] = str[i];
            j++;
        }
    }
    new_str[j] = '\0';
    return new_str;
}