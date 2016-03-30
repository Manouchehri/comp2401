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

int  global_socket;

/* client.c */
void sig_handler(int signum, siginfo_t *info, void *ptr);
void controller_add(void);
void controller_delete(void);
void controller_view(void);
void controller_quit(void);
void view_menu(void);
void init_client_socket(void);
