#include "protocol.h"

void socket_shutdown()
{
  shutdown(global_socket, SHUT_WR);
}

void socket_send_raw_param(const char *str)
{
  char buf[MAX_BUFF];
  size_t len;
  memset(buf,0,MAX_BUFF);
  len = strlen(str);
  strcpy(buf,PROTO_PARAMETER);
  strncat(buf,str,MAX_BUFF);

  if(str[len-1]!='\n'){
    if(len > MAX_BUFF-2){
      printf("socket_send_raw_param: buffer overflow prevented");
      return;
    }
    strcat(buf,"\n");
  }
  socket_send(buf);
}

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
    socket_send_raw_param(str);
    break;
  }
}

/**
 * Read the next parameter from `global_socket`.
 * @param param [out] Pointer to the newly-parsed parameter ending with the null character.
 * @param accept [in] Pointer to a string of acceptable characters for the parameter to contain.
 * @return Returns true if and only if a new parameter was parsed successfully, false otherwise, including
 *  the case where the parameter does not begin with `PROTO_PARAMETER`.
 */
bool socket_read_param(char **param, const char *accept)
{
  static char   bufarr[MAX_BUFF], *buf=bufarr;
  static char   *pos=NULL, *endpos=NULL;

  char *replace;

  if ( &pos >= &endpos ){
    // read from the socket
    for(;;){
      socket_read(buf); 
      if(strlen(buf)>0)
        break;
    }
    pos=buf;
    endpos=buf+(strlen(buf+1));

    /* replace newlines with the null char */
    while(*(replace = strchrnul(pos,'\n')) != '\0'){
      *replace='\0';
      pos=replace+1;
    }

    /* reset pos to to start of buf */
    pos=buf;
  }
  else {
    // move pos forward in buf
    pos = strchr(pos,'\0');
  }

  printf(">>>START\n%s\n<<<END\n",buf);
  if(strncmp(buf+1,PROTO_PARAMETER PROTO_END_PARAMETERS,2)==0){
    return false;
  }
  if(
      strncmp(pos,PROTO_PARAMETER,1)!=0  /* first char must be protocol parameter marker */
      ||
      strspn(pos+1, accept) != strlen(pos+1) /* rest must be chars ∈ accept */ 
    ){
    printf("Received invalid parameter: \"%s\"\n",buf);
    return false;
  }
  printf("%s\n",buf+1);
  
  if (param != NULL){
    *param = pos;
  }
  return true;
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
