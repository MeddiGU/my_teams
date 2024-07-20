/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** utils
*/

#include "my.h"

#ifndef UTILS_H_
    #define UTILS_H_


char **strtok_tab(char *str, char *tok);
char **my_str_to_word_array(char *str, char separator);
int my_strcmp(char *s1, char *s2);

char *my_itoa(int nb);
char *my_revstr(char *str);


char *my_strcat(char *dest, char *src);
char *my_strdup(char *str);
char *my_strcpy(char *dest, char *src);
int my_strlen(char *str);


#endif /* !UTILS_H_ */
