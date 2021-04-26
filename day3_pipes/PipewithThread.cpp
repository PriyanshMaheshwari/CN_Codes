#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<bits/stdc++.h>
using namespace std;
int fd[2];//define globally so anyone can access it
void* writethread(void*){
    int value=0;
    int result;
   while(1){
     //close(fd[0]);
     result=write(fd[1],&value,sizeof(int));
      if (result==-1){
           perror ("write error");
           exit (2);
       }
        cout<<"Writing from Thread1 : "<<value<<"\n";
        value++;
        if(value>26)
        value=1;
        sleep(1);
   }
}
void* readthread(void*){
   int value=0;
   int result;
   while(1){
     //close(fd[1]);
     sleep(1);
     result=read(fd[0],&value,sizeof(int));
      if (result==-1){
           perror ("read error");
           exit (2);
       }
        cout<<"Reading from Thread2 : "<<value<<"\n";
   }
}
int main(){
    int p=pipe(fd);
     if(p<0){
     cout<<"Error because of Pipe\n";
     return 1;
     }
     pthread_t t1,t2;
   pthread_create(&t1,NULL,readthread,NULL);
   pthread_create(&t2,NULL,writethread,NULL);

   pthread_join(t1,NULL);
   pthread_join(t2,NULL);

return 0;
}
//g++ PipewithThread.cpp -lpthread -o PipewthThread
