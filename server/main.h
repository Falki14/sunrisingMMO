#ifndef MAIN_H
#define MAIN_H

static int errorMessageLog(const char *message);
static int infoMessageLog(const char *message);
static int createSocketServer();
void *connection_handler(void *);

#endif