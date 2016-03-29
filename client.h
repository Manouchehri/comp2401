#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 60003

#define MENU_TEXT "(A)dd song\t(D)elete song\t(V)iew songs\t(Q)uit\n"

#include "defs.h"

int  mySocket;

void initClientSocket(void);
void printMenu(void);
