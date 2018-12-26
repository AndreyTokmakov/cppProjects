//============================================================================
// Name        : EthernetHeader.h
// Created on  : Apr 09, 2015
// Author      : Tokmakov Andrey
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#ifndef ETHERNETHEADER_H_
#define ETHERNETHEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>           // close()
#include <string.h>           // strcpy, memset(), and memcpy()
#include <netdb.h>            // struct addrinfo
#include <sys/types.h>        // needed for socket(), uint8_t, uint16_t
#include <sys/socket.h>       // needed for socket()
#include <netinet/in.h>       // IPPROTO_RAW, INET_ADDRSTRLEN
#include <netinet/ip.h>       // IP_MAXPACKET (which is 65535)
#include <arpa/inet.h>        // inet_pton() and inet_ntop()
#include <sys/ioctl.h>        // macro ioctl is defined
#include <bits/ioctls.h>      // defines values for argument "request" of ioctl.
#include <net/if.h>           // struct ifreq
#include <linux/if_ether.h>   // ETH_P_ARP = 0x0806
#include <linux/if_packet.h>  // struct sockaddr_ll (see man 7 packet)
#include <net/ethernet.h>
#include <errno.h>            // errno, perror()
#include <iostream>

/** EthernetHeader class: **/
class EthernetHeader
{
public:
	unsigned char destMac[6];
	unsigned char sourceMac[6];
	unsigned char type[2];

public:
	EthernetHeader();
	//virtual ~EthernetHeader();

public:
	bool SetSourceMACAddress(const std::string& mac);
	bool SetSourceMACAddress(unsigned char* mac) ;
	bool SetDestinationMACAddress(const std::string& mac);

	void PrintSourceMACAddres(void);
	void PrintDestinationMACAddress(void);

    bool CompareMacs(const char* s, unsigned char* d);
	bool CompareSourceMac(const std::string& mac);
	bool CompareDestMac(const std::string& mac);
	
	bool CompareSourceMacFast(const unsigned char* mac);
	bool CompareDestMacFast(const unsigned char* mac);
	
	void SetType(unsigned short packetType);
	unsigned short GetType();
	
	std::string GetSourceMACAddress(void) const;
	std::string DestinationMACAddress(void) const;

protected:
	bool SetMACAddress(const char* s, unsigned char* d);
	void PrintMACAddres(unsigned char* mac);
} __attribute__((packed, aligned(1)));

#endif /* ETHERNETHEADER_H_ */
