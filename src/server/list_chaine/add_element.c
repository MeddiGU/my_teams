/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-meddi.gueran
** File description:
** init_server
*/

#include "../../../include/my.h"

void print_list(client_info *head)
{
    int i = 1;

    while (head != NULL) {
        printf("Client %d: %s:%d\n", i, inet_ntoa(head->client_addr.sin_addr),
            ntohs(head->client_addr.sin_port));
        head = head->next;
        i++;
    }
}

void deletenodeatposition(server_s *server)
{
    client_info *temp;

    if (server->client_head == server->current) {
        server->client_head = server->client_head->next;
        server->current = server->client_head;
    } else {
        temp = server->client_head;
        while (temp->next != server->current) {
            temp = temp->next;
        }
        temp->next = server->current->next;
        server->current = temp->next;
    }
}

client_info *add_client(client_info *client_head, int client_socket,
    sockaddr_in client_addr, server_s *server)
{
    client_info *new_client = malloc(sizeof(client_info));

    if (new_client == NULL) {
        perror("Failed to allocate memory for new client");
        exit(84);
    }
    new_client->socket = client_socket;
    new_client->client_addr = client_addr;
    new_client->next = client_head;
    new_client->uuid = NULL;
    new_client->connected = 0;
    new_client->is_logged = false;
    new_client->is_in_channel = false;
    new_client->is_in_team = false;
    new_client->is_in_thread = false;
    new_client->current_channel = NULL;
    new_client->current_thread = NULL;
    new_client->port = 0;
    new_client->current_team = NULL;
    return new_client;
}
