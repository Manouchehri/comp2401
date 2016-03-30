#include "client.h"

int main()
{
  char str[MAX_STR];

  mySocket = -1;
  initClientSocket();

  /* get input from user and send to server */
  for (;; ) {
    printMenu();

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

  printf("Enter song name to delete:\t");
  memset(buf, 0, MAX_BUFF);
  fgets(buf,MAX_STR,stdin);
  socket_send(buf);
}
void controller_view(void)
{
  socket_send(PROTO_VIEW);
}
void controller_add(void)
{

  socket_send(PROTO_ADD);
  get_and_send_for("Enter song name:\t",PROTO_VALID_USER_INPUT_CHARS);
  get_and_send_for("Enter artist:\t",PROTO_VALID_USER_INPUT_CHARS);
  get_and_send_for("Enter album:\t",PROTO_VALID_USER_INPUT_CHARS);
  get_and_send_for("Enter duration:\t",PROTO_VALID_USER_INPUT_CHARS_FOR_INTEGER);
}
void controller_quit(void)
{
  socket_send(PROTO_QUIT);
}

void get_and_send_for(const char *prompt, const char *accept)
{
  int a,b;
  char buf[MAX_BUFF];

  for(;;){
    printf("%s",prompt);
    memset(buf, 0, MAX_BUFF);
    if(fgets(buf,MAX_STR,stdin) == NULL){
      continue;
    }
    buf[strlen(buf)-1]=0; // replace \n with \0
    if((a=strspn(buf,accept)) != (b=strlen(buf))){
      printf("strspn=%d strlen=%d {%s}\n",a,b,buf);
      printf("Invalid input. Only the characters below are allowed. Try again.\n[%s]\n",accept);
      continue;
    }
    socket_send(buf);
    break;
  }
}

void socket_send(const char *str)
{
  char buffer[MAX_BUFF];
  memset(buffer, 0, MAX_BUFF);

  assert(mySocket != -1); // the socket must be initialized

  if (strlen(str) > MAX_BUFF-2){ // -2 for \n\0
    perror("socket_send: buffer overflow prevented");
    exit(EXIT_FAILURE);
  }
  strcpy(buffer, str);
  strcat(buffer,"\n");
  send(mySocket, buffer, strlen(buffer), 0);
}
