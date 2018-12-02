#include <time.h>
#include <stdio.h>
#include <string.h>
#include "logHandler.h"

time_t t;
struct tm * ts;

/**
 * print error message
 * @author Falki
 * @param char message
 * */
int errorMessageLog(const char *message)
{
    t = time(NULL);
    ts = localtime(&t);
    printf("[%d-%d-%d %d:%d:%d] ERROR: %s \n",
     ts->tm_year+1900,
     ts->tm_mon+1,
     ts->tm_mday,
     ts->tm_hour,
     ts->tm_min,
     ts->tm_sec
     ,message);
     return 0;
}

/**
 * print info message
 * @author Falki
 * @param char message
 * */
int infoMessageLog(const char *message)
{
    t = time(NULL);
    ts = localtime(&t);
    printf("[%d-%d-%d %d:%d:%d] INFO: %s \n",
     ts->tm_year+1900,
     ts->tm_mon+1,
     ts->tm_mday,
     ts->tm_hour,
     ts->tm_min,
     ts->tm_sec
     ,message);
     return 0;
}