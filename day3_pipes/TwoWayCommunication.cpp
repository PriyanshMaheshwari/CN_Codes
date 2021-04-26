#include<stdio.h>
#include<unistd.h>
#include<bits/stdc++.h>
using namespace std;
#define SIZE 50
int main(){
   int fd1[2];//file descriptor one fd1[0] for read(child end), fd1[1] for write(parent end)
   int fd2[2];//file descriptor one fd2[0] for read(parent end), fd2[1] for write(child end)
   int a=pipe(fd1);
   int b=pipe(fd2);
  if(a==-1||b==-1){
  cout<<"Error in Pipes\n";
  return 1;
  }
   int pid=fork();//child create
   if(pid==0){
     // fd1 -> parent to Child
     // fd2 -> child to parent
       close(fd1[1]);//close pipe1 write end close for child
       close(fd2[0]);//close pipe2 read end close for child
       int k=2;
       while(k--){
         string str;
         read(fd1[0],&str,SIZE);
         cout<<"Read from Child End : ";
         cout<<str<<"\n";
          cout<<"Enter the string from Child End : ";
         string s;
         getline(cin,s);
         write(fd2[1],&s,SIZE);
       }
       close(fd2[1]);
       close(fd1[0]);
      }
   else{
       close(fd2[1]);//close pipe1 write end close for parent
       close(fd1[0]);//close pipe2 read end close for parent
       int k=2;
       while(k--){
         cout<<"Enter the string from Parent End : ";
         string s;
         getline(cin,s);
         write(fd1[1],&s,SIZE);
         string str;
         read(fd2[0],&str,SIZE);
         cout<<"Read from Parent End : ";
         cout<<str<<"\n";
       }
       close(fd1[1]);
       close(fd2[0]);
   }
   return 0;
}

//g++ TwoWayCommunication.cpp -o TwoWayCommunication
