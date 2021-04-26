#include<unistd.h>
#include<sys/uio.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

void* read1(void*){
  while(true){
    mkfifo("myfifo", 0666);
    int fd=open("myfifo", O_RDONLY);
    struct iovec iov[2];
    char buf1[100],buf2[100];
    iov[0].iov_base=buf1;
    iov[0].iov_len=100;
    iov[1].iov_base=buf2;
    iov[1].iov_len=100;
    readv(fd,iov,2);
    cout << "Read from client :-" << endl;
    cout<<buf1<<endl;
    cout<<buf2<<endl;
    close(fd);
  }
}

void* write1(void*){
    while(true){
    	mkfifo("myfifo2", 0666);
      int fd=open("myfifo2", O_WRONLY);
      struct iovec iov[2];
      char buf1[100],buf2[100];
      cin.getline(buf1,100);
      cin.getline(buf2,100);
      iov[0].iov_base=buf1;
      iov[0].iov_len=100;
      iov[1].iov_base=buf2;
      iov[1].iov_len=100;
      writev(fd,iov,2);
      cout<<"Written from server :"<<buf1<<buf2<<endl;
      close(fd);
    }
}

int main(){
  pthread_t t1,t2;
	pthread_create(&t1,NULL,write1,NULL);
  pthread_create(&t2,NULL,read1,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
  return 0;
}
