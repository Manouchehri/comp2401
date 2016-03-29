#include "client.h"

int main()
{
  char str[MAX_STR];
  char buffer[MAX_BUFF];

  initClientSocket();

/* get input from user and send to server */
  while (1) {
    printf("Please enter message: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str)-1] = '\0';

    strcpy(buffer, str);
    send(mySocket, buffer, strlen(buffer), 0);
    if (strcmp(str, "quit") == 0)
      break;
  }

/* close the socket */
  close(mySocket);

  return 0;
}

void initClientSocket()
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

