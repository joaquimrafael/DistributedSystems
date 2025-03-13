#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    int client_socket;
    struct sockaddr_in server_address;
    char server_response[256];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(client_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0)
    {
        printf("Connection failed\n");
        return 1;
    }

    recv(client_socket, &server_response, sizeof(server_response), 0);

    printf("Resposta do servidor: %s\n", server_response);

    close(client_socket);

    return 0;
}
