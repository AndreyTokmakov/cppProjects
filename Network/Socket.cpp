//============================================================================
// Name        : Socket.cpp
// Created on  : Jun 30, 2017
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Socket class declaration
//============================================================================

#include "Socket.h"

/** Socket class default constructor: **/
Socket::Socket(void) : _hSocket(INVALID_SOCKET) {
}

/**
Socket class parameterized constructor: 
Description: Protected socket class constructor: **/
Socket::Socket(int sock) : _hSocket(sock) {
}

/** Socket class default destructor: **/
Socket::~Socket(void) {
	if (INVALID_SOCKET != this->_hSocket)
		::close(_hSocket);
}

/**
Function   : GetHandle()
Description: Returns the INTEGER socket handle value
Parameters : None
Return     : Value of the socket handle.   **/
int Socket::GetHandle(void) const {
	return this->_hSocket;
}

/**
Function   : Select()
Description: The select function determines the status of one or more sockets, waiting if necessary, to perform synchronous I/O
Parameters : readfds   - An optional pointer to a set of sockets to be checked for readability.
			 writefds  - An optional pointer to a set of sockets to be checked for writability.
			 exceptfds - An optional pointer to a set of sockets to be checked for errors.
			 timeout   - The maximum time for select to wait, provided in the form of a TIMEVAL structure. 
			 Set the timeout parameter to null for blocking operations.
Return     : The select function returns the total number of socket handles that are ready and contained in the fd_set structures,
	         zero if the time limit expired, or SOCKET_ERROR if an error occurred. If the return value is SOCKET_ERROR **/ 
int Socket::Select(fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout) {
	return ::select(this->_hSocket, readfds, writefds, exceptfds, timeout);
}

/**
Function   : Create()
Description: Creates a socket that is bound to a specific transport service provide
Parameters : family   - The address family specification (Default = SOCK_FAMILY_INET)
	         type     - The type specification for the new socket (Default = SOCK_TYPE_STREAM)
		     protocol - The protocol to be used. (Default = SOCK_PROTOCOL_IP)
Return     : If no error occurs, returns true. Otherwise, it returns false **/
bool Socket::Create(int family, int type, int protocol) {
	if (INVALID_SOCKET == (_hSocket = ::socket(family, type, protocol))) {
		return false;
	}
	int t = 5000;
	int err = setsockopt(_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&t, sizeof(t));
	return true;
}

/** 
Function   : Accept()
Description: The accept function permits an incoming connection attempt on a socket.
Parameters : addr    - An optional pointer to a buffer that receives the address of the connecting entity, as known
	                   to the communications layer. The exact format of the addr parameter is determined by the
	                   address family that was established when the socket from the sockaddr structure was created.
	         addrlen - An optional pointer to an integer that contains the length of structure pointed to by the addr parameter.
Return     : If no error occurs, accept returns a value of type SOCKET that is a descriptor for the new socket.
	         This returned value is a handle for the socket on which the actual connection is made.
	         Otherwise, a value of INVALID_SOCKET is returned **/ 
Socket* Socket::Accept(sockaddr *addr, socklen_t *addrlen) throw (Exception) {
	int socket = ::accept(this->_hSocket, addr, addrlen);
	if (INVALID_SOCKET == socket)
		throw Exception("Failed to accept connection", errno);
	return new Socket(socket);
}

/** 
Function   : Listen()
Description: Function places a socket in a state in which it is listening for an incoming connection. 
Parameters : backlog - The maximum length of the queue of pending connections. 
	                   If set to SOMAXCONN, the underlying service provider responsible for socket s will 
		               set the backlog to a maximum reasonable value. There is no standard provision to obtain the actual backlog value.
Return     : If no error occurs TRUE is returned. Otherwise FALSE **/
bool Socket::Listen(int backlog){
	return SOCKET_ERROR == ::listen(this->_hSocket, backlog) ? false : true;
}

/** 
Function   : Bind()
Description: The bind function associates a local address with a socket.
Parameters : name    - A pointer to a sockaddr structure of the local address to assign to the bound socket .
	         namelen - The length, in bytes, of the value pointed to by the name parameter.
Return     : If no error occurs, bind returns zero. Otherwise, it returns SOCKET_ERROR **/ 
int Socket::Bind(const sockaddr* name, int namelen) {
	return ::bind(this->_hSocket, name, namelen);
}

/**
Function   : Bind()
Description: The bind function associates a local address with a socket.
Parameters : ipAddress - Server IP addresses string
	         port      - Server port
Return     : If no error occurs, Bind() returns TRUE. Otherwise, it returns FALSE **/
bool Socket::Bind(CString ipAddress, unsigned short port) {
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	/** **/
	return (SOCKET_ERROR == Bind((sockaddr*)&server, sizeof(server))) ? false : true;
}

/** 
Function   : Connect()
Description: Establishes a connection to a specified socket
Parameters : name    - A pointer to the sockaddr structure to which the connection should be established
	         namelen - The length, in bytes, of the sockaddr structure pointed to by the name parameter.
Return     : If no error occurs, Connect() returns zero. Otherwise, it returns SOCKET_ERROR **/
int Socket::Connect(const sockaddr* address, int namelen) {
	return ::connect(this->_hSocket, address, namelen);
}

/**
Function   : Connect()
Description: Establishes a connection to a specified socket
Parameters : ipAddress - Server IP addresses string
	         port      - Server port
Return     : If no error occurs, Connect() returns TRUE. Otherwise, it returns FALSE **/
bool Socket::Connect(CString ipAddress, unsigned int port) {
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	/*** ***/
	return (SOCKET_ERROR == Connect((sockaddr*)&server, sizeof(server))) ? false : true;
}

/** 
Function   : SendTo()
Description: Sends data to a specific destination.
Parameters : sendData   - A pointer to a buffer containing the data to be transmitted.
		     dataLength - The length, in bytes, of the data in buffer pointed to by the buf parameter..
			 flags      - A set of flags that specify the way in which the call is made. This parameter 
			              is constructed by using the bitwise OR operator with any of the following values. 
			 srvAddr    - An optional pointer to a sockaddr structure that contains the address of the target socket
			 tolen      - The size, in bytes, of the address pointed to by the to parameter
Return     : If no error occurs, Send() returns the total number of bytes sent, which can be less than the number
			 requested to be sent in the len parameter. Otherwise, a value of SOCKET_ERROR is returned. **/
int Socket::SendTo(const char* sendData, int dataLength, int flags, const sockaddr *srvAddr, socklen_t tolen) {
	return ::sendto(this->_hSocket, sendData, dataLength, flags, srvAddr, tolen);
}

/** 
Function   : Send()
Description: TSends data on a connected socket.
Parameters : sendData   - A pointer to a buffer containing the data to be transmitted.
			 dataLength - The length, in bytes, of the data in buffer pointed to by the buf parameter..
			 flags      - A set of flags that specify the way in which the call is made. This parameter 
				          is constructed by using the bitwise OR operator with any of the following values. 
Return     : If no error occurs, Send() returns the total number of bytes sent, which can be less than the number
			 requested to be sent in the len parameter. Otherwise, a value of SOCKET_ERROR is returned. **/
int Socket::Send(char* sendData, int dataLength, int flags) {
	return ::send(this->_hSocket, sendData, dataLength,  flags);
}

/** 
Function   : Send()
Description: TSends data on a connected socket.
Parameters : buffer   - A standard C++ string with data to send.
			 flags    - A set of flags that specify the way in which the call is made. This parameter 
				        is constructed by using the bitwise OR operator with any of the following values. 
Return     : If no error occurs, Send() returns the total number of bytes sent, which can be less than the number
	         requested to be sent in the len parameter. Otherwise, a value of SOCKET_ERROR is returned. **/
int Socket::Send(CString buffer, int flags) {
	return Send(const_cast<char*>(buffer.c_str()), buffer.length(),flags);
}

/** 
Function   : ReceiveFrom()
Description: Receives data from a connected socket or a bound connectionless socket.
Parameters : recvData   - [out] A pointer to the buffer to receive the incoming data.
		     dataLength - [in]  The length, in bytes, of the buffer pointed to by the buf parameter.
		     flags      - [in]  A set of flags that influences the behavior of this function. 
		     clientAddr - [out] An optional pointer to a buffer in a sockaddr structure that will hold the source address upon return.
		     fromlen    - [in] [out] An optional pointer to the size, in bytes, of the buffer pointed to by the from parameter.
Return     : If no error occurs, Receive() returns zero. Otherwise, a value of SOCKET_ERROR is returned. **/
int Socket::ReceiveFrom(char* recvData, 
						int dataLength,
						int flags,
						sockaddr *clientAddr,
						socklen_t *fromlen) {
	return ::recvfrom(this->_hSocket, recvData, dataLength, flags, clientAddr, fromlen);
}

/** 
Function   : Receive()
Description: Receives data from a connected socket or a bound connectionless socket.
Parameters : recvData   - [out] A pointer to the buffer to receive the incoming data.
		     dataLength - [in]  The length, in bytes, of the buffer pointed to by the buf parameter.
			 flags      - [in]  A set of flags that influences the behavior of this function. 
Return     : If no error occurs, Receive() returns zero. Otherwise, a value of SOCKET_ERROR is returned. **/
int Socket::Receive(char* recvData, int dataLength, int flags) {
	return ::recv(this->_hSocket, recvData, dataLength, flags);
}

/** 
Function   : Shutdown():
Description: The shutdown function disables sends or receives on a socket
Parameters : type - A flag that describes what types of operation will no longer be allowed.
Return     : If no error occurs, Shutdown() returns zero. Otherwise, a value of SOCKET_ERROR is returned. **/
int Socket::Shutdown(int type) {
	return ::shutdown(this->_hSocket, type);
}

/** 
Function   : Close() 
Description: Closes an existing socket
Return     : If no error occurs, Close() returns zero. Otherwise, a value of SOCKET_ERROR is returned. **/
int Socket::Close() {
	return ::close(this->_hSocket);
}

/** 
Function   : GetLastError() 
Description: Retrieves the calling thread's last-error code value. 
	         The last-error code is maintained on a per-thread basis. 
		     Multiple threads do not overwrite each other's last-error code
Return     : The return value is the calling thread's last-error code. **/
int Socket::GetLastError() {
	return errno; 
}