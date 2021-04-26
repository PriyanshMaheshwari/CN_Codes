#include<iostream>
#include<unistd.h>
#include <stdio.h>
#include<cstring>
using namespace std;
int main(){

	char buffer1[1024];
	char buffer2[1024];
	int rfd,wfd;
    rfd=dup(STDIN_FILENO);
    wfd=dup(STDOUT_FILENO);
	int t=2;
	while(t--)
	{
		read(rfd,buffer1,1024);
    dup2(7,STDIN_FILENO);
dup2(8,STDOUT_FILENO);
    cout << "Read by child : ";
    for( int i=0;i<1024;i++)
		{
			if(buffer1[i]!='\0')
			{
				cout << buffer1[i] ;
			}
			else
			break;
		}
    cout << endl;
		int i;
		memset(buffer2,0,sizeof(buffer2));
    cout << "Enter input from child : ";
		cin >> buffer2;
		write(wfd,buffer2,1024);
	}
	close(rfd);
	close(wfd);

}
