
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

int main()
{
    /*Spawn a child to run the program.*/
    pid_t pid=fork();
    if (pid==0) { /* child process */
        static char *argv[]={"echo","Back to 1 program.",NULL};
        system("./a2.out");
        execv("/bin/echo",argv);
        exit(127); /* only if execv fails */
    }
    else{ /* pid!=0; parent process */
        printf("Program 1 start\n");
        waitpid(pid,0,0); /* wait for child to exit */
        printf("Program 1 exit\n");
    }
    return 0;
}
