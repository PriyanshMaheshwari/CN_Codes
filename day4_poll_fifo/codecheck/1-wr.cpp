#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <bits/stdc++.h>
using namespace std;

int main(){
  system("g++ prog.cpp -o p.out");
  system("./p.out < in > output");
  FILE* wfd = popen("./p.out","w");
  FILE* fd = popen("./p.out","r");
	//int fd=open("./output",O_RDONLY);
  int fd2=open("./out",O_RDONLY);
  int wfd2=open("./in",O_RDONLY);
	char c1,c2;
  char in;
  bool f=true;
  int x,y,z,t;
  while(x && y && z && t){
    t = read(wfd2,&in,1);
    z = write(fileno(wfd),&in,1);
    x = read(fileno(fd),&c1,1);
    y = read(fd2,&c2,1);
    if(x!=y | c1 != c2) {f=false;break;}
  }
  if(f) cout << "Accepted" << endl;
  else cout << "Rejected" << endl;

	return 0;
}
