#include "client.h"

int main()
{
  char str[MAX_STR];

  mySocket = -1;
  initClientSocket();

  /* get input from user and send to server */
  for (;; ) {
    printMenu();

    memset(str, '0', MAX_STR);
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

    close(mySocket);
  }


  return EXIT_SUCCESS;
}

void initClientSocket(void)
{
  struct sockaddr_in addr;
  int i;

/* create socket */
  mySocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (mySocket < 0) {
    printf("couldn't open socket\n");
    exit(-1);
  }

/* setup address */
  memset(&addr, 0, sizeof (addr) );
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  addr.sin_port = htons( (unsigned short) SERVER_PORT);

/* connect to server */

  i = connect(mySocket, (struct sockaddr *) &addr, sizeof (addr) );
  if (i < 0) {
    printf("client could not connect!\n");
    exit(EXIT_FAILURE);
  }
}

void printMenu(void)
{
  printf(MENU_TEXT);
}

void controller_delete(void)
{
  char buf[MAX_BUFF];
  memset(buf, 0, MAX_BUFF);
  socket_send(PROTO_DELETE);
  printf("Enter song name to be deleted:\t");
  memset(buf, 0, MAX_BUFF);
  fgets(buf,MAX_STR,stdin);
  socket_send(buf);
}
void controller_view(void)
{
  
}
void controller_add(void)
{
  
}
void controller_quit(void)
{
  
}

void socket_send(char *str)
{
  char buffer[MAX_BUFF];

  assert(mySocket != -1); // the socket must be initialized

  if (strlen(str) > MAX_BUFF-2){ // -2 for \n\0
    perror("socket_send: buffer overflow prevented");
    exit(EXIT_FAILURE);
  }
  strcpy(buffer, str);
  strcat(buffer,"\n");
  send(mySocket, buffer, strlen(buffer), 0);
}
