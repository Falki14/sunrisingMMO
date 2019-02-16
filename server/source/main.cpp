//#include <iostream>
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
#include "main.h"


/**
 * @author Falki
 * @param int argc
 * @param char argv
 **/
int main(int argc, char *argv[])
{
    /**
     * Create socket
     * */
    logHandler *log = new logHandler();
    socketHandler *socket = new socketHandler();
    log->infoMessageLog("Sunrising-Network Server starts now.");
    socket->createSocketServer();
    //createSocketServer();
}
