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
    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    
    // Get address information
    struct addrinfo hints, * result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_protocol = SOCK_STREAM;
    
    getaddrinfo(NULL, "3000", &hints, &result);
    
    if (bind(sockfd, result->ai_addr, result->ai_addrlen) != 0) {
        perror("bind()");
        return 1;
    }
    
    if(listen(sockfd, 10) != 0){
        perror("listen()");
        return 1;
    }
    
    int clientfd = accept(sockfd, NULL, NULL);
    
    FILE * f = fopen("index.html", "r");
    if(f == NULL){
        perror("fopen()");
        return 1;
    }
    
    char line[1024];
    while(fgets(line, sizeof(line), f)){
        write(clientfd, line, strlen(line));
        write(STDOUT_FILENO, line, strlen(line));
    }
    
    fclose(f);
    
    close(clientfd);
    close(sockfd);
    
    return 0;
}
