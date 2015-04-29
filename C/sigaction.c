#include <signal.h>
#include <stdio.h>

void signal_handler(int signum){
  (void)signum;
  puts("Signal handled");
}

int main(){
  struct sigaction new;
  new.sa_handler = signal_handler;
  sigemptyset(&new.sa_mask);
  sigaction(SIGALRM, &new, NULL);
  raise(SIGALRM);
  return 0;
}
