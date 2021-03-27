#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <wait.h>

int main()
{
    printf("\n");
    while (1){
        int sleeptime;
        int pid; 
        
        // We use ps to observe the working processes
        printf("\n");
        // User is asked to give a snooze time
        printf("How long should the alarm sleep?: ");
        scanf("%d", &sleeptime);

         // We use waitpid to kill zombie processes
        int wp;
        do {
            wp = waitpid(-1, NULL,  WNOHANG);
            printf("Deceased child: %d \n", wp);
        } while (wp > 0); 
        
        // Added code for catching errors
        if (errno == ECHILD)
            printf("Error ECHILD: %d\n", errno);
        
        else if (errno == EINTR)
            printf("Error EINTR: %d\n", errno);
        
        else
            printf("Error EINVAL: %d \n", errno); 

        // The process is duplicated from OVER here
        pid = fork(); 

        if (pid > 0) {
            printf("\n");
        }
        else if (pid == 0) {
            sleep(sleeptime);
            printf("\n");
           // Alarm rings after sleeptime-seconds has passed
            printf("RING RING RING RING!"); 
            printf("\n");
            exit(0);
        }
    }    
}