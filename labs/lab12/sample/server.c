#include "common.h"

#define BACKLOG 5

/****************************/
// IMPORTANT: ERROR CHECK ALL SOCKET APIs
/****************************/
int main(int argc, char *argv[]) {
    int listen_fd, conn_fd;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0); // create listening socket
    if(listen_fd == -1)
        perror("socket error");

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen to any of the network interface (INADDR_ANY)
    servaddr.sin_port = htons(PORT); // Port number

    int ret = bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)); // bind address, port to socket
    if(ret == -1)
        perror("bind error");

    ret = listen(listen_fd, BACKLOG); // listen on the listen_fd
    if(ret == -1)
        perror("listen error");

    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    conn_fd = accept(listen_fd, (struct sockaddr *) &clientaddr, &clientaddr_len); // accept a request from a client
    if(conn_fd == -1)
        perror("accept error");

    // Server receiving packet from client
    char recvdata[PACKETSZ];
    memset(recvdata, 0, PACKETSZ);
    ret = recv(conn_fd, recvdata, PACKETSZ, 0); // receive data from client
    if(ret == -1)
        perror("recv error");    
    Packet *recvpacket = deserializeData(recvdata);
    fprintf(stdout, "Server received operation %d with value %d and message %s from client\n", ntohs(recvpacket->operation), ntohs(recvpacket->val1), recvpacket->val2);

    // Send ack packet to client
    Packet packet = {htons(PROTO_ACK), htons(ntohs(recvpacket->val1) * 5), "Message 2"};
    char *serializedData = serializePacket(&packet);
    ret = send(conn_fd, serializedData, PACKETSZ, 0); // send message to client
    if(ret == -1)
        perror("send error");

    close(conn_fd); // close sockets
    close(listen_fd);
    fprintf(stdout, "Server exiting...\n");
    return 0;
}
