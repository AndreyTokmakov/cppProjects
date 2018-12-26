//============================================================================
// Name        : TCPSocket.h
// Created on  : Feb 03, 2017
// Author      : Tokmakov 2015
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : TCPSocket class definition
//============================================================================

#ifndef _TCP_SOCKET_INCLUDE_GUARD_H_
#define _TCP_SOCKET_INCLUDE_GUARD_H_

#include "Socket.h"

/** TCPSocket class declaration: **/
class TCPSocket : public Socket {
public:
	TCPSocket(void) throw (Exception);
	virtual ~TCPSocket(void);

protected:
	TCPSocket(const Socket* socket);

public:
	/* 
	Function:    Accept()
	Description: The accept function permits an incoming connection attempt on a socket.
	Parameters:  addr    - An optional pointer to a buffer that receives the address of the connecting entity, as known
	             to the communications layer. The exact format of the addr parameter is determined by the
				 address family that was established when the socket from the sockaddr structure was created.
	             addrlen - An optional pointer to an integer that contains the length of structure pointed to by the addr parameter.
	Return:      If no error occurs, accept returns the TCPSocket class object pointed of the connected socket. 
                 In case of error the Exception raised. */ 
	TCPSocket* Accept(sockaddr *addr, socklen_t *addrlen) throw (Exception);
	
	/* 
	Send()
	Description: TSends data on a connected socket.
	Parameters:  request    - Send data string.
			     flags      - A set of flags that specify the way in which the call is made. This parameter 
				              is constructed by using the bitwise OR operator with any of the following values. 
	Return:      If no error occurs, Send() returns the total number of bytes sent, which can be less than the number
	             requested to be sent in the len parameter. Otherwise, a value of SOCKET_ERROR is returned. */	
	int Send(CString request, int flags = 0);
	
	/* 
	Function:    Receive()
	Description: Receives data from a connected socket or a bound connectionless socket.
	Parameters:  flags - [input]  A set of flags that influences the behavior of this function. 
	Return:      If no error occurs, Receive() returns the received date, othewise the Exception raised. */ 
	String Receive(int flags = 0) throw (Exception);
};

#endif /** !_TCP_SOCKET_INCLUDE_GUARD_H_ **/