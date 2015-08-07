#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
  int fd[2];
  pipe(fd);
  pid_t pid = fork();
  if(pid > 0){ // Parent
    close(fd[1]); // Close write for parent

    dup2(fd[0], 0);

    char * buffer = NULL;
    size_t len;
    while(getline(&buffer, &len, stdin) != -1){
      puts("Parent: About to print out");
      puts(buffer);
    }

    puts("Parent: waiting on child");
    waitpid(pid, NULL, 0);
    puts("Parent: child waited on");
    close(fd[0]);
  }else{ // Child
    close(fd[0]); // Close read for child

    puts("Child: Going to print");
    dup2(fd[1], 1); // redirect stdout to write

    printf("hello parent\n");

    close(fd[1]);
    exit(0);
  }
}
