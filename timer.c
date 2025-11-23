/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t message = 0;
volatile sig_atomic_t count = 0;
time_t start_time;

void alarm_handler(int signum)
{ //signal alarm_handler

  // Handler executes quickly; no shared non-atomic state modified here.
  // Reentrancy is safe because count/message are sig_atomic_t.
  printf("Hello World!\n");
  message = 1;
  count++;
  alarm(5);
}

void int_handler(int signum)
{ //signal alarm_handler
  time_t now = time(NULL);
  int elapsed = (int)(now - start_time);
  printf("Number of alarms: %d\n", count);
  printf("Time in time_in_execution: %d secs\n", elapsed);
  exit(0);
}

int main()
{ 
  start_time = time(NULL);

  struct sigaction sa;

  // SIGALRM
  sa.sa_handler = alarm_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sigaction(SIGALRM, &sa, NULL);

  // SIGINT (Ctrl+C)
  sa.sa_handler = int_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sigaction(SIGINT, &sa, NULL);

  while(1){
    pause();

    if (message) { 
      printf("Turing was right!\n");
      message = 0;
    }
  }
  return 0;
}
