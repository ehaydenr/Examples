#include <stdio.h>
int main(){
  char * buffer = NULL;
  size_t len;
  while(getline(&buffer, &len, stdin) != -1){
    puts(buffer);
  }
  return 0;
}
