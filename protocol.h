#pragma once

#define PROTO_ADD    "ADD"
#define PROTO_DELETE "DEL"
#define PROTO_VIEW   "VIW"
#define PROTO_QUIT   "QIT"
#define PROTO_REPLY  "RPY"
#define PROTO_ERROR  "ERR"

#define PROTO_PARAMETER "|"
#define PROTO_END_PARAMETERS ";"

#define PROTO_VALID_USER_INPUT_CHARS_FOR_INTEGER "1234567890"
#define PROTO_VALID_USER_INPUT_CHARS "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM-_' " PROTO_VALID_USER_INPUT_CHARS_FOR_INTEGER
#define PROTO_VALID_REPLY_CHARS PROTO_VALID_USER_INPUT_CHARS "=[]#.{}"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

#include "defs.h"

extern int global_socket;


/* protocol.c */
void socket_read_reply(void);
void socket_send_raw_param(const char *str);
void socket_send_param(const char *prompt, const char *accept);
_Bool socket_read_param(char **param, const char *accept);
char *socket_read_raw_token(void);
void socket_send(const char *str);
void socket_read(char *text);
