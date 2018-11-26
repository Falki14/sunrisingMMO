/**
 * Test Client made by Falki
 * */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        printf("COULD NOT CREATE SOCKET!");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family      = AF_INET;
    server.sin_port        = htons(8888);

    // Connect to Server
    if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connection faild. Error");
        return 1;
    }

    puts("Connected\n");

    //communitcation
    while(1)
    {
        printf("Enter message: ");
        scanf("%s", message);

        // send data to server
        if(send(sock, message, strlen(message), 0) < 0)
        {
            puts("Send faild!");
            return 1;
        }

        if(recv(sock, server_reply, 2000, 0) < 0)
        {
            puts("recv faild");
            break;
        }

        puts("Server reply: ");
        puts(server_reply);
    }

    // close connection
    close(sock);
    // exit
    return 0;
}
