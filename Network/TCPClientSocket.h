//============================================================================
// Name        : TCPClientSocket.h
// Created on  : Feb 04, 2015
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : TCP Client socket declaration
//============================================================================

#ifndef _TCP_CLIENT_SOCKET_INCLUDE_GUARD_H_
#define _TCP_CLIENT_SOCKET_INCLUDE_GUARD_H_

#include "TCPSocket.h"

class TCPClientSocket : protected TCPSocket
{
public:
	TCPClientSocket(void);
	~TCPClientSocket(void);

	bool Connect(const std::string& ipAddress, unsigned int port);

	int Send(const std::string& request);
	std::string Receive();
};

#endif /** (!_TCP_CLIENT_SOCKET_INCLUDE_GUARD_H_) **/