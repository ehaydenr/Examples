#include <time.h>
#include <stdio.h>

int main(){
  time_t current_time = time(NULL);
  char * time_str;
  time_str = ctime(&current_time);
  puts(time_str);
  return 0;
}
