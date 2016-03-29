#pragma once
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <stdbool.h>
#include <assert.h>
#include "defs.h"

typedef struct SongType {
  char name[MAX_STR];
  char artist[MAX_STR];
  char album[MAX_STR];
  int duration;
} SongType;

typedef struct NodeType {
  struct Node *next;
  SongType *data;
} Node;

typedef struct ListType {
  Node *head;
  Node *tail;
} ListType;

/* ./list.c */
int list_enqueue(ListType *l, SongType *s);
int list_remove(ListType *l, char *song_name);
int list_print(ListType *l);
