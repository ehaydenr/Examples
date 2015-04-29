#include <sys/stat.h>
#include <stdio.h>
//int lstat(const char *restrict path, struct stat *restrict buf);

int main(int argc, char * argv[]){
  if(argc < 2) return 1;
  struct stat s;
  lstat(argv[1],  &s);
  if(S_ISLNK(s.st_mode)){
    puts("Link");
  }else if(S_ISDIR(s.st_mode)){
    puts("Directory");
  }
  return 0;
}
