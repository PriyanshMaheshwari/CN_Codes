
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

int main()
{
    /*Spawn a child to run the program.*/
    // pid_t pid=fork();
    // printf("Program 2 start\n");
    // if (pid==0) { /* child process */
    //     system("./a.out");
    //     static char *argv[]={"Going to third program.",NULL};
    //     execv("/bin/echo",argv);
    //     exit(127); /* only if execv fails */
    // }
    // else{ /* pid!=0; parent process */
    //     waitpid(pid,0,0); /* wait for child to exit */
    //     printf("Program 2 exit\n");
    // }
    printf("Program 4 start\n");
    printf("Program 4 exit\n");
    return 0;
}
