//============================================================================
// Name        : Socket.h
// Created on  : Jun 30, 2017
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Socket class definition
//============================================================================

#ifndef _SOCKETS___H_
#define _SOCKETS___H_

#include <iostream>
#include <string.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>

#include "../exception/Exception.h"

#define INVALID_SOCKET -1
#define SOCKET_ERROR   -1

/** Socket class declaration: **/
class Socket {
protected:
	/** Socket handle: **/
    int _hSocket;

public:
	/** Socket class default constructor: **/
	Socket(void);
	/** Socket class destructor: **/
	virtual ~Socket(void);
	
protected:
	/** Socket class constructor: **/
	Socket(int sock);

public:
	virtual int GetHandle(void) const;
	/* 
	Function:    Select()
	Description: The select function determines the status of one or more sockets, waiting if necessary, to perform synchronous I/O
	Parameters:  readfds   - An optional pointer to a set of sockets to be checked for readability.
				 writefds  - An optional pointer to a set of sockets to be checked for writability.
				 exceptfds - An optional pointer to a set of sockets to be checked for errors.
				 timeout   - The maximum time for select to wait, provided in the form of a TIMEVAL structure. 
				 Set the timeout parameter to null for blocking operations.
	Return:      The select function returns the total number of socket handles that are ready and contained in the fd_set structures,
	             zero if the time limit expired, or SOCKET_ERROR if an error occurred. If the return value is SOCKET_ERROR */ 
	virtual int Select(fd_set *readfds,
					   fd_set *writefds,
					   fd_set *exceptfds,
					   timeval *timeout);
	/* 
	Function:    Accept()
	Description: The accept function permits an incoming connection attempt on a socket.
	Parameters:  addr    - An optional pointer to a buffer that receives the address of the connecting entity, as known
	             to the communications layer. The exact format of the addr parameter is determined by the
				 address family that was established when the socket from the sockaddr structure was created.
	             addrlen - An optional pointer to an integer that contains the length of structure pointed to by the addr parameter.
	Return:      If no error occurs, accept returns a value of type SOCKET that is a descriptor for the new socket.
	             This returned value is a handle for the socket on which the actual connection is made.
				 Otherwise, a value of INVALID_SOCKET is returned */ 
	virtual Socket* Accept(sockaddr *addr,
						   socklen_t *addrlen) throw (Exception);
	/* 
	Function:    Bind()
	Description: The bind function associates a local address with a socket.
	Parameters:  name    - A pointer to a sockaddr structure of the local address to assign to the bound socket .
	             namelen - The length, in bytes, of the value pointed to by the name parameter.
	Return:      If no error occurs, bind returns zero. Otherwise, it returns SOCKET_ERROR */ 
	virtual int Bind(const sockaddr *name, 
					 int namelen);
					 
	/* 
	Function:    Bind()
	Description: The bind function associates a local address with a socket.
	Parameters:  ipAddress - Server IP addresses string
	             port      - Server port
	Return:      If no error occurs, bind returns zero. Otherwise, it returns SOCKET_ERROR */ 
	virtual bool Bind(CString ipAddress, 
					  unsigned short port);					 
					 
	/* 
	Function:    Listen()
	Description: Function places a socket in a state in which it is listening for an incoming connection. 
	Parameters:  backlog - The maximum length of the queue of pending connections. 
	             If set to SOMAXCONN, the underlying service provider responsible for socket s will 
				 set the backlog to a maximum reasonable value. There is no standard provision to obtain the actual backlog value.
	Return:      If no error occurs, listen returns zero. Otherwise, a value of SOCKET_ERROR is returned */ 
	virtual bool Listen(int backlog = 0);
	
	/* 
	Function:    Create()
	Description: Creates a socket that is bound to a specific transport service provide
	Parameters:  family   - The address family specification (Default = SOCK_FAMILY_INET)
	             type     - The type specification for the new socket (Default = SOCK_TYPE_STREAM)
				 protocol - The protocol to be used. (Default = SOCK_PROTOCOL_IP)
	Return:      If no error occurs, returns true. Otherwise, it returns false */
    virtual bool Create(int family = PF_INET,
						int type = SOCK_STREAM,
						int protocol = IPPROTO_IP);
	/* 
	Function:    Connect()
	Description: Establishes a connection to a specified socket
	Parameters:  name    - A pointer to the sockaddr structure to which the connection should be established
	             namelen - The length, in bytes, of the sockaddr structure pointed to by the name parameter.
	Return:      If no error occurs, Connect() returns zero. Otherwise, it returns SOCKET_ERROR */
	virtual int Connect(const sockaddr* address,
						int namelen);
	/*
	Function:    Create()
	Description: Establishes a connection to a specified socket
	Parameters:  ipAddress - Server IP addresses string
	             port      - Server port
	Return:      If no error occurs, Connect() returns TRUE. Otherwise, it returns FALSE */
	virtual bool Connect(CString ipAddress, 
						 unsigned int port);
	/* 
	SendTo()
	Description: Sends data to a specific destination.
	Parameters:  sendData   - A pointer to a buffer containing the data to be transmitted.
		         dataLength - The length, in bytes, of the data in buffer pointed to by the buf parameter..
			     flags      - A set of flags that specify the way in which the call is made. This parameter 
				              is constructed by using the bitwise OR operator with any of the following values. 
                 srvAddr    - An optional pointer to a sockaddr structure that contains the address of the target socket
				 tolen      - The size, in bytes, of the address pointed to by the to parameter
	Return:      If no error occurs, Send() returns the total number of bytes sent, which can be less than the number
	             requested to be sent in the len parameter. Otherwise, a value of SOCKET_ERROR is returned. */
	virtual int SendTo(const char* sendData,
					   int dataLength, 
				   	   int flags,
					   const sockaddr *srvAddr,
					   socklen_t tolen);
	/* 
	Send()
	Description: TSends data on a connected socket.
	Parameters:  sendData   - A pointer to a buffer containing the data to be transmitted.
		         dataLength - The length, in bytes, of the data in buffer pointed to by the buf parameter..
			     flags      - A set of flags that specify the way in which the call is made. This parameter 
				              is constructed by using the bitwise OR operator with any of the following values. 
	Return:      If no error occurs, Send() returns the total number of bytes sent, which can be less than the number
	             requested to be sent in the len parameter. Otherwise, a value of SOCKET_ERROR is returned. */
	virtual int Send(char* sendData,
					int dataLength, 
					int flags);
	/* 
	Send()
	Description: TSends data on a connected socket.
	Parameters:  buffer   - A standard C++ string with data to send.
			     flags    - A set of flags that specify the way in which the call is made. This parameter 
				           is constructed by using the bitwise OR operator with any of the following values. 
	Return:      If no error occurs, Send() returns the total number of bytes sent, which can be less than the number
	             requested to be sent in the len parameter. Otherwise, a value of SOCKET_ERROR is returned. */
	virtual int Send(CString buffer, 
					int flags = 0);	
	/* 
	Function:    ReceiveFrom()
	Description: Receives data from a connected socket or a bound connectionless socket.
	Parameters:  recvData   - [out] A pointer to the buffer to receive the incoming data.
		         dataLength - [in]  The length, in bytes, of the buffer pointed to by the buf parameter.
			     flags      - [in]  A set of flags that influences the behavior of this function. 
				 clientAddr - [out] An optional pointer to a buffer in a sockaddr structure that will hold the source address upon return.
				 fromlen    - [in] [out] An optional pointer to the size, in bytes, of the buffer pointed to by the from parameter.
	Return:      If no error occurs, Receive() returns zero. Otherwise, a value of SOCKET_ERROR is returned. */
	virtual int ReceiveFrom(char* recvData, 
							int dataLength,
							int flags,
							sockaddr *clientAddr,
							socklen_t *fromlen);
	/* 
	Function:    Receive()
	Description: Receives data from a connected socket or a bound connectionless socket.
	Parameters:  recvData   - [out] A pointer to the buffer to receive the incoming data.
		         dataLength - [in]  The length, in bytes, of the buffer pointed to by the buf parameter.
			     flags      - [in]  A set of flags that influences the behavior of this function. 
	Return:      If no error occurs, Receive() returns zero. Otherwise, a value of SOCKET_ERROR is returned. */
	virtual int Receive(char* recvData, 
						int dataLength,
						int flags);
	/* 
	Shutdown():
	Description: The shutdown function disables sends or receives on a socket
	Parameters:  type - A flag that describes what types of operation will no longer be allowed.
	Return:      If no error occurs, Shutdown() returns zero. Otherwise, a value of SOCKET_ERROR is returned. */
	virtual int Shutdown(int type = 2);
	/* 
	Close() 
	Description: Closes an existing socket
	Return: If no error occurs, Close() returns zero. Otherwise, a value of SOCKET_ERROR is returned. */
	virtual int Close();
	/* 
	GetLastError() 
	Description: Retrieves the calling thread's last-error code value. 
	             The last-error code is maintained on a per-thread basis. 
				 Multiple threads do not overwrite each other's last-error code
	Return: The return value is the calling thread's last-error code. */
	virtual int GetLastError();
};

#endif /** !_SOCKETS___H_ **/