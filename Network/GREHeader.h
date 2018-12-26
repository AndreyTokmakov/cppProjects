//============================================================================
// Name        : GREHeader.h
// Created on  : Jan 25, 2015
// Author      : Tokmakov Andrey
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#ifndef __GRE_HEADER_H__
#define __GRE_HEADER_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <errno.h>
#include <string.h>

class GREHeader
{
private:
	/** **/
	char something;
	/** GRE protocol version: **/
	unsigned char version :3;
	/** GRE Flags: **/
	unsigned char flags :5;
	/** Contains the protocol type of the payload packet.  **/
	/** In general, the value will be the Ethernet protocol type field for the packet.  **/
	/** Additional values may be defined in other documents: **/
	unsigned char protocol[2];
	/** Contains the IP (one's complement) checksum of the GRE header and the payload packet: **/
	//unsigned short checksum;
	/** Indicates the byte offset from the start of the Routing field to the first byte of the active Source Route Entry to be examined: **/
	//unsigned short Offset;
	/** Contains a number which was inserted by the encapsulator.  **/
	/** It may be used by the receiver to authenticate the source of the packet: **/
	//unsigned int key;
	/** Contains a number which is inserted by the encapsulator.  **/
	/** It may be used by the receiver to establish the order in which packets have been transmitted from the encapsulator to the receiver: **/
	//unsigned int sequenceNumber;

public:

	void SetProtocol(unsigned short protocol);
	unsigned short GetProtocol();

	/*unsigned short GetIPVersion(void);
	void SetIPVersion(unsigned short version = 4);

	unsigned short GetIPHeaderLength(void);
	void SetIPHeaderLength(unsigned short len = 20);

	unsigned short GetServiceType(void);
	void SetServiceType(unsigned short tos = 16);

	unsigned short GetPacketLength(void);
	void SetPacketLength(unsigned short length);

	unsigned short GetPacketId(void);
	void SetPacketId(unsigned short id);

	unsigned short GetTimeToLive(void);
	void SetTimeToLive(unsigned short ttl = 64);

	unsigned short GetProtocol(void);
	void SetProtocol(unsigned short protocol = IPPROTO_TCP);

	unsigned short GetChecksum(void);
	void SetChecksum(unsigned short csum);

	unsigned short GetDontFragment();
	void SetDontFragment(unsigned short fragment);

	std::string GetSourceAddress() const;
	void SetSourceAddress(const std::string &address);
	void SetSourceAddress(const sockaddr_in &address);

	std::string GetDestAddress() const;
	void SetDestAddress(const std::string &address);
	void SetDestAddress(const sockaddr_in &address);
	*/
public:
	GREHeader(void);
	~GREHeader(void);

private:
	//std::string ResolveAddress(unsigned long address) const;
};

#endif /* __GRE_HEADER_H__ */


