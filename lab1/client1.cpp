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
   char* myfifo1="myfifo11";
   mkfifo("myfifo11",0666);
   int t=3;
    char arr1[80], arr2[80];
   while(1){
    int fd = open(myfifo1,O_WRONLY); ;
    cout<<"C1 : ";
    fgets(arr2, 80, stdin);
    int x = write(fd, arr2, strlen(arr2)+1);
    cout << x << endl;
    close(fd);
   }


 return 0;
}
