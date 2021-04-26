#include<stdio.h>
#include<unistd.h>
int main(){
   int fd[2];//fd[0] for read,fd[1] for write
   pipe(fd);//pipe function
   printf("Enter 5 Values\n");
   for(int i=0;i<5;i++){
      int x;
      scanf("%d",&x);
      write(fd[1],&x,sizeof(int));
   }
   printf("Values Stored in Pipe\n");
   for(int i=0;i<5;i++){
      int k;
      read(fd[0],&k,sizeof(int));
      printf("%d ",k);
   }
return 0;
}

//gcc Intro.cpp -o Intro
