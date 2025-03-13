#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    char server_message[256] = "You have reached the server!";

    const char *response_body = "You have reached the server!";
    char http_header[256];

    /* snprintf(http_header, sizeof(http_header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/plain\r\n"
             "Content-Length: %ld\r\n"
             "\r\n%s",
             strlen(response_body), response_body);
             */

    int server_socket =socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket, 1);

    int client_socket = accept(server_socket, NULL, NULL);

    send(client_socket,server_message,sizeof(server_message),0);
    // send(client_socket,http_header,strlen(http_header),0);

    printf("Response sent and server closed\n");
    close(client_socket);
    return 0;
}
