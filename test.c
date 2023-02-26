#include <stdio.h>
#include <signal.h>

void signal_handler(int signum) {
    printf("Received signal %d\n", signum);
}

int main(void) {
    signal(SIGINT, signal_handler);
    
    printf("Press Ctrl-C to send an interrupt signal\n");
    
    while (1) {
        // Main program loop
    }
    
    return 0;
}