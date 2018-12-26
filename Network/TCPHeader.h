//============================================================================
// Name        : TCPHeader.h
// Created on  : Dec 04, 2014
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : TCP Header class declaration
//============================================================================

#ifndef TCPHEADER_H_
#define TCPHEADER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <errno.h>
#include <string.h>

/** PseudoTCPHeader class declaration: **/
class PseudoTCPHeader
{
public:
	unsigned int   sourceAddress;
	unsigned int   destinationAddress;
	unsigned char  useless;
	unsigned char  protocol;
	unsigned short totalLength;
} __attribute__((packed, aligned(1)));

class TCPHeader
{
public:
	/** Source port: **/
	unsigned short sourcePort;
	/** Destination port: **/
	unsigned short destinationPort;
	/** Sequence number: **/
	unsigned int   sequence;
	/** Acknowledgement number: **/
	unsigned int   acknowledge;
	/** : **/
	unsigned char  reserved_part1:4;
	/** This indicates where the data begins: **/
	unsigned char  dataOffset:4;
    /** Unsigned char  flags: **/
	unsigned char  FYN :1;
	/** : **/
	unsigned char  SYN :1;
	/** Reset Flag: **/
	unsigned char  RST :1;
	/** Push Flag: **/
	unsigned char  PSH :1;
	/** Acknowledgement Flag: **/
	unsigned char  ACK :1;
	/** Urgent Flag: **/
	unsigned char  URG :1;
	/** : **/
	unsigned char  reserved2:2;
	/** Window: **/
	unsigned short window;
	/** Checksum: **/
	unsigned short checksum; //
	/** Urgent pointer: **/
	unsigned short urgent_pointer; //

public:
	TCPHeader(void);
	~TCPHeader(void);

public:
	unsigned short GetChecksum(void);
	void SetChecksum(unsigned short chsm);

	unsigned short GetDataOffset(void) const;
	void SetDataOffset(unsigned short offset);

	unsigned short GetSourcePort(void);
	void SetSourcePort(unsigned short port);

	unsigned short GetDestinationPort(void);
	void SetDestinationPort(unsigned short port);

	unsigned short GetWindow(void);
	void SetWindow(unsigned short wnd);

	unsigned int GetAcknowledgeSeqNum(void);
	void SetAcknowledgeSeqNum(unsigned int ackSeq);

	unsigned int GetSequenceNum(void);
	void SetSequenceNum(unsigned int seq);

	bool GetFlag_SYN(void);
	void SetFlag_SYN(bool state);

	bool GetFlag_ACK(void);
	void SetFlag_ACK(bool state);

	bool GetFlag_FYN(void);
	void SetFlag_FYN(bool state);

	bool GetFlag_RST(void);
	void SetFlag_RST(bool state);

	bool GetFlag_PSH(void);
	void SetFlag_PSH(bool state);

	bool GetFlag_URG(void);
	void SetFlag_URG(bool state);

	unsigned short GetUrgentPointer(void);
	void SetUrgentPointer(unsigned short urgPtr);
} __attribute__((packed, aligned(1))) ;

#endif /* TCPHEADER_H_ */
