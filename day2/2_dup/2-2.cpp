#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(){
  for(int i=0;i<5;i++){
    char c;
    scanf(" %c", &c);
    printf("%c\n",c);
  }
  // int fd;
  // dup2(fd,0);
  // char buf[2];
  // buf[1] = '\0';
  // read(fd,buf,1);
  // printf("%c\n",buf[0]);'
  int stdin = dup(0);
  dup2(stdin,0);
  printf("Input a character\n");
  char c;
  scanf(" %c", &c);
  printf("%c\n",c);
}
