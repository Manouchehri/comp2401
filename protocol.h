#pragma once

#define PROTO_ADD    "ADD"
#define PROTO_DELETE "DEL"
#define PROTO_VIEW   "VIW"
#define PROTO_QUIT   "QIT"
#define PROTO_REPLY  "RPY"

#define PROTO_PARAMETER "|"
#define PROTO_END_PARAMETERS ";"

#define PROTO_VALID_USER_INPUT_CHARS "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM-_1234567890 '"
#define PROTO_VALID_USER_INPUT_CHARS_FOR_INTEGER "1234567890"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "defs.h"

extern int global_socket;

/* protocol.c */
void socket_send_param(const char *prompt, const char *accept);
void socket_send(const char *str);
void socket_read(char *text);
