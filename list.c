#include "list.h"

int list_enqueue(ListType *l, SongType *s)
{
  NodeType *n = calloc(1, sizeof(NodeType));
  if (l == NULL || s == NULL){
    perror("list_add_to_end: null parameter");
    return EXIT_FAILURE;
  }

  if (l->head == NULL ^ l->tail == NULL){
    perror("list_add_to_end: inconsistent list, head or tail is null but not both!");
    return EXIT_FAILURE
  }

  if (l->head == NULL){
    /* new head */
    l->head = n;
    l->tail = n;
  }
  else {
    /* new tail */
    l->tail->next = n;
    l->tail = n;
  }
  return EXIT_SUCCESS;
}

int list_remove(ListType *l, char *song_name)
{
  NodeType *p, *p_prev = NULL;
  bool found = false;

  if (l == NULL || s == NULL){
    perror("list_remove: null parameter");
    return EXIT_FAILURE;
  }

  if (l->head == NULL || l->tail == NULL){
    perror("list_remove: cannot remove from empty list!");
    return EXIT_FAILURE
  }

  /* find the node */
  p = l->head;
  while(p != NULL){
    if (p->data == NULL){
      perror("list_remove: node has null data pointer!");
      return EXIT_FAILURE
    }
    if (strncmp(p->data->name,song_name)==0){
      found = true;
      break;
    }
    p_prev = p;
    p = p->next;
  }

  /* exit iff we did not find the node */
  if (!found){
    perror("list_remove: unable to match song name in list for input");
    return EXIT_FAILURE;
  }

  /* handle removing the head */
  if (p_prev == NULL){
   l->head = p->next; /* safe for p being end of list */
  }
  else {
    p_prev->next = p->next;
  }

  if (p == l->tail){
    l->tail = p_prev; /* safe for p being head of list */
  }

  free(p);
  return EXIT_SUCCESS;
}

int list_print(ListType *l)
{
  int i;
  NodeType *p;

  if (l == NULL){
    perror("list_remove: null parameter");
    return EXIT_FAILURE;
  }

  if (l->head == NULL || l->tail == NULL){
    printf("Empty list.\n");
    return EXIT_SUCCESS
  }

  printf("%-4s %-32s %-20s %-20s %-4s\n","[#]","Name","Artist","Album","Duration");
  printf("================================================================================\n");

  i=0;
  p = l->head;
  while(p != NULL){
    printf("[%02d] %-32s %-20s %-20s %-4s\n",++i,p->data->name,p->data->artist,p->data->album,p->data->duration);
    p = p->next;
  }

  return EXIT_SUCCESS;
}
