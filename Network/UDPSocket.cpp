//============================================================================
// Name        : UDPHeader.cpp
// Created on  : Jan 22, 2015
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : UDP Socket class definitions
//============================================================================

#include "UDPSocket.h"

UDPSocket::UDPSocket(void) {

	if (false == this->Create(PF_INET, SOCK_DGRAM, IPPROTO_UDP)){
		throw std::exception();
	}
	//memset(responseBuffer, 0, MAX_RCV_BUFF_SIZE);
}

UDPSocket::~UDPSocket(void)
{
	//std::cout << __FUNCTION__ << std::endl;
	this->Close();

#ifdef _WIN32
	WSACleanup();
#endif
}

int UDPSocket::SendTo(const char* sendData,
				      int dataLength,
				      const struct sockaddr *srvAddr,
					  socklen_t tolen)
{
	return Socket::SendTo(sendData, dataLength, 0, srvAddr, tolen); 
}

int UDPSocket::SendTo(const std::string& ipAddress, 
                       unsigned int port,
					   const std::string& data)
{
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	
	socklen_t tolen = sizeof(server);
	return Socket::SendTo(data.c_str(), data.length(), 0, (sockaddr*)&server, tolen); 
}

int UDPSocket::ReceiveFrom(char* recvData, 
						   int dataLength,
						   struct sockaddr *clientAddr,
						   socklen_t *fromlen)
{
	return Socket::ReceiveFrom(recvData, dataLength, 0, clientAddr, fromlen);
}	