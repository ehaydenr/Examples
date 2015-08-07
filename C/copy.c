#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char * argv[]){
  if(argc < 3) return 0;
  int fd = open(argv[1], O_RDONLY);
  int fd2 = open(argv[2], O_WRONLY | O_TRUNC);

  int len;
  char buffer[1024];
  while( (len = read(fd, buffer, sizeof(buffer) ) > 0) ){
    write(fd2, buffer, strlen(buffer));
  }

}
