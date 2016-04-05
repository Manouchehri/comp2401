#include "protocol.h"

void socket_send_param(const char *prompt, const char *accept)
{
  int a,b;
  char str[MAX_STR];
  char buf[MAX_BUFF];

  for(;;){
    printf("%s",prompt);
    memset(buf, 0, MAX_BUFF);
    memset(str, 0, MAX_STR);
    if(fgets(str,MAX_STR-1,stdin) == NULL){
      continue;
    }
    str[strlen(str)-1]=0; // replace \n with \0
    if((a=strspn(str,accept)) != (b=strlen(str))){
      /* printf("strspn=%d strlen=%d {%s}\n",a,b,buf); */
      printf("Invalid input '%s'. Only the characters below in [] are allowed. Try again.\n[%s]\n",str,accept);
      continue;
    }
    strcpy(buf,PROTO_PARAMETER);
    strcat(buf,str);
    socket_send(buf);
    break;
  }
}

void socket_send(const char *str)
{
  assert(global_socket != -1); // the socket must be initialized

  if (strlen(str) > MAX_BUFF-1){ // -1 for \0
    perror("socket_send: buffer overflow prevented");
    exit(EXIT_FAILURE);
  }
  send(global_socket, str, strlen(str), 0);
}

void socket_read(char *text)
{
  char buff[MAX_BUFF];
  int bytesRcv;

  buff[0] = '\0';

  bytesRcv = recv(global_socket, buff, sizeof (buff), 0);
  buff[bytesRcv] = '\0';
  strcpy(text, buff);
}
