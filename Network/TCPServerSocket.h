//============================================================================
// Name        : TCPServerSocket.h
// Created on  : Feb 05, 2015
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : TCP server socket class declaration
//============================================================================

#ifndef _TCP_SERVER_SOCKET_INCLUDE_GUARD_H_
#define _TCP_SERVER_SOCKET_INCLUDE_GUARD_H_

#include "TCPSocket.h"

class TCPServerSocket : protected TCPSocket
{
public:
	TCPServerSocket(void);
	~TCPServerSocket(void);

	bool Bind(const std::string& ipAddress, 
			  unsigned int port);
	bool Listen(int backlog = 0);
};

#endif /** (!_TCP_SERVER_SOCKET_INCLUDE_GUARD_H_) **/