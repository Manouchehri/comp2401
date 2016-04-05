#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <stdbool.h>
#include <assert.h>
#include "defs.h"

typedef struct Song {
  char name[MAX_STR];
  char artist[MAX_STR];
  char album[MAX_STR];
  int duration;
} SongType;

typedef struct Node {
  struct Node *next;
  SongType *data;
} NodeType;

typedef struct List {
  NodeType *head;
  NodeType *tail;
} ListType;

/* list.c */
void list_init(ListType *l);
int list_enqueue(ListType *l, SongType *s);
int list_remove(ListType *l, char *song_name);
int list_print(ListType *l);
