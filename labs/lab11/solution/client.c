#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STRSZ 100
#define PORT 3000

int main(int argc, char *argv[]) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
        perror("socket error");

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    int ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if(ret == -1)
        perror("connect error");

    char msg[STRSZ];
    while(1) {
        bzero(msg, STRSZ);
        fprintf(stdout, "Client: ");
        fscanf(stdin, "%[^\n]s", msg);
        setbuf(stdin, NULL);
        ret = send(sockfd, msg, STRSZ, 0);
        if(ret == -1)
            perror("send error");

        if(strcmp(msg, "END") == 0)
            break;

        bzero(msg, STRSZ);
        ret = recv(sockfd, msg, STRSZ, 0);
        if(ret == -1)
            perror("recv error");
        fprintf(stdout, "Server: %s\n", msg);
    }
    close(sockfd);
    fprintf(stdout, "Client exiting...\n");
    return 0;
}