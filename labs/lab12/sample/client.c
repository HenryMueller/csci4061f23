#include "common.h"

/****************************/
// IMPORTANT: ERROR CHECK ALL SOCKET APIs
/****************************/

int main(int argc, char *argv[]) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // create socket to establish connection
    if(sockfd == -1)
        perror("socket error");

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // server IP, since the server is on same machine, use localhost IP
    servaddr.sin_port = htons(PORT); // Port the server is listening on

    int ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)); // establish connection to server
    if(ret == -1)
        perror("connect error");

    // Packet to send to server
    Packet packet = {htons(PROTO_M1), htons(123), "Message 1"}; // endianess of messages
    char *serializedData = serializePacket(&packet);
    ret = send(sockfd, serializedData, PACKETSZ, 0); // send message to server
    if(ret == -1)
        perror("send error");

    // Receive acknowledgment packet from server
    char recvdata[PACKETSZ];
    memset(recvdata, 0, PACKETSZ);
    ret = recv(sockfd, recvdata, PACKETSZ, 0); // receive data from server
    if(ret == -1)
        perror("recv error");
    Packet *ackpacket = deserializeData(recvdata);
    fprintf(stdout, "Client received ack %d with value %d and message %s from server\n", ntohs(ackpacket->operation), ntohs(ackpacket->val1), ackpacket->val2);
    
    close(sockfd); // close socket
    fprintf(stdout, "Client exiting...\n");
    return 0;
}