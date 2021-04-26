#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
   char* myfifo2="myfifo2";
   mkfifo("myfifo2",0666);
   int t=3;
    char arr1[80], arr2[80];
   while(1){
    int fd = open(myfifo2,O_WRONLY); ;
    cout<<"C2 : ";
     fgets(arr2, 80, stdin);
    if(write(fd, arr2, strlen(arr2)+1)==-1){
       return 1;
    }
    close(fd);
   }


 return 0;
}
