#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(){
  int in;
  int stdin = dup(0);
  in = open("text", O_RDONLY);
  dup2(in,0);
  pid_t pid = fork();
  if(pid == 0){
    static char *argv[]={"./a2.out",NULL};
    execv(argv[0],argv);
    exit(127);
  }
  else{
    waitpid(pid,0,0);
    for(int i=0;i<5;i++){
      char c;
      scanf(" %c", &c);
      printf("%c\n",c);
    }
    dup2(STDIN_FILENO,0);
    printf("Input a character\n");
    char c;
    scanf(" %c", &c);
    printf("%c\n",c);
  }
}
