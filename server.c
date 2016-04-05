#include  "server.h"

int global_listen_socket, global_socket;

int main()
{
  char buffer[MAX_BUFF];
  ListType list;
  list_init(&list);

  init_server_socket();

  while (1) {
    /*  waiting for next client to connect  */
    wait_for_connection();
    /*  a client has connected  */

    /* read messages from client and do something with it  */
    while (1) {
      socket_read(buffer);
      if (strncmp(buffer, PROTO_QUIT,3) == 0) {
        break;
      }
      else if (strncmp(buffer, PROTO_ADD,3)==0){
        server_add(list);
      }
      else if (strncmp(buffer, PROTO_DELETE,3)==0){
        server_delete();
      }
      else if (strncmp(buffer, PROTO_VIEW,3)==0){
        server_view();
      }
      else {
        printf("Received garbage: \"%s\"",buffer);
      }
    }
    /*  closing this client's connection  */
    close(global_socket);
  }

  /*  all done, no more clients will be connecting  */
  close(global_listen_socket);

  return EXIT_SUCCESS;
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

