#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_IP "10.0.2.15"
#define SERVER_PORT 60003

#include "defs.h"

int  mySocket;
void initClientSocket();
