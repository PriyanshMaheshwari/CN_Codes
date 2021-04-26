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
  //system("./p.out < in > output");

  FILE* fd = popen("./p.out < in","r");
	//int fd=open("./output",O_RDONLY);
  int fd2=open("./out",O_RDONLY);
	char c1,c2;
  bool f=true;
  int x,y;
  while(x && y){
    x = read(fileno(fd),&c1,1);
    y = read(fd2,&c2,1);
    if(x!=y | c1 != c2) {f=false;break;}
  }
  if(f) cout << "Accepted" << endl;
  else cout << "Rejected" << endl;

	return 0;
}
