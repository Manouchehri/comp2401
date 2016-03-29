#include "client.h"

int main()
{
  char str[MAX_STR];
  char buffer[MAX_BUFF];

  initClientSocket();

/* get input from user and send to server */
  for(;;) {
    printMenu();

    memset(str,'0',MAX_STR);
    fgets(str, sizeof(str), stdin);

    strcpy(buffer, str);
    send(mySocket, buffer, strlen(buffer), 0);
    if (strncasecmp(str, "a",1) == 0){ 

      continue;
    }
    if (strncasecmp(str, "d",1) == 0){
      controller_delete();
    }
    if (strncasecmp(str, "v",1) == 0)
    if (strncasecmp(str, "q",1) == 0)
  }

/* close the socket */
  close(mySocket);

  return 0;
}

void initClientSocket(void)
{
  struct sockaddr_in  addr;
  int i;

/* create socket */
  mySocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (mySocket < 0) {
    printf("couldn't open socket\n");
    exit(-1);
  }

/* setup address */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  addr.sin_port = htons((unsigned short) SERVER_PORT);

/* connect to server */

  i = connect(mySocket, 
              (struct sockaddr *) &addr,
              sizeof(addr));
  if (i<0) {
    printf("client could not connect!\n");
    exit(-1);
  }
}

void printMenu(void)
{
  printf(MENU_TEXT);
}
