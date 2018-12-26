//============================================================================
// Name        : TCPSocket.cpp
// Created on  : Feb 03, 2017
// Author      : Tokmakov 2015
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : TCPSocket class definition
//============================================================================

#include "TCPSocket.h"

TCPSocket::TCPSocket(void) throw (Exception) {
	if (false == this->Create(PF_INET, SOCK_STREAM, IPPROTO_IP)){
		throw Exception("Failed to create the TCPSocket", errno);
	}
}

TCPSocket::TCPSocket(const Socket* bSocket) : Socket(bSocket->GetHandle()) {
}

TCPSocket* TCPSocket::Accept(sockaddr *addr, socklen_t *addrlen) throw (Exception) {
	return new TCPSocket(Socket::Accept(addr, addrlen));
}

int TCPSocket::Send(CString request, int flags) {
	return Socket::Send(const_cast<char*>(request.c_str()), request.length(), flags);
}

String TCPSocket::Receive(int flags) throw (Exception) {
	int bytes = 0;
	String result = "";
	char buffer[32];
	do {
		bytes = Socket::Receive(buffer, 32, flags);
		if (SOCKET_ERROR == bytes)  {
			throw Exception("Failed to read data from socket", errno);
		}
		result.append(buffer, bytes);
	} while (32 == bytes);
	return result;
}

TCPSocket::~TCPSocket(void) {
}