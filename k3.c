#include <unistd.h>
#include <stdio.h>

int main() {
    printf("Je suis ton père (%d)\n", getpid());
                                     
    pid_t pid1 = fork();             
    if (pid1 == 0) {                 
        printf("Je suis ton fils (%d)\n", getpid());
        return 0;                    
    }                                
                                     
    pid_t pid2 = fork();             
    if (pid2 == 0) {                 
        printf("Je suis ta fille (%d)\n", getpid());
        return 0;                    
    }                                
                                     
    printf("Je suis ton père (%d)\n", getpid());
                                     
    return 0;                        
}
