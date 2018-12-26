//============================================================================
// Name        : UDPHeader.h
// Created on  : Jan 22, 2015
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : UDP Socket class declaration
//============================================================================

#ifndef _UDP_SOCKET_INCLUDE_GUARD_H_
#define _UDP_SOCKET_INCLUDE_GUARD_H_

#include "Socket.h"
#include <exception>

#define MAX_RCV_BUFF_SIZE 16384

class UDPSocket : public Socket
{
public:
	int SendTo(const char* sendData,
			   int dataLength,
			   const struct sockaddr *srvAddr,
			   socklen_t tolen);
	int SendTo(const std::string& ipAddress, 
               unsigned int port,
			   const std::string& data);
	int ReceiveFrom(char* recvData, 
					int dataLength,
					struct sockaddr *clientAddr,
					socklen_t *fromlen);
public:
	UDPSocket(void);
	~UDPSocket(void);
};

#endif /** !_UDP_SOCKET_INCLUDE_GUARD_H_ **/