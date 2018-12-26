//============================================================================
// Name        : TCPClientSocket.cpp
// Created on  : Feb 04, 2015
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : TCP Client socket class definition
//============================================================================

#include "TCPClientSocket.h"

TCPClientSocket::TCPClientSocket(void)
{
}

TCPClientSocket::~TCPClientSocket(void)
{
}

bool TCPClientSocket::Connect(const std::string& ipAddress, 
									   unsigned int port) {
	return TCPSocket::Connect(ipAddress, port);
}

int TCPClientSocket::Send(const std::string& request)
{
	return TCPSocket::Send(request, 0);
}

std::string TCPClientSocket::Receive()
{
	return TCPSocket::Receive(0);
}