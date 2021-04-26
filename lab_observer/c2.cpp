#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
#define PORT 6000

int main(int argc, char const *argv[])
{
  cout << "yo"  << endl;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buff[1024];
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    fgets(buff,1024,stdin);
    send(sock , buff , strlen(buff) , 0 );
    valread = recv( sock , buffer, 1024,0);
    buffer[valread] = '\0';
    printf("%s\n",buffer );
    return 0;
}
