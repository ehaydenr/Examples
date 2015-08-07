#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search_file(char * path, char * file){
  DIR * dir;
  struct dirent *dp;
  if((dir = opendir(path)) == NULL) return -1;

  while((dp = readdir(dir)) != NULL){

    char newpath[ strlen(path) + strlen(dp->d_name) + 2];
    sprintf(newpath, "%s/%s", path, dp->d_name);
    if(strcmp(dp->d_name, file) == 0){
      printf("Found file: %s\n", newpath);
    }

    struct stat s;
    if(lstat(newpath, &s) != 0){
      continue;
    }

    if(S_ISDIR(s.st_mode) && strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
      search_file(newpath, file);
    }
  }
  closedir(dir);
  return 0;
}

int main(int argc, char * argv[]){
  if(argc < 2) return 1;
  search_file(getenv("HOME"), argv[1]);
  return 0;
}
