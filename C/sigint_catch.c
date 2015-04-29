#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void catch(int signal_number){
  printf("Caught signal with number: %d.\n", signal_number);
  exit(signal_number);
}

int main(){
  signal(SIGINT, catch);

  while(1){
    printf("Busy loop.\n");
    sleep(1);
  }

  return 0;
}
