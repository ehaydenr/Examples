#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
  // Create socket
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // Address info
  struct addrinfo hints, *result;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_protocol = SOCK_STREAM;

  getaddrinfo("localhost", "3000", &hints, &result);

  connect(sockfd, result->ai_addr, result->ai_addrlen);
  FILE * fp = fdopen(sockfd, "r");
  if(fp == NULL){
    perror("connect");
    return 1;
  }

  char line[1024];
  while(fgets(line, sizeof(line), fp)){
    write(STDOUT_FILENO, line, strlen(line));
  }

  fclose(fp);

  return 0;
}
