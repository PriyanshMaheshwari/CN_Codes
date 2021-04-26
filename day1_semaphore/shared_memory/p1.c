#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
// #include <iostream>
// using namespace std;

int main()
{
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);
    printf("Write Data : \n");
    fgets(str,20,stdin);

    printf("Data written in memory: %s\n",str);

    //detach from shared memory
    shmdt(str);

    return 0;
}
// #include<stdio.h> #include<unistd.h> #include<fcntl.h> #include<stdlib.h> int main() { int fd; char buf[128]; fd=open("mytext.txt",O_RDONLY); read(fd,buf,10); printf("%s",buf); int c=fork(); if(c>0) { read(fd,buf,10); //cout<<buf; printf("%s",buf); } else { read(fd,buf,10); //cout<<buf; printf("%s",buf); } return 0; }15:45
