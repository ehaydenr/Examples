#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
int main(){
  // Create socket
  // int socket(int domain, int type, int protocol)
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  
  // Addrinfo
  // int getaddrinfo( char *hostname, char *servname, struct addrinfo *hints, struct addrinfo **res)
  struct addrinfo hints, *result;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, "3000", &hints, &result);

  // Bind
  // int bind(int socket, struct sockaddr *address, socklen_t address_len)
  bind(sockfd, result->ai_addr, result->ai_addrlen);

  // Recieve
  // ssize_t recvfrom(int socket, void* buffer, size_t buflen, int flags, struct sockaddr *addr, socklen_t * address_len);
  void * buf = malloc(1024);
  ssize_t res = recvfrom(sockfd, buf, 1024, 0, NULL, NULL);
  printf("bytes: %zu, buf: %s", res, (char*)buf);

  return 0;
}
