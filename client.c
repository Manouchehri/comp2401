#include "client.h"

int main()
{
  char str[MAX_STR];
  struct sigaction sigact;


  global_socket = -1;
  init_client_socket();

  memset(&sigact, 0, sizeof(sigact));
  sigact.sa_sigaction = sig_handler;
  sigact.sa_flags = SA_SIGINFO;
  sigaction(SIGTERM, &sigact, NULL);
  
  /* get input from user and send to server */
  for (;; ) {
    view_menu();

    memset(str, 0, MAX_STR);
    fgets(str, MAX_STR-1, stdin);

    if (strncasecmp(str, "a", 1) == 0) {
      controller_add();
      continue;
    }
    if (strncasecmp(str, "d", 1) == 0) {
      controller_delete();
      continue;
    }
    if (strncasecmp(str, "v", 1) == 0) {
      controller_view();
      continue;
    }
    if (strncasecmp(str, "q", 1) == 0) {
      controller_quit();
      break;
    }
  }
  raise(SIGTERM);
  return EXIT_SUCCESS;
}

void sig_handler(int signum, siginfo_t *info, void *ptr)
{
  close(global_socket);
}

void controller_add(void)
{
  socket_send(PROTO_ADD);
  socket_send_param("Enter song:\t",PROTO_VALID_USER_INPUT_CHARS);
  socket_send_param("Enter artist:\t",PROTO_VALID_USER_INPUT_CHARS);
  socket_send_param("Enter album:\t",PROTO_VALID_USER_INPUT_CHARS);
  socket_send_param("Enter duration:\t",PROTO_VALID_USER_INPUT_CHARS_FOR_INTEGER);
  socket_send(PROTO_END_PARAMETERS);
}

void controller_delete(void)
{
  socket_send(PROTO_DELETE);
  socket_send_param("Enter song name to delete:\t");
  socket_send(PROTO_END_PARAMETERS);
}

void controller_view(void)
{
  socket_send(PROTO_VIEW);
  
}

void controller_quit(void)
{
  socket_send(PROTO_QUIT);
}

void view_menu(void)
{
  printf(MENU_TEXT);
}

void  init_client_socket(void)
{
  struct sockaddr_in addr;
  int i;

  /* create socket */
  global_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (global_socket < 0) {
    printf("couldn't open socket\n");
    exit(-1);
  }

  /* setup address */
  memset(&addr, 0, sizeof (addr) );
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  addr.sin_port = htons( (unsigned short) SERVER_PORT);

  /* connect to server */
  i = connect(global_socket, (struct sockaddr *) &addr, sizeof (addr) );
  if (i < 0) {
    printf("client could not connect!\n");
    exit(EXIT_FAILURE);
  }
}
