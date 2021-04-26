#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<bits/stdc++.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
int fd1[2];
int fd2[2];//define globally so anyone can access it
void* writethreadpar(void*){
    int value=0;
    int result;
   while(1){
     //close(fd[0]);
     cout << "Enter the value for par : ";
     cin >> value;
     result=write(fd1[1],&value,sizeof(int));
      if (result==-1){
           perror ("write error");
           exit (2);
       }

        cout<<"Writing from parent thread: "<<value<<"\n";
        // value++;
        // if(value>26)
        // value=1;
        sleep(1);
   }
}

void* writethreadchi(void*){
    int value=0;
    int result;
   while(1){
     //close(fd[0]);
     cout << "Enter the value for chi : ";
     cin >> value;
     result=write(fd2[1],&value,sizeof(int));
      if (result==-1){
           perror ("write error");
           exit (2);
       }
        cout<<"Writing from child thread: "<<value<<"\n";
        // value++;
        // if(value>26)
        // value=1;
        sleep(1);
   }
}

void* readthreadpar(void*){
   int value=0;
   int result;
   while(1){
     //close(fd[1]);
     sleep(1);
     result=read(fd2[0],&value,sizeof(int));
      if (result==-1){
           perror ("read error");
           exit (2);
       }
        cout<<"Reading from Thread2 : "<<value<<"\n";
   }
}

void* readthreadchi(void*){
   int value=0;
   int result;
   while(1){
     //close(fd[1]);
     sleep(1);
     result=read(fd1[0],&value,sizeof(int));
      if (result==-1){
           perror ("read error");
           exit (2);
       }
        cout<<"Reading from Thread2 : "<<value<<"\n";
   }
}

int main(){
    int p1=pipe(fd1);
    int p2=pipe(fd2);
     if(p1<0){
     cout<<"Error because of Pipe\n";
     return 1;
     }
     if(p2<0){
     cout<<"Error because of Pipe\n";
     return 1;
     }

     pid_t pid = fork();
     if(pid == 0){
       close(fd1[1]);close(fd2[0]);
       pthread_t t1,t2;
       pthread_create(&t1,NULL,readthreadchi,NULL);
       pthread_create(&t2,NULL,writethreadchi,NULL);
       pthread_join(t1,NULL);
       pthread_join(t2,NULL);
     }
     else{
       close(fd1[0]);close(fd2[1]);
       pthread_t t1,t2;
       pthread_create(&t1,NULL,readthreadpar,NULL);
       pthread_create(&t2,NULL,writethreadpar,NULL);
       pthread_join(t1,NULL);
       pthread_join(t2,NULL);
     }

return 0;
}
//
