#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
/*
 *        void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
 *        int munmap(void *addr, size_t length);
 */
int main(int argc, char * argv[]){
  if(argc < 3) return 1;

  puts("Opening files");
  FILE * fp = fopen(argv[1], "r");
  FILE * fp2 = fopen(argv[2], "w+");

  puts("Seeking");
  fseek(fp, 0, SEEK_END);

  puts("Telling");
  size_t len = ftell(fp);

  puts("Seeking");
  fseek(fp, 0, SEEK_SET);

  puts("Truncating");
  ftruncate(fileno(fp2), len);

  puts("Mapping");
  char * buffer = (char *)mmap(NULL, len, PROT_READ, MAP_PRIVATE, fileno(fp), 0); 
  char * buffer2 = (char *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fileno(fp2), 0);


  puts("Copying");
  memcpy(buffer2, buffer, len);

  puts("unmapping");
  munmap(buffer, len);
  munmap(buffer2, len);

  return 0;
}
