#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid=fork();
    pid_t pid2 = fork();                                  //~
    if (pid==0 && pid2>0){                                // 1    0
      static char *argv[]={"./a2.out",NULL};        //     11 10 01 00
      execv(argv[0],argv);
      exit(127); /* only if execv fails */
    }
    else if(pid2 == 0 && pid > 0){
      static char *argv[]={"./a3.out",NULL};
      execv(argv[0],argv);
      exit(127); /* only if execv fails */
    }
    else if(pid > 0 && pid2 > 0){ /* pid!=0; parent process */
      printf("Program 1 start\n");
      waitpid(pid,0,0);
      waitpid(pid2,0,0); /* wait for child to exit */
      printf("Program 1 exit\n");
    }
    return 0;
}
