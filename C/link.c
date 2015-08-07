#include <stdio.h>
#include <unistd.h> 
int main(int argc, char * argv[]){
  //int link(const char *path1, const char *path2);
  if(argc < 4) return 1;

  link(argv[1], argv[2]);
  symlink(argv[1], argv[3]);
  
}
