//============================================================================
// Name        : UDPHeader.h
// Created on  : May 19, 2015
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : UDP Header class declaration
//============================================================================

#ifndef UDP_HEADER__H_
#define UDP_HEADER__H_

#include <arpa/inet.h>

/** UDPPseudoHeader class declaration: **/
class UDPPseudoHeader {
public:
	unsigned int   sourceAddress;
	unsigned int   destinationAddress;
	unsigned char  useless;
	unsigned char  protocol;
	unsigned short totalLength;
};

/** UDPHeader class declaration: **/
class UDPHeader
{
private:
	/** Source port: **/
	/** The 16-bit port number of the process that originated the UDP message on the source device.         **/
	/** This will normally be an ephemeral (client) port number for a request sent by a client to a server, **/ 
	/** or a well-known/registered (server) port number for a reply sent by a server to a client            **/
	unsigned short sourcePort;
	/** Destination port: **/
	/** The 16-bit port number of the process that is the ultimate intended recipient of the message on the destination device.  **/
	/** This will usually be a well-known/registered (server) port number for a client request, or an ephemeral (client) port    **/
	/** number for a server reply                                                                                                **/
	unsigned short destinationPort;
	/** Length:  **/
	/** The length of the entire UDP datagram, including both header and Data fields.  **/
	unsigned short length;
	/** Checksum: **/
	/** An optional 16-bit checksum computed over the entire UDP datagram plus a special “pseudo header” of fields. See below for more information.**/
	unsigned short checksum;
	/** Data: The encapsulated higher-layer message to be sent.**/
	//char data[MTU]; 
	
public:
	UDPHeader(void);
	~UDPHeader(void);

public:
	unsigned short GetSourcePort(void) const;
	void SetSourcePort(unsigned short port);

	unsigned short GetDestinationPort(void) const;
	void SetDestinationPort(unsigned short port);
	
	unsigned short GetPacketLength(void) const;
	void SetPacketLength(unsigned short len);
	
	unsigned short GetChecksum(void) const;
	void SetChecksum(unsigned short chsm);
} __attribute__((packed, aligned(1))) ;

#endif // !(UDP_HEADER__H_)