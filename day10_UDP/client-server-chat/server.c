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
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    sfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    bind(sfd, (const struct sockaddr *)&servaddr,sizeof(servaddr));
    int len, n;

    len = sizeof(cliaddr);

    while(1)
    {
        n = recvfrom(sfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                (socklen_t*)&len);
        buffer[n] = '\0';
        printf("Client : %s\n", buffer);
        fgets(hello,1024,stdin);
        sendto(sfd, (const char *)hello, strlen(hello),
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                len);
    }

    return 0;
}
