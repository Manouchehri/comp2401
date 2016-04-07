#include  "server.h"

int global_listen_socket, global_socket;

int main()
{
  char buffer[MAX_BUFF];
  ListType list;
  list_init(&list);

  init_sighandler();

  init_server_socket();

  while (1) {
    /*  waiting for next client to connect  */
    wait_for_connection();
    /*  a client has connected  */

    /* read messages from client and do something with it  */
    while (1) {
      socket_read(buffer);
      printf("%s\n",buffer);
      if (strncmp(buffer, PROTO_QUIT,3) == 0) {
        server_quit();
        break;
      }
      else if (strncmp(buffer, PROTO_ADD,3)==0){
        server_add(&list);
      }
      else if (strncmp(buffer, PROTO_DELETE,3)==0){
        server_delete(&list);
      }
      else if (strncmp(buffer, PROTO_VIEW,3)==0){
        server_view(&list);
      }
      else if (strlen(buffer)>0) {
        printf("Received garbage: \"%s\"\n",buffer);
      }
    }
    /*  closing this client's connection  */
    close(global_socket);
  }

  /*  all done, no more clients will be connecting  */
  close(global_listen_socket);

  return EXIT_SUCCESS;
}

void init_sighandler()
{
  struct sigaction sigactint, sigactusr1;
  memset(&sigactint, 0, sizeof(struct sigaction));
  memset(&sigactusr1, 0, sizeof(struct sigaction));

  sigactusr1.sa_flags = sigactint.sa_flags = SA_SIGINFO | SA_NODEFER;

  sigactint.sa_sigaction = sighandlerint;
  sigemptyset(&sigactint.sa_mask);

  sigactusr1.sa_sigaction = sighandlerint;
  sigemptyset(&sigactusr1.sa_mask);
  sigaddset(&sigactusr1.sa_mask,SIGINT);
  sigaddset(&sigactusr1.sa_mask,SIGTERM);

  sigaction(SIGUSR1, &sigactusr1, NULL);
  sigaction(SIGINT, &sigactint, NULL);
  //TODO: why can i cant sigint
}
/**
 * Handler for SIGINT.
 */
void sighandlerint(int signum, siginfo_t *info, void *ptr)
{
  printf("Send SIGUSR1 to terminate me, master.\n");
}
/**
 * Handler for SIGUSR1.
 * Closes the socket and exits.
 */
void sighandlerusr1(int signum, siginfo_t *info, void *ptr)
{
  printf("SIGUSR1 received. Terminating.\n");
  if(global_socket != -1){
    socket_send(PROTO_QUIT);
    close(global_socket);
  }
  exit(EXIT_SUCCESS);
}

void init_server_socket()
{
  struct sockaddr_in myAddr;
  int i;

  /* create socket */
  global_listen_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (global_listen_socket < 0) {
    perror("couldn't open socket");
    exit(EXIT_FAILURE);
  }

  /* setup my server address */
  memset(&myAddr, 0, sizeof (myAddr) );
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myAddr.sin_port = htons( (unsigned short) MY_PORT);

  /* bind my listen socket */
  i = bind(global_listen_socket,
           (struct sockaddr *) &myAddr,
           sizeof (myAddr) );
  if (i < 0) {
    perror("couldn't bind socket");
    exit(EXIT_FAILURE);
  }

  /* listen */
  i = listen(global_listen_socket, 5);
  if (i < 0) {
    perror("couldn't listen");
    exit(EXIT_FAILURE);
  }
}

void wait_for_connection()
{
  struct sockaddr_in clientAddr;
  socklen_t addrSize;

  printf("waiting for connection... \n");

  /* wait for connection request */
  global_socket = accept(global_listen_socket,
                        (struct sockaddr *) &clientAddr,
                        &addrSize);
  if (global_socket < 0) {
    perror("couldn't accept the connection\n");
    exit(EXIT_FAILURE);
  }
  printf("got one! \n");
}

void server_add(ListType *l)
{
  SongType *s = calloc(1, sizeof(SongType));
  char *param;
  char *params[3]={s->name,s->artist,s->album};
  unsigned short i;

  for(i=0; i < 3; ++i) {
    if(!socket_read_param(&param,PROTO_VALID_USER_INPUT_CHARS)){
      printf("invalid param from client");
      socket_send(PROTO_ERROR);
      return;
    }
    strcpy(params[i],param);
  }

  if(!socket_read_param(&param,PROTO_VALID_USER_INPUT_CHARS_FOR_INTEGER)){
    printf("invalid param from client");
    socket_send(PROTO_ERROR);
    return;
  }
  s->duration=atoi(param);

  list_enqueue(l,s);
}

void server_delete(ListType *l)
{
  char buf[MAX_BUFF];
  char *param;
  NodeType *pivot, *prev=NULL;
  bool found = false;
  if(!socket_read_param(&param,PROTO_VALID_USER_INPUT_CHARS))
    return;

  pivot = l->head;
  if(pivot == NULL){
    printf("Empty list, nothing to delete.\n");
    socket_send(PROTO_ERROR);
    return;
  }

  do {
    if(strcasecmp(pivot->data->name,param)==0){
      found = true;
      break;
    }
    prev=pivot;
  } while(list_walk(&pivot));
  
  if(!found){
    printf("Song name \"%s\" not found.\n",buf);
  }

  list_delete(l,prev,pivot);
}

void server_view(ListType *l)
{
  char *view, *tok, *saveptr;
  NodeType *pivot = l->head;

  socket_send(PROTO_REPLY);
  if(pivot == NULL){
    socket_send_raw_param("No songs on the server");
    socket_send_raw_param(PROTO_END_PARAMETERS);
    return;
  }

  view = list_view(l);
  printf(">>>START\n%sEND<<<\n",view);
  tok = strtok_r(view,"\n",&saveptr);
  for(;;){ 
    if(tok == NULL){
      break;
    }
    socket_send_raw_param(tok);
    tok=strtok_r(NULL,"\n",&saveptr);
  }
  socket_send_raw_param(PROTO_END_PARAMETERS);

  free(view); // free from calloc in list_view
}

void server_quit()
{}
