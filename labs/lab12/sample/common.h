#ifndef COMMON_H_
#define COMMON_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 3000
#define STRSZ 10

// Protocol operations
#define PROTO_M1 0
#define PROTO_ACK 1

// Packet structure
struct Packet_Structure {
    int operation;
    int val1;
    char val2[STRSZ];
};

typedef struct Packet_Structure Packet;

const int PACKETSZ = sizeof(Packet);

// serialize packet
char *serializePacket(Packet *packet){
    char *serializedData = (char *)malloc(sizeof(char) * PACKETSZ);
    memset(serializedData, 0, PACKETSZ);
    memcpy(serializedData, packet, PACKETSZ);
    return serializedData;
}

// deserialize data
Packet *deserializeData(char *serializedData){
    Packet *packet = (Packet *)malloc(sizeof(Packet));
    memset(packet, 0, PACKETSZ);
    memcpy(packet, serializedData, PACKETSZ);
    return packet;
}

#endif