/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-meddi.gueran
** File description:
** my
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
#include <linux/limits.h>
#include "../libs/myteams/logging_server.h"



#ifndef MY_H
    #define MY_H

typedef struct sockaddr_in sockaddr_in;

typedef struct client_info {
    int socket;
    char *username;
    bool is_logged;
    int connected;
    char *uuid;
    int port;
    bool is_in_team;
    bool is_in_channel;
    bool is_in_thread;
    char *current_channel;
    char *current_thread;
    char *current_team;
    struct sockaddr_in client_addr;
    struct sockaddr_in address;
    struct client_info *next;
} client_info;

typedef struct server_s {
    int port;
    int max_fds;
    int server_socket;
    char buffer[1024];
    size_t bytes_received;
    int client_socket;
    int check;
    int logout;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    client_info *client_head;
    client_info *current;
    fd_set read_fds;
    fd_set tmp_fds;
} server_s;

// Main
int usage_server(void);
void usage_client(void);

// Loop
int loop(server_s *serv);

// Server
void init_serv(server_s *serv);
void init_fd(server_s *serv);
void error_socket(server_s *server);
void sameport(server_s *server);
void load_client(server_s *server);


// Useful
char **my_str_to_word_array(char *str, char separator);
int my_strcmp(char *str, char *str2);
char **strtok_tab(char *str, char *tok);
char *my_itoa(int nb);
char *my_revstr(char *str);
char *replace_char(char *str, char c, char c2);
char *take_all_messages(char **tab);
void remove_quotes(char **cmd);
char *take_description(char **tab, int i);
char *remove_char_quote(char *str);
char **strtok_tab_spe(char *str, char *tok, int i, int in_quotes);
void check_quote(char *token, int *in_quotes);



// Client
void add_client_queue(server_s *server);
void read_data(server_s *server);
void handle_client(server_s *server);
void read_command(server_s *server);
client_info *add_client(client_info *client_head, int client_socket,
    sockaddr_in client_addr, server_s *server);
void myteams_cli(char *ip, int port);



// List Chaînée
void print_list(client_info *head);
void deletenodeatposition(server_s *server);

// Commandes
void do_command(server_s *server, char *buffer);
int basic_command(server_s *server, char *buffer);
void help(server_s *server);
void logout(server_s *server, char *buffer);
void send_logout(server_s *server);
void send_to_all_user(server_s *server);
int team_command(server_s *server, char *buffer);


// Login Command
void login(server_s *server, char *buffer);
int check_existing_user(server_s *server, char *uuid);
void create_user(server_s *server, char **tab);

// Messages Command
void messages(server_s *server, char *buffer);
bool check_existing_id(server_s *server, char *uuid_user);
void find_message(server_s *server, char *uuid_user);

// Send Command
int send_message(server_s *server, char *uuid, char **tab);
void send_main(server_s *server, char *buffer);
void write_db(char *uuid_receive, char *msg, char *uuid);
void send_find_message(server_s *server, char *uuid_user, char **tab);

// User Command
void user(server_s *server, char *buffer);
int read_user_info(server_s *server, char *uuid);
int find_user(server_s *server, char **tab, int tmpsock, char *uuid);


// Users Command
void users(server_s *server, char *buffer);
void list_user(server_s *server);
void user_exist(server_s *server, char **tab, int tmpsock);

// Create Command
void create(server_s *server, char *buffer);
void create_thread_reply(server_s *server, char **tab);

// Team Command
void write_team_db(char *team_name, char *team_desc, char *team_uuid);
void create_team(server_s *server, char **tab);
int check_file(char *path, char *team_name, DIR *dir);

// Sub Command
int find_team(char *path, char *team_uuid, DIR *dir, server_s *sever);
int subscribe_to_team(server_s *server, char *team_uuid);
void subscribe(server_s *server, char *buffer);
void write_user_subscribed(server_s *server, char *path);
void send_user(server_s *server, char **tab, char *uuid);

// Subscribed Command
void user_team(server_s *server, char *line);
int find_user_team(char *path, char **tab, DIR *dir, server_s *server);
int find_file(server_s *sever, char **tab);
void subscribed(server_s *server, char *buffer);
void user_not_logged(server_s *server, char **tab2);
void user_logged(server_s *server, char **tab);

// Unsub Command
void unsubscribe(server_s *server, char *buffer);
int check_team(server_s *server, char *team_uuid);
int find_team_to_unsub(char *path, char *team_uuid, server_s *server);
void clear_and_send(char *path, server_s *server, char *team_uuid);
void close_file(FILE *file, FILE *tmp);
int verif_namefile(char *path, char *uuid);

// Use Command
void use(server_s *server, char *buffer);
int use_command(server_s *server, char *buffer);
void use_reply(server_s *server, char **tab);

// Channel Command
void write_channel_db(char *team_name, char *team_desc, char *team_uuid);
void create_channel(server_s *server, char **tab);
int check_file(char *path, char *team_name, DIR *dir);

// Thread Command
void write_thread_db(char *team_name, char *team_desc, char *team_uuid);
void create_thread(server_s *server, char **tab);

// Reply Command
void create_reply(server_s *server, char **tab);
void write_reply_db(char *reply_desc, server_s *server);
void reply_all(server_s *server, char *reply_desc);


#endif /* !MY_H_ */