/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** client
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <uuid/uuid.h>
#include <sys/time.h>
#include "./utils.h"
#include "../libs/myteams/logging_client.h"
#include "./my.h"

#ifndef CLIENT_H_
    #define CLIENT_H_

typedef struct client_s {
    int sockFd;
    char *line;
    char **cmd;
    char *uuid;
    char *username;
} client_s;

void myteams_cli(char *ip, int port);
void loop_client(client_s *client);
void get_command(client_s *client);
void usage_client(void);
void get_command(client_s *client);
void call_function(client_s *client);
void free_tab(char **tab);
void fill_buffer(char *buffer, client_s *client);
int error_function(client_s *client);
int basic_function(client_s *client);
void set_fd(client_s *client, fd_set *current_sock);
time_t get_date(client_s *client, int i);
char *login_client(client_s *client, char *buffer);
void check_client(client_s *client);
void create_client(client_s *client);
void send_msg(client_s *client, char *line);
void generate_client(client_s *client);
void get_uuid(client_s *client, FILE *file);
void get_username(client_s *client);
int send_function(client_s *client, char *msg, int i, time_t t);
int user_function(client_s *client, int i);
int team_function(client_s *client);
int error_team(client_s *client);
int channel(client_s *client);
char *take_description(char **tab, int i);
char **strtok_tab_spe(char *str, char *tok, int i, int in_quotes);
int thread_reply(client_s *client, time_t t);


#endif /* !CLIENT_H_ */
