#include  "server.h"

int myListenSocket, clientSocket;

int main()
{
  char buffer[MAX_BUFF];

  initServerSocket();

  while (1) {

/*  waiting for next client to connect  */
    waitForConnection();
/*  a client has connected  */

/* read messages from client and do something with it  */
    while (1) {
      recvText(buffer);
      printf("the client sent:  %s\n", buffer);
      if(strcmp(buffer,"quit") == 0) {
        break;
      }
    } 
/*  closing this client's connection  */
    close(clientSocket);
  }

/*  all done, no more clients will be connecting  */
  close(myListenSocket);

  return 0;
}

void initServerSocket()
{
  struct sockaddr_in  myAddr;
  int i;

/* create socket */
  myListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (myListenSocket < 0) {
    printf("couldn't open socket\n");
    exit(-1);
  }

/* setup my server address */
  memset(&myAddr, 0, sizeof(myAddr));
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myAddr.sin_port = htons((unsigned short) MY_PORT);

/* bind my listen socket */
  i = bind(myListenSocket, 
           (struct sockaddr *) &myAddr,
           sizeof(myAddr));
  if (i < 0) {
    printf("couldn't bind socket\n");
    exit(-1);
  }

/* listen */
  i = listen(myListenSocket, 5);
  if (i < 0) {
    printf("couldn't listen\n");
    exit(-1);
  }
}

void waitForConnection()
{
  struct sockaddr_in clientAddr;
  int addrSize;

  printf("waiting for connection... \n");

/* wait for connection request */
  clientSocket = accept(myListenSocket,
                        (struct sockaddr *) &clientAddr,
                        &addrSize);
  if (clientSocket < 0) {
    printf("couldn't accept the connection\n");
    exit(-1);
  }
  printf("got one! \n");
}

void recvText(char *text)
{
  char buff[MAX_BUFF];
  int bytesRcv;

  buff[0] = '\0';

  bytesRcv = recv(clientSocket, buff, sizeof(buff), 0);
  buff[bytesRcv] = '\0';
  strcpy(text, buff);
}

