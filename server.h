#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MY_PORT 60003

#include "list.h"
#include "defs.h"
#include "protocol.h"
#include "ainsi.h"

/* server.c */
void initServerSocket(void);
void waitForConnection(void);
void recvText(char *text);
