#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE  1024

// Driver code
int main()
{
    int sfd;
    char buffer[MAXLINE];
    char hello[MAXLINE];
    struct sockaddr_in     servaddr;

    // Creating socket file descriptor
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    while(1)
    {
        fgets(hello,1024,stdin);
        sendto(sfd, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
        n = recvfrom(sfd, (char *)buffer, MAXLINE,MSG_WAITALL, (struct sockaddr *) &servaddr,(socklen_t*)&len);
        buffer[n] = '\0';
        printf("Server : %s\n", buffer);
    }
    close(sfd);
    return 0;
}
