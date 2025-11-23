/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t message = 0; 

void handler(int signum)
{ //signal handler
  message = 1;
  printf("Hello World!\n");
  alarm(5);
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(5); //Schedule a SIGALRM for 5 seconds

  while(1){
    pause();

    if (message){
      printf("Turing was right!\n");
      message = 0;
    }
  }
  return 0; //never reached
}
