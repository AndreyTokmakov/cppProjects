//============================================================================
// Name        : TCPServerSocket.cpp
// Created on  : Feb 05, 2015
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : TCP server socket class definition
//============================================================================

#include "TCPServerSocket.h"

TCPServerSocket::TCPServerSocket(void) {
}

TCPServerSocket::~TCPServerSocket(void) {
}

bool TCPServerSocket::Bind(const std::string& ipAddress, 
						   unsigned int port) {
	return TCPSocket::Bind(ipAddress, port);
}

bool TCPServerSocket::Listen(int backlog) {
	return TCPSocket::Listen(backlog);
}
