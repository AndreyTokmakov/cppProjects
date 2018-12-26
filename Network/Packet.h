//============================================================================
// Name        : Packet.h
// Created on  : Jul 3, 2015
// Author      : Tokmakov Andrey
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#ifndef _PACKET_INCLUDE_GUARD__H_
#define _PACKET_INCLUDE_GUARD__H_

#include "EthernetHeader.h"
#include "IPv4Header.h"
#include "UDPHeader.h"
#include "ICMPHeader.h"
#include "TCPHeader.h"


//============================================================================
//                  EthernetPacket class declaration: 
//============================================================================

class EthernetPacket
{
public:
    EthernetHeader ethernetHeader;

public:
    EthernetPacket(void);
    EthernetPacket(const std::string &sourceMac,
				   const std::string &destMack,
				   unsigned int protocol);

    ~EthernetPacket(void);

public:
	bool SetSourceMACAddress(const std::string& mac);
	bool SetSourceMACAddress(unsigned char* mac) ;
	bool SetDestinationMACAddress(const std::string& mac);

	void PrintSourceMACAddres(void);
	void PrintDestinationMACAddress(void);
    
    bool CompareSourceMac(const std::string& mac);
	bool CompareDestMac(const std::string& mac);
	
	void SetType(unsigned short packetType);
	unsigned short GetType();
	
	void SetEthernetHeader(EthernetHeader* ethernetHeader);

protected:
    unsigned short Checksum(unsigned short *ptr, int nbytes);
} __attribute__((packed, aligned(1)));

//============================================================================
//                  IPPacket class declaration: 
//============================================================================

class IPPacket: public EthernetPacket
{
protected:
    IPv4Header ipHeader;

public:
    IPPacket(void);

    IPPacket(const std::string &sourceMac,
			 const std::string &destMack,
             unsigned short protocol,
		     unsigned short packetLength,
			 const std::string& sourceAddress,
			 const std::string& destAddress,
             unsigned short packetId,
             unsigned short serviceType = 0,
			 unsigned short ttl = 128,
			 unsigned short version = 4);
    
    ~IPPacket(void);

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

	std::string GetSourceAddress() const;
	void SetSourceAddress(const std::string &address);
	void SetSourceAddress(const sockaddr_in &address);

	std::string GetDestAddress() const;
	void SetDestAddress(const std::string &address);
	void SetDestAddress(const sockaddr_in &address);
	
	void SetIPHeader(IPv4Header* ipHeader);

protected:
    unsigned short Checksum(unsigned short *ptr, int nbytes);
} __attribute__((packed, aligned(1)));

//============================================================================
//                  ICMPPacket class declaration: 
//============================================================================

class ICMPPacket: public IPPacket
{
protected:
    ICMPHeader icmpHeader;
	/** Data: The encapsulated higher-layer message to be sent.**/
	char payload[1024]; 
	
public:
    ICMPPacket(void);
    ICMPPacket(const std::string &sourceMac,
			   const std::string &destMac,
			   const std::string &sourceAddress,
			   const std::string &destAddress,
			   unsigned short packetId,
			   ICMPType icmpType,
			   unsigned short icmpCode,
			   unsigned short seq,
			   unsigned short id,
			   const unsigned char* icmpPayload = (const unsigned char*)"",
			   unsigned short payloadLength = 0,
			   unsigned short ttl = 128,
			   unsigned short typeOfService = 0);
    
    ~ICMPPacket(void);	
	
protected:
    unsigned short CalcChecksum(const ICMPHeader* icmpHeader,
			                    unsigned const char* icmpPayload,
							    unsigned short payloadLength);
} __attribute__((packed, aligned(1)));

//============================================================================
//                  UDPPacket class declaration: 
//============================================================================

class UDPPacket: public IPPacket
{
protected:
    UDPHeader udpHeader;
	/** Data: The encapsulated higher-layer message to be sent.**/
	char payload[10240];
	
public:
    UDPPacket(void);
    UDPPacket(const std::string &sourceMac,
			  const std::string &destMac,
			  const std::string &sourceAddress,
			  unsigned short sourcePort,
			  const std::string &destAddress,
			  unsigned short destPort,
			  unsigned short packetId,
			  const unsigned char* udpPayload = (const unsigned char*)"",
			  unsigned short payloadLength = 0,
			  unsigned short ttl = 128,
			  unsigned short typeOfService = 0);
    
    ~UDPPacket(void);	
	
	void SetUDPHeader(const char* buffer);
	
	std::string GetUDPData(void);
	void ChecksumRecalculate();
	
	unsigned short GetSourcePort(void) const;
	void SetSourcePort(unsigned short port);
	
	unsigned short GetDestinationPort(void) const;
	void SetDestinationPort(unsigned short port);

protected:
    unsigned short CalcChecksum(const UDPHeader* udpHeader,
			                    unsigned const char* payload,
							    unsigned short payloadLen);
} __attribute__((packed, aligned(1)));

//============================================================================
//                  TCPPacket class declaration: 
//============================================================================

class TCPPacket: public IPPacket
{
protected:
    TCPHeader tcpHeader;
public:
    char  tcpOptsPayload[1536];
	
public:
    TCPPacket(void);
    TCPPacket(const std::string &sourceMac,
			  const std::string &destMack,
			  const std::string &sourceAddress,
			  unsigned short sourcePort,
			  const std::string &destAddress,
			  unsigned short destPort,
			  unsigned int sequence,
			  unsigned int acknowledge,
			  unsigned short packetId,
			  unsigned short ttl = 128,
			  unsigned short window = 8192,
			  unsigned short typeOfService = 0,
			  bool SYN = true,
			  bool ACK = false,
			  bool FIN = false,
			  bool PSH = false,
			  bool RST = false,
			  const unsigned char* tcpOptions = (const unsigned char*)"",
			  unsigned short tcpOptsLength = 0,
			  const unsigned char* tcpData = (const unsigned char*)"",
			  unsigned short tcpDataLength = 0);
    
    ~TCPPacket(void);

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
	
	void SetTCPHeader(TCPHeader* tcpHeader);
	void SetTCPHeader(const char* tcpBufferPtr);
	
	unsigned short GetTCPDataLength(void);
	unsigned short GetTCPOptionsLength(void);
	
	void ChecksumRecalculate(void);	
	
public:
    void Configure(const std::string &sourceMac,
				   const std::string &destMack,
				   const std::string &sourceAddress,
			  	   unsigned short sourcePort,
			  	   const std::string &destAddress,
			  	   unsigned short destPort,
			  	   unsigned int sequence,
			  	   unsigned int acknowledge,
			  	   unsigned short packetId,
			  	   unsigned short ttl = 128,
			  	   unsigned short window = 8192,
			  	   unsigned short typeOfService = 0,
			  	   bool SYN = true,
			  	   bool ACK = false,
			  	   bool FIN = false,
			  	   bool PSH = false,
				   bool RST = false,
			  	   const unsigned char* tcpOptions = (const unsigned char*)"",
			  	   unsigned short tcpOptsLength = 0,
			  	   const unsigned char* tcpData = (const unsigned char*)"",
			  	   unsigned short tcpDataLength = 0);
				   
	std::string GetTCPData();
	std::string GetTCPOptions();
	
protected:
    unsigned short CalcChecksum(const IPv4Header* ipHeader,
			                    const TCPHeader* tcpHeader,
			                    const unsigned char* tcpOptions,
					            const unsigned char* tcpData,
							    unsigned short tcpDataLength);
	unsigned short CalcChecksumEx();
} __attribute__((packed, aligned(1)));

#endif /** !_PACKET_INCLUDE_GUARD__H_ **/