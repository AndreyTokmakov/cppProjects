//============================================================================
// Name        : ICMPHeader.h
// Created on  : May 19, 2015
// Author      : Tokmakov Andrey
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#ifndef ICMP_HEADER__H_
#define ICMP_HEADER__H_

#include <arpa/inet.h>

enum ICMPType {
	ICMP_EchoReply = 0,
	ICMP_DestinationUnreachable = 3,
	ICMP_EchoRequest = 8,
	ICMP_RouterAdvertisemen = 9,
	ICMP_RouterSolicitation = 10,
	ICMP_TimestampRequest = 13,
	ICMP_TimestampReply = 14,
	ICMP_InformationRequest = 15
};

/** ICMPHeader class declaration: **/
class ICMPHeader
{
private:
	/** Type: Identifies the ICMP message type.                                                               **/
	/** For ICMPv6, values from 0 to 127 are error messages and values 128 to 255 are informational messages. **/
	unsigned char  type;
	/** Code: Identifies the “subtype” of message within each ICMP message Type value. **/
	/** Thus, up to 256 “subtypes” can be defined for each message type.               **/	
	unsigned char  code;
	/** Checksum: **/
	/** It provides error detection coverage for the entire ICMP message.  **/
	unsigned short checksum;
	/** Identifier: **/
	unsigned short identifier;
	/** Sequence: **/
	unsigned short sequence;
	
public:
	ICMPHeader(void);
	~ICMPHeader(void);

public:
	unsigned short GetType(void) const;
	void SetType(unsigned short type);

	unsigned short GetCode(void) const;
	void SetCode(unsigned short code);
	
	unsigned short GetChecksum(void) const;
	void SetChecksum(unsigned short chsm);
	
	unsigned short GetIdentifier(void) const;
	void SetIdentifier(unsigned short id);
	
	unsigned short GetSequence(void) const;
	void SetSequence(unsigned short seq);	
} __attribute__((packed, aligned(1)));

#endif // !(ICMP_HEADER__H_)