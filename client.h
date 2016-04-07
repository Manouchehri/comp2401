#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 60003

#define MENU_TEXT "\nWhat shall we do now?\n[A]dd song\t[D]elete song\t[V]iew songs\t[Q]uit \n"

#include "ainsi.h"
#include "defs.h"
#include "protocol.h"

extern int  global_socket;

/* client.c */
void init_sighandler(void);
void sighandler(int signum, siginfo_t *info, void *ptr);
void client_add(void);
void client_delete(void);
void client_view(void);
void client_quit(void);
void view_menu(void);
void init_client_socket(void);
