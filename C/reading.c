#include <stdio.h>
#include <pthread.h>

#define BYTES_TO_READ (14)

void * thread_read(void * arg){
  int read_fd = *(int *)arg;

  size_t index = 0;
  size_t bytes_read = 0;

  char buffer[BYTES_TO_READ];
  while( index < BYTES_TO_READ && (bytes_read = read(read_fd, buffer + index, BYTES_TO_READ)) > 0 ){
    index += bytes_read;
  }

  printf("All bytes read. Buffer: %s.\n", buffer);

  close(read_fd);

  return NULL;
}

int main(){
  int fd[2];
  pipe(fd);

  pthread_t tid;
  pthread_create(&tid, NULL, thread_read, &fd[0]);

  write(fd[1], "hello", 5);
  sleep(2);
  write(fd[1], "world", 5);
  sleep(3);
  write(fd[1], "done", 4);

  close(fd[1]);

  pthread_join(tid, NULL);

  return 0;
}
