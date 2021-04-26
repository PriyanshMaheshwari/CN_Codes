#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <string.h>
using namespace std;

void* thread1(void*){
  mkfifo("serve",0666);mkfifo("C2",0666);
	mkfifo("C1",0666);mkfifo("C3",0666);
	while(1){
	int fd = open("serve",O_RDONLY);
	cout<<"Serve Fifo is opened\n";
	char buff[1024];
	read(fd,&buff,1024);
	cout<<"Message read from group by server "<<buff<<"\n";
  int wd[3];
  wd[0] = open("C1",O_WRONLY);
  wd[1] = open("C2",O_WRONLY);
  wd[2] = open("C3",O_WRONLY);

	 //write(wd[0],buff,1024);
  int x = buff[1]-'0';
  for(int i=0;i<3;i++){
    if(x!=i+1){
      write(wd[i],buff,1024);
    }
  }
  //close(wd[0]);
	close(wd[0]);close(wd[1]);close(wd[2]);
	close(fd);
   }
}

int main()
{
  pthread_t t1;
	pthread_create(&t1,NULL,thread1,NULL);

	pthread_join(t1,NULL);
	return 0;
}
