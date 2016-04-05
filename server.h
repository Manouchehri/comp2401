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

extern int global_listen_socket, global_socket;

/* server.c */
void init_server_socket(void);
void wait_for_connection(void);
void server_add(ListType *l);
void server_delete(ListType *l);
void server_view(ListType *l);
void server_quit(void);
