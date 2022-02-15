#pragma once

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

typedef struct packetPositions
{
    int auth;
    float posX;
    float posY;
} packetPositions_t;

void InitializeSocket();
void UpdatePositionsWithServer(float X, float Y);