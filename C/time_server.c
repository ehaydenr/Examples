/*
 * Some code taken from: https://github.com/angrave/SystemProgramming/wiki/
 * Building a basic TCP time server in C
 * 4 Steps:
 *    1) Create Socket
 *    2) Bind
 *    3) Listen
 *    4) Accept
 */

#include <sys/socket.h> 
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define PORT "8080"
#define QUEUE_LEN (10)

int main(){

  time_t current_time;

  // Creating socket
  // sockfd = socket(int socket_family, int socket_type, int protocol);
  // AF_INET -> IP
  // SOCK_STREAM -> Provides sequenced, reliable, two-way, connection-based byte streams.
  // IPPROTO_TCP -> TCP
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // Get the information we need about 
  struct addrinfo hints, *result;
  /*
   * int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
   */
  memset(&hints, 0, sizeof(struct addrinfo)); // clear out all hints before setting to ensure getaddrinfo isn't reading trash
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE; // AI_PASSIVE -> We are going to be a server

  char * node = NULL; // If node is NULL, then the network address will be set to the loopback interface address
  int a = getaddrinfo(node, PORT, &hints, &result);
  if(a != 0){
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(a));
    return 1;
  }

  // Bind socket on address
  if (bind(sockfd, result->ai_addr, result->ai_addrlen) != 0) {
    perror("bind()");
    return 1;
  }

  // Listen
  if (listen(sockfd, QUEUE_LEN) != 0) {
    perror("listen()");
    return 1;
  }

  struct sockaddr_in *result_addr = (struct sockaddr_in *) result->ai_addr;
  printf("Listening on file descriptor %d, port %d\n", sockfd, ntohs(result_addr->sin_port));

  // Accept connections until killed
  while(1){
    printf("Waiting for connection...\n");
    int client_fd = accept(sockfd, NULL, NULL);
    printf("Connection made: client_fd=%d\n", client_fd);

    // Send them the time!
    current_time = time(NULL);
    FILE * fptr = fdopen(client_fd, "w");
    fprintf(fptr, "The time is: %s\n", ctime(&current_time));

    // Close client;
    fclose(fptr);
    printf("Closed: client_fd=%d\n", client_fd);
  }

  return 0;
}
