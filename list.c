#include "list.h"
void list_init(ListType *l)
{
  memset(l,0,sizeof(ListType));
}

int list_enqueue(ListType *l, SongType *s)
{
  NodeType *n = calloc(1, sizeof(NodeType));
  n->data=s;
  if (l == NULL || s == NULL){
    perror("list_enqueue: null parameter");
    return EXIT_FAILURE;
  }

  if ((l->head == NULL) ^ (l->tail == NULL)){
    perror("list_enqueue: inconsistent list, head or tail is null but not both!");
    return EXIT_FAILURE;
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

/*
 * int list_remove(ListType *l, char *song_name)
 * {
 *   NodeType *p, *p_prev = NULL;
 *   bool found = false;
 * 
 *   if (l == NULL || song_name == NULL){
 *     perror("list_remove: null parameter");
 *     return EXIT_FAILURE;
 *   }
 * 
 *   if (l->head == NULL || l->tail == NULL){
 *     perror("list_remove: cannot remove from empty list!");
 *     return EXIT_FAILURE;
 *   }
 * 
 *   [> find the node <]
 *   p = l->head;
 *   while(p != NULL){
 *     if (p->data == NULL){
 *       perror("list_remove: node has null data pointer!");
 *       return EXIT_FAILURE;
 *     }
 *     if (strcasecmp(p->data->name,song_name)==0){
 *       found = true;
 *       break;
 *     }
 *     p_prev = p;
 *     p = p->next;
 *   }
 * 
 *   [> exit iff we did not find the node <]
 *   if (!found){
 *     perror("list_remove: unable to match song name in list for input");
 *     return EXIT_FAILURE;
 *   }
 * 
 *   [> handle removing the head <]
 *   if (p_prev == NULL){
 *    l->head = p->next; [> safe for p being end of list <]
 *   }
 *   else {
 *     p_prev->next = p->next;
 *   }
 * 
 *   if (p == l->tail){
 *     l->tail = p_prev; [> safe for p being head of list <]
 *   }
 * 
 *   free(p);
 *   return EXIT_SUCCESS;
 * }
 */

char* list_view(ListType *l)
{
  int i;
  char tmp[MAX_BUFF];
  char *buf = calloc(1,MAX_BUFF*MAX_BUFF);
  NodeType *p;

  if (l == NULL){
    perror("list_view: null parameter");
    sprintf(buf,"ERROR from list_view()\n");
    return buf;
  }

  if (l->head == NULL){
    sprintf(buf,"Empty list.\n");
    return buf;
  }

  sprintf(tmp,"%-4s %-32s %-20s %-20s %-4s\n","No.","Name","Artist","Album","Duration");
  strcpy(buf,tmp);
  /* sprintf(tmp,"================================================================================\n"); */
  /* buf=strcat(buf,tmp); */

  i=0;
  p = l->head;
  while(p != NULL){
    sprintf(tmp,"[%02d] %-32s %-20s %-20s %04d\n",++i,p->data->name,p->data->artist,p->data->album,p->data->duration);
    strcat(buf,tmp);
    p = p->next;
  }
  strcat(buf,"\0");

  return buf;
}

bool list_walk(NodeType **pivot){
  if((*pivot)->next == NULL){
    return false;
  }
  *pivot = (*pivot)->next;
  return true;
}

bool list_delete(ListType *l, NodeType *prev, NodeType *target){
  if(l->head == NULL){
    // head of the list is null
    assert(l->tail == NULL);
    return false;
  }

  if (l->head == target){
    // here we are changing the head
    l->head = target->next; // works even if pivot->next == 0
  }
  if(l->tail == target){
    // here we are chaning the tail
    l->tail = prev; // works even if prev == 0
  }
  if(prev != NULL){
    prev->next = target->next;
  }

  free(target->data);
  free(target);
  return true;
}
