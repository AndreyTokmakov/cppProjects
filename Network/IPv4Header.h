//============================================================================
// Name        : IPv4Header.h
// Created on  : Dec 4, 2014
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : IP Version 4 Header declaration
//============================================================================

#ifndef IPHEADER_H_
#define IPHEADER_H_

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

class IPv4Header
{
public:
	/** 4-bit header length (in 32-bit words) normally=5 (Means 20 Bytes may be 24 also): **/
	unsigned char ipHeaderLength:4;
	/** 4-bit IPv4 version: **/
	unsigned char ipVersion :4;
	/** IP type of service: **/
	unsigned char serviceType;
	/** Packet total length. Payload data size included: **/
	unsigned short packetLength;
	/** Unique packet identifier: **/
	unsigned short packetId;
	/** Fragment offset fields: **/
	unsigned char  frag_offset :5;
	unsigned char  more_fragment :1;
	unsigned char  dont_fragment :1;
	unsigned char  reserved_zero :1;
	/** Fragment offset. **/
	unsigned char  frag_offset1;
	/** Time to live: (TTL) **/
	unsigned char  timeToLive;
	/** Protocol(TCP,UDP etc): **/
	unsigned char  protocol;
	/** IP checksum: **/
	unsigned short checksum;
	/** Source address: **/
	unsigned int  srcaddr;
	/** Dext address: **/
	unsigned int  destaddr;

public:
	unsigned short GetIPVersion(void);
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

	unsigned int GetSourceAddressAsInt() const;
	std::string GetSourceAddress() const;
	void SetSourceAddress(const std::string &address);
	void SetSourceAddress(const sockaddr_in &address);

	std::string GetDestAddress() const;
	unsigned int GetDestAddressAsInt() const;
	void SetDestAddress(const std::string &address);
	void SetDestAddress(const sockaddr_in &address);

public:
	IPv4Header(void);
	~IPv4Header(void);

private:
	std::string ResolveAddress(unsigned long address) const;
} __attribute__((packed, aligned(1)));

#endif /* IPHEADER_H_ */
