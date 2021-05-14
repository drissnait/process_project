#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char* argv[] ) 
{ 
    printf("Father : %d\n",getpid());
    int nbrProcessus=atoi(argv[1]);
    for(int i=0;i<nbrProcessus;i++) // loop will run n times (n=5) 
    { 
        if(fork() == 0) 
        { 
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            exit(0); 
        } 
    } 
    for(int i=0;i<5;i++) // loop will run n times (n=5) 
    wait(NULL); 
      
} 
