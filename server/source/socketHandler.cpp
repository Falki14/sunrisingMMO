#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "socketHandler.h"
#include "logHandler.h"

/**
* declaration
**/
int socket_desc, client_sock, c , read_size, *new_sock;
struct sockaddr_in server, client;

//the thread function
void *connection_handler(void *);

/**
 * create socket connection
 * @author Falki
 * */
int socketHandler::createSocketServer()
{
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_desc == -1)
    {
        printf("Could not create socket!");
        return 1;
    }

	logHandler *log = new logHandler();

    //puts("Socket");
    log->infoMessageLog("Socket was created");
    server.sin_family       = AF_INET;
    server.sin_addr.s_addr  = INADDR_ANY;
    server.sin_port         = htons(8888);

    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        log->errorMessageLog("Bind Faild!");
        return 1;
    }
    
    //puts("bind done");
    log->infoMessageLog("Server bind to address");

    listen(socket_desc, 3);
    log->infoMessageLog("SERVER is now live");
    puts("Waiting for incoming connections.....");
    c = sizeof(struct sockaddr_in);

   while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
   {
		puts("Connection accepted");
		
		pthread_t sniffer_thread;
        //int i;
		//new_sock = (char*) malloc (i+1);;
        //new_sock = malloc(1);
		//*new_sock = client_sock;
        new_sock= (int *) malloc(client_sock +1);
		*new_sock = client_sock;
		
		if( pthread_create( &sniffer_thread , NULL , connection_handler , (void*) new_sock) < 0)
		{
			perror("could not create thread");
			return 1;
		}
		
		//Now join the thread , so that we dont terminate before the thread
		//pthread_join( sniffer_thread , NULL);
		puts("Handler assigned");
	}
    
    if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}

    return 0;
}  

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
	logHandler *log = new logHandler();
	//Get the socket descriptor
	int sock = *(int*)socket_desc;
	int read_size;
	char client_message[2000];
	char const *message;
	//Send some messages to the client
	message = "Greetings! I am your connection handler\n";
	write(sock , message , strlen(message));
	
	message = "Now type something and i shall repeat what you type \n";
	write(sock , message , strlen(message));
	
	//Receive a message from client
	while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
	{
		//Send the message back to client
		write(sock , client_message , strlen(client_message));
        log->infoMessageLog(client_message);
	}
	
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
		
	//Free the socket pointer
	free(socket_desc);
	
	return 0;
}