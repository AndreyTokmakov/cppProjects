//============================================================================
// Name        : Packet.cpp
// Created on  : Jul 3, 2015
// Author      : Tokmakov Andrey
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include "Packet.h"

EthernetPacket::EthernetPacket(void) {
	memset(&ethernetHeader, 0, sizeof(EthernetHeader));
	ethernetHeader.SetDestinationMACAddress("00:00:00:00:00:02");
	ethernetHeader.SetSourceMACAddress("00:00:00:00:00:01");
	ethernetHeader.SetType(ETHERTYPE_IP);
}

EthernetPacket::EthernetPacket(const std::string &sourceMac,
				               const std::string &destMack,
				               unsigned int protocol)
{
	memset(&ethernetHeader, 0, sizeof(EthernetHeader));
	ethernetHeader.SetDestinationMACAddress(destMack);
	ethernetHeader.SetSourceMACAddress(sourceMac);
	ethernetHeader.SetType(protocol);
}

EthernetPacket::~EthernetPacket(void) {
}

void EthernetPacket::SetEthernetHeader(EthernetHeader* ethernetHeader) {
	memcpy(&(this->ethernetHeader), ethernetHeader, sizeof(EthernetHeader));
}

bool EthernetPacket::SetSourceMACAddress(const std::string& mac) {
    return ethernetHeader.SetSourceMACAddress(mac);
}

bool EthernetPacket::SetSourceMACAddress(unsigned char* mac) {
    return ethernetHeader.SetSourceMACAddress(mac);
}

bool EthernetPacket::SetDestinationMACAddress(const std::string& mac) {
    return ethernetHeader.SetDestinationMACAddress(mac);
}

void EthernetPacket::PrintSourceMACAddres(void) {
    ethernetHeader.PrintSourceMACAddres();
}

void EthernetPacket::PrintDestinationMACAddress(void) {
    ethernetHeader.PrintDestinationMACAddress();
}

bool EthernetPacket::CompareSourceMac(const std::string& mac) {
    return ethernetHeader.CompareSourceMac(mac);
}

bool EthernetPacket::CompareDestMac(const std::string& mac) {
    return ethernetHeader.CompareDestMac(mac);
}
	
void EthernetPacket::SetType(unsigned short packetType) {
    ethernetHeader.SetType(packetType);
}

unsigned short EthernetPacket::GetType() {
    return ethernetHeader.GetType();
}

unsigned short EthernetPacket::Checksum(unsigned short *ptr, int nbytes)
{
	register long sum = 0;
	register u_short answer, oddbyte;

	while (nbytes > 1) {
		sum += *ptr++;
		nbytes -= 2;
	}
	if (nbytes == 1) {
		oddbyte = 0;
		*((u_char *) & oddbyte) = *(u_char *) ptr;
		sum += oddbyte;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

	return (answer);
}

//============================================================================
// IPPacket class definition:
//============================================================================

IPPacket::IPPacket(void) {
}

IPPacket::IPPacket(const std::string &sourceMac,
			       const std::string &destMac,
                   unsigned short protocol,
				   unsigned short packetLength,
				   const std::string& sourceAddress,
				   const std::string& destAddress,
                   unsigned short packetId,
                   unsigned short serviceType,
				   unsigned short ttl,
				   unsigned short version): EthernetPacket(sourceMac, destMac, ETHERTYPE_IP) 
{
	memset(&ipHeader, 0, sizeof(IPv4Header));
    /** IP Header configuraton: **/
    ipHeader.SetIPHeaderLength(20);   // Since in IPv4 its size is 20
	ipHeader.SetIPVersion(version);   // Trivial
	ipHeader.SetServiceType(serviceType);
	ipHeader.SetPacketLength(packetLength);
	ipHeader.SetPacketId(packetId);
	ipHeader.SetTimeToLive(ttl);
	ipHeader.SetProtocol(protocol);
	ipHeader.SetChecksum(0);
	ipHeader.SetDontFragment(1);
	ipHeader.SetSourceAddress(sourceAddress);
	ipHeader.SetDestAddress(destAddress);
	/** Calculate the IP Header Checksum: **/
	ipHeader.SetChecksum(this->Checksum((unsigned short*)(&ipHeader), sizeof(IPv4Header)));
}

IPPacket::~IPPacket(void) {
}

void IPPacket::SetIPHeader(IPv4Header* ipHeader) {
	memcpy(&(this->ipHeader), ipHeader, sizeof(IPv4Header));
}

unsigned short IPPacket::GetIPVersion(void) {
    return ipHeader.GetIPVersion();
}

void IPPacket::SetIPVersion(unsigned short version) {
    ipHeader.SetIPVersion(version);
}

unsigned short IPPacket::GetIPHeaderLength(void) {
    return ipHeader.GetIPHeaderLength();
}

void IPPacket::SetIPHeaderLength(unsigned short len) {
    ipHeader.SetIPHeaderLength(len);
}

unsigned short IPPacket::GetServiceType(void) {
    return ipHeader.GetServiceType();
}

void IPPacket::SetServiceType(unsigned short tos) {
    ipHeader.SetServiceType(tos);
}

unsigned short IPPacket::GetPacketLength(void) {
    return ipHeader.GetPacketLength();
}

void IPPacket::SetPacketLength(unsigned short length) {
    ipHeader.SetPacketLength(length);
}

unsigned short IPPacket::GetPacketId(void) {
    return ipHeader.GetPacketId();
}

void IPPacket::SetPacketId(unsigned short id) {
    ipHeader.SetPacketId(id);
}

unsigned short IPPacket::GetTimeToLive(void) {
    return ipHeader.GetTimeToLive();
}

void IPPacket::SetTimeToLive(unsigned short ttl) {
    ipHeader.SetTimeToLive(ttl);
}

unsigned short IPPacket::GetProtocol(void) {
    return ipHeader.GetProtocol();
}

void IPPacket::SetProtocol(unsigned short protocol) {
    ipHeader.SetProtocol(protocol);
}

unsigned short IPPacket::GetChecksum(void) {
    return ipHeader.GetChecksum();
}

void IPPacket::SetChecksum(unsigned short csum) {
    ipHeader.SetChecksum(csum);
}

unsigned short IPPacket::GetDontFragment() {
    return ipHeader.GetDontFragment();
}

void IPPacket::SetDontFragment(unsigned short fragment) {
    ipHeader.SetDontFragment(fragment);
}

std::string IPPacket::GetSourceAddress() const {
    return ipHeader.GetSourceAddress();
}

void IPPacket::SetSourceAddress(const std::string &address) {
    ipHeader.SetSourceAddress(address);
}

void IPPacket::SetSourceAddress(const sockaddr_in &address) {
    ipHeader.SetSourceAddress(address);
}

std::string IPPacket::GetDestAddress() const {
    return ipHeader.GetDestAddress();
}

void IPPacket::SetDestAddress(const std::string &address) {
    ipHeader.SetDestAddress(address);
}

void IPPacket::SetDestAddress(const sockaddr_in &address) {
    ipHeader.SetDestAddress(address);
}

unsigned short IPPacket::Checksum(unsigned short *ptr, int nbytes) {
    return EthernetPacket::Checksum(ptr, nbytes);
}

//============================================================================
// ICMPPacket class definition:
//============================================================================

ICMPPacket::ICMPPacket(void) {
	 memset(payload, 0, sizeof(payload));
}

ICMPPacket::~ICMPPacket(void) {
}

ICMPPacket::ICMPPacket(const std::string &sourceMac,
			           const std::string &destMac,
			           const std::string &sourceAddress,
			           const std::string &destAddress,
			           unsigned short packetId,
					   ICMPType icmpType,
					   unsigned short icmpCode,
					   unsigned short seq,
					   unsigned short id,
					   const unsigned char* icmpPayload,
					   unsigned short payloadLength,
			           unsigned short ttl,
			           unsigned short typeOfService): IPPacket(sourceMac, 
                                                               destMac, 
                                                               IPPROTO_ICMP,  
                                                               sizeof(IPv4Header) + sizeof(ICMPHeader) + payloadLength,
                                                               sourceAddress,
                                                               destAddress,
                                                               packetId,
                                                               typeOfService,
                                                               ttl, 4) 
{
	memset(&icmpHeader, 0, sizeof(ICMPHeader));
	memset(payload, 0, sizeof(payload));
    /** ICMP Header configuraton: **/
	icmpHeader.SetType(icmpType);
	icmpHeader.SetCode(icmpCode);
	icmpHeader.SetChecksum(0);
	icmpHeader.SetIdentifier(id);
	icmpHeader.SetSequence(seq);
	/** Calculate the ICMP Header Checksum: **/
	icmpHeader.SetChecksum(this->CalcChecksum(&icmpHeader, icmpPayload, payloadLength));
	if (payloadLength) 
        memcpy(payload, icmpPayload, payloadLength);
}

 unsigned short ICMPPacket::CalcChecksum(const ICMPHeader* icmpHeader,
			                 unsigned const char* icmpPayload,
							 unsigned short payloadLength)
{
	char buffer[2048];
	memcpy(buffer, icmpHeader, sizeof(ICMPHeader));
	memcpy(buffer + sizeof(ICMPHeader), icmpPayload, payloadLength);
	return this->Checksum((unsigned short*)buffer, sizeof(ICMPHeader) + payloadLength);
}

//============================================================================
// UDPPacket class definition:
//============================================================================

UDPPacket::UDPPacket(void) {
	 memset(payload, 0, sizeof(payload));
}

UDPPacket::~UDPPacket(void) {
}

UDPPacket::UDPPacket(const std::string &sourceMac,
					 const std::string &destMac,
					 const std::string &sourceAddress,
					 unsigned short sourcePort,
					 const std::string &destAddress,
					 unsigned short destPort,
					 unsigned short packetId,
					 const unsigned char* udpPayload,
					 unsigned short payloadLength,
					 unsigned short ttl,
					 unsigned short typeOfService) : IPPacket(sourceMac, 
															  destMac, 
                                                              IPPROTO_UDP,  
                                                              sizeof(IPv4Header) + sizeof(UDPHeader) + payloadLength,
                                                              sourceAddress,
                                                              destAddress,
                                                              packetId,
                                                              typeOfService,
                                                              ttl,
															  4) 
{
	memset(&udpHeader, 0, sizeof(UDPHeader));
	memset(payload, 0, sizeof(payload));
    /** UDP Header configuraton: **/
	udpHeader.SetSourcePort(sourcePort);
	udpHeader.SetDestinationPort(destPort);
	udpHeader.SetChecksum(0);
	udpHeader.SetPacketLength(sizeof(UDPHeader) + payloadLength);
	/** Calculate the UDP Header Checksum: **/
	udpHeader.SetChecksum(this->CalcChecksum(&udpHeader, udpPayload, payloadLength));
	if (payloadLength) 
        memcpy(payload, udpPayload, payloadLength);
}

void UDPPacket::SetUDPHeader(const char* buffer) {
	memcpy(&udpHeader, buffer, sizeof(UDPHeader));
	int len = ipHeader.GetPacketLength() -  ipHeader.GetIPHeaderLength() - sizeof(UDPHeader);
	if (len > 0)
		memcpy(payload, (const char*)(buffer + sizeof(UDPHeader)), len);
}

std::string UDPPacket::GetUDPData(void) {
	std::string data;
	data.assign(payload, ipHeader.GetPacketLength() -  ipHeader.GetIPHeaderLength() - sizeof(UDPHeader));
	return data;
}
void UDPPacket::ChecksumRecalculate() {
	/** Calculate the IP Header Checksum: **/
	ipHeader.SetChecksum(0);
	ipHeader.SetChecksum(this->Checksum((unsigned short*)(&ipHeader), sizeof(IPv4Header)));
	/** Set UDP Checksum to 0. Its OK. **/
	udpHeader.SetChecksum(0);
}

unsigned short UDPPacket::GetSourcePort(void) const {
	return udpHeader.GetSourcePort();
}

void UDPPacket::SetSourcePort(unsigned short port) {
	udpHeader.SetSourcePort(port);
}
	
unsigned short UDPPacket::GetDestinationPort(void) const {
	return udpHeader.GetDestinationPort();
}

void UDPPacket::SetDestinationPort(unsigned short port) {
	udpHeader.SetDestinationPort(port);
}

unsigned short UDPPacket::CalcChecksum(const UDPHeader* udpHeader,
										unsigned const char* payload,
										unsigned short payloadLen)
{
	/*char buffer[2048];
	memcpy(buffer, udpHeader, sizeof(UDPHeader));
	memcpy(buffer + sizeof(UDPHeader), payload, payloadLen);
	return this->Checksum((unsigned short*)buffer, sizeof(UDPHeader) + payloadLen);*/
	
	char buffer[5120];
	/** Pseudo UDP Header initialization: **/
    UDPPseudoHeader udpPHdr;
    udpPHdr.sourceAddress = ipHeader.srcaddr;
	udpPHdr.destinationAddress = ipHeader.destaddr;
	udpPHdr.protocol = IPPROTO_UDP;
	udpPHdr.totalLength = htons(sizeof(UDPHeader) + payloadLen);
	udpPHdr.useless = 0;
	
	memcpy(buffer, &udpPHdr, sizeof(UDPPseudoHeader));
	memcpy(buffer + sizeof(UDPPseudoHeader), udpHeader, sizeof(UDPHeader));
	memcpy(buffer + sizeof(UDPPseudoHeader) + sizeof(UDPHeader), payload, payloadLen);
	
	return this->Checksum((unsigned short*)buffer, sizeof(UDPHeader) + sizeof(UDPPseudoHeader) + payloadLen);
}

//============================================================================
// TCPPacket class definition:
//============================================================================

TCPPacket::TCPPacket(void) {
    memset(tcpOptsPayload, 0, sizeof(tcpOptsPayload));
}

TCPPacket::~TCPPacket(void) {
}

TCPPacket::TCPPacket(const std::string &sourceMac,
			         const std::string &destMac,
			         const std::string &sourceAddress,
			         unsigned short sourcePort,
			         const std::string &destAddress,
			         unsigned short destPort,
			         unsigned int sequence,
			         unsigned int acknowledge,
			         unsigned short packetId,
			         unsigned short ttl,
			         unsigned short window,
			         unsigned short typeOfService,
			         bool SYN,
			         bool ACK,
			         bool FIN,
			         bool PSH,
					 bool RST,
			         const unsigned char* tcpOptions,
			         unsigned short tcpOptsLength,
			         const unsigned char* tcpData,
			         unsigned short tcpDataLength) : IPPacket(sourceMac, 
                                                              destMac, 
                                                              IPPROTO_TCP,  
                                                              sizeof(IPv4Header) + sizeof(TCPHeader) + tcpOptsLength + tcpDataLength,
                                                              sourceAddress,
                                                              destAddress,
                                                              packetId,
                                                              typeOfService,
                                                              ttl, 4) 
{
	memset(&tcpHeader, 0, sizeof(TCPHeader));
    memset(tcpOptsPayload, 0, sizeof(tcpOptsPayload));
    /** TCP Header configuraton: **/
	tcpHeader.SetSourcePort(sourcePort);
	tcpHeader.SetDestinationPort(destPort);
	tcpHeader.SetWindow(window);
	tcpHeader.SetAcknowledgeSeqNum(acknowledge);
	tcpHeader.SetSequenceNum(sequence);
	tcpHeader.SetDataOffset(sizeof(TCPHeader) + tcpOptsLength);
	tcpHeader.SetFlag_URG(0);
	tcpHeader.SetFlag_ACK(ACK);
	tcpHeader.SetFlag_PSH(PSH);
	tcpHeader.SetFlag_RST(RST);
	tcpHeader.SetFlag_SYN(SYN);
	tcpHeader.SetFlag_FYN(FIN);
	tcpHeader.SetChecksum(0);
	tcpHeader.SetUrgentPointer(0);
	tcpHeader.SetChecksum(0);
	tcpHeader.SetChecksum(CalcChecksum(&ipHeader, &tcpHeader, tcpOptions, tcpData, tcpDataLength));
	if (tcpOptsLength) 
        memcpy(tcpOptsPayload, tcpOptions, tcpOptsLength);
	if (tcpDataLength) 
		memcpy(tcpOptsPayload  + tcpOptsLength, tcpData, tcpDataLength);
}

void TCPPacket::SetTCPHeader(const char* tcpBufferPtr) {
	memcpy(&tcpHeader, tcpBufferPtr, sizeof(TCPHeader));
	if (GetTCPOptionsLength() > 0)
		memcpy(tcpOptsPayload, ((const char*)(tcpBufferPtr + sizeof(TCPHeader))), GetTCPOptionsLength());
	if (GetTCPDataLength() > 0)
		memcpy(tcpOptsPayload, ((const char*)(tcpBufferPtr + GetDataOffset())), GetTCPDataLength());
}

void TCPPacket::SetTCPHeader(TCPHeader* tcpHeader) {
	memcpy(&(this->tcpHeader), tcpHeader, sizeof(TCPHeader));
}

unsigned short TCPPacket::GetTCPDataLength(void) {
    return ipHeader.GetPacketLength() -  ipHeader.GetIPHeaderLength() - tcpHeader.GetDataOffset();
}

unsigned short TCPPacket::GetTCPOptionsLength(void) {
    return tcpHeader.GetDataOffset() - sizeof(TCPHeader);
}

unsigned short TCPPacket::GetChecksum(void) {
    return tcpHeader.GetChecksum();
}

void TCPPacket::SetChecksum(unsigned short chsm) {
    tcpHeader.SetChecksum(chsm);
}

unsigned short TCPPacket::GetDataOffset(void) const {
    return tcpHeader.GetDataOffset();
}

void TCPPacket::SetDataOffset(unsigned short offset) {
    tcpHeader.SetDataOffset(offset);
}

unsigned short TCPPacket::GetSourcePort(void) {
    return tcpHeader.GetSourcePort();
}

void TCPPacket::SetSourcePort(unsigned short port) {
    tcpHeader.SetSourcePort(port);
}

unsigned short TCPPacket::GetDestinationPort(void) {
    return tcpHeader.GetDestinationPort();
}

void TCPPacket::SetDestinationPort(unsigned short port) {
    tcpHeader.SetDestinationPort(port);
};

unsigned short TCPPacket::GetWindow(void) {
    return tcpHeader.GetWindow();
}

void TCPPacket::SetWindow(unsigned short wnd) {
    tcpHeader.SetWindow(wnd);
}

unsigned int TCPPacket::GetAcknowledgeSeqNum(void) {
    return tcpHeader.GetAcknowledgeSeqNum();
}

void TCPPacket::SetAcknowledgeSeqNum(unsigned int ackSeq) {
    tcpHeader.SetAcknowledgeSeqNum(ackSeq);
}

unsigned int TCPPacket::GetSequenceNum(void) {
    return tcpHeader.GetSequenceNum();
}

void TCPPacket::SetSequenceNum(unsigned int seq) {
    tcpHeader.SetSequenceNum(seq);
}

bool TCPPacket::GetFlag_SYN(void) {
    return tcpHeader.GetFlag_SYN();
}

void TCPPacket::SetFlag_SYN(bool state) {
    tcpHeader.SetFlag_SYN(state);
}

bool TCPPacket::GetFlag_ACK(void) {
    return tcpHeader.GetFlag_ACK();
}

void TCPPacket::SetFlag_ACK(bool state) {
    tcpHeader.SetFlag_ACK(state);
}

bool TCPPacket::GetFlag_FYN(void) {
    return tcpHeader.GetFlag_FYN();
}

void TCPPacket::SetFlag_FYN(bool state) {
    tcpHeader.SetFlag_FYN(state);
}

bool TCPPacket::GetFlag_RST(void) {
    return tcpHeader.GetFlag_RST();
}

void TCPPacket::SetFlag_RST(bool state) {
    tcpHeader.SetFlag_RST(state);
}

bool TCPPacket::GetFlag_PSH(void) {
    return tcpHeader.GetFlag_PSH();
}

void TCPPacket::SetFlag_PSH(bool state) {
    tcpHeader.SetFlag_PSH(state);
}

bool TCPPacket::GetFlag_URG(void) {
    return tcpHeader.GetFlag_URG();
}

void TCPPacket::SetFlag_URG(bool state) {
    tcpHeader.SetFlag_URG(state);
}

unsigned short TCPPacket::GetUrgentPointer(void) {
    return tcpHeader.GetUrgentPointer();
}

void TCPPacket::SetUrgentPointer(unsigned short urgPtr) {
    tcpHeader.SetUrgentPointer(urgPtr);
}

unsigned short TCPPacket::CalcChecksum(const IPv4Header* ipHeader,
			                           const TCPHeader* tcpHeader,
			                           unsigned const char* tcpOptions,
					                   const unsigned char* tcpData,
							           unsigned short tcpDataLength)
{
    char pseudoBuffer[2048];
	unsigned short tcpHeaderLength = tcpHeader->GetDataOffset();
	unsigned short tcpOptionsLength = tcpHeaderLength - sizeof(TCPHeader);
	/** Pseudo TCP Header initialization: **/
    PseudoTCPHeader tcpPseudoHeader;
    tcpPseudoHeader.sourceAddress = ipHeader->srcaddr;
	tcpPseudoHeader.destinationAddress = ipHeader->destaddr;
	tcpPseudoHeader.protocol = IPPROTO_TCP;
	tcpPseudoHeader.totalLength = htons(tcpHeaderLength + tcpDataLength);
	tcpPseudoHeader.useless = 0;
	/** Preparing pseudodata buffer. For TCP Checksum calclulation: **/
	memcpy(pseudoBuffer, &tcpPseudoHeader, sizeof(PseudoTCPHeader));
	memcpy(pseudoBuffer + sizeof(PseudoTCPHeader), tcpHeader, sizeof(TCPHeader));
	if (tcpOptionsLength) {
        memcpy(pseudoBuffer + sizeof(PseudoTCPHeader) + sizeof(TCPHeader),
		tcpOptions,
		tcpOptionsLength);
	}
	if (tcpDataLength) {
        memcpy(pseudoBuffer + sizeof(PseudoTCPHeader) + sizeof(TCPHeader) + tcpOptionsLength,
		       tcpData,
			   tcpDataLength);
	}
	/** Calculating the checksum: **/
	return IPPacket::Checksum((unsigned short*)pseudoBuffer, tcpHeaderLength + sizeof(PseudoTCPHeader) + tcpDataLength);
}

unsigned short TCPPacket::CalcChecksumEx() {
    char pseudoBuffer[10240];
	unsigned short tcpOptionsLength = tcpHeader.GetDataOffset() - sizeof(TCPHeader);
	unsigned short tcpDataLength = ipHeader.GetPacketLength() -  ipHeader.GetIPHeaderLength() - tcpHeader.GetDataOffset();
	if (tcpDataLength > sizeof(pseudoBuffer)) {
		std::cout << "Error. Buffer size = " << sizeof(pseudoBuffer) << ", TCP Data length = " << tcpDataLength << std::endl;
		return 1;
	}
	/** Pseudo TCP Header initialization: **/
    PseudoTCPHeader tcpPseudoHeader;
    tcpPseudoHeader.sourceAddress = ipHeader.srcaddr;
	tcpPseudoHeader.destinationAddress = ipHeader.destaddr;
	tcpPseudoHeader.protocol = IPPROTO_TCP;
	tcpPseudoHeader.totalLength = htons(tcpHeader.GetDataOffset() + tcpDataLength);
	tcpPseudoHeader.useless = 0;
	/** Preparing pseudodata buffer. For TCP Checksum calclulation: **/
	memcpy(pseudoBuffer, &tcpPseudoHeader, sizeof(PseudoTCPHeader));
	memcpy(pseudoBuffer + sizeof(PseudoTCPHeader), &tcpHeader, sizeof(TCPHeader));
	if (tcpOptionsLength) 
        memcpy(pseudoBuffer + sizeof(PseudoTCPHeader) + sizeof(TCPHeader), tcpOptsPayload, tcpOptionsLength);
	if (tcpDataLength) 
        memcpy(pseudoBuffer + sizeof(PseudoTCPHeader) + sizeof(TCPHeader) + tcpOptionsLength, tcpOptsPayload + tcpOptionsLength, tcpDataLength);
	/** Calculating the checksum: **/
	return IPPacket::Checksum((unsigned short*)pseudoBuffer, tcpHeader.GetDataOffset() + sizeof(PseudoTCPHeader) + tcpDataLength);
}

std::string TCPPacket::GetTCPData()
{
	std::string tcpData;
	tcpData.assign(tcpOptsPayload + GetTCPOptionsLength(), GetTCPDataLength());
	return tcpData;
}

std::string TCPPacket::GetTCPOptions() {
	std::string opts;
	opts.assign(tcpOptsPayload, GetTCPOptionsLength());
	return opts;
}

void TCPPacket::ChecksumRecalculate() {
	/** Calculate the IP Header Checksum: **/
	ipHeader.SetChecksum(0);
	ipHeader.SetChecksum(this->Checksum((unsigned short*)(&ipHeader), sizeof(IPv4Header)));
	/** Calculate the TCP Header Checksum: **/
	tcpHeader.SetChecksum(0);
	tcpHeader.SetChecksum(CalcChecksumEx());
}

void TCPPacket::Configure(const std::string &sourceMac,
						  const std::string &destMack,
						  const std::string &sourceAddress,
						  unsigned short sourcePort,
			  	   		  const std::string &destAddress,
			  	   		  unsigned short destPort,
			  	   		  unsigned int sequence,
			  	   		  unsigned int acknowledge,
			  	   		  unsigned short packetId,
			  	   		  unsigned short ttl,
			  	   		  unsigned short window,
			  	   		  unsigned short typeOfService,
			  	   		  bool SYN,
			  	   		  bool ACK,
			  	   		  bool FIN,
			  	   		  bool PSH,
						  bool RST,
			  	   		  const unsigned char* tcpOptions,
						  unsigned short tcpOptsLength,
						  const unsigned char* tcpData,
					      unsigned short tcpDataLength)
{
	/** Prepare Ethernet Header data strucure: **/
	memset(&ethernetHeader, 0, sizeof(EthernetHeader));
	/** Ethernet Header configuraton: **/
	ethernetHeader.SetDestinationMACAddress(destMack);
	ethernetHeader.SetSourceMACAddress(sourceMac);
	ethernetHeader.SetType(ETHERTYPE_IP);
	
	/** Prepare IP Header data strucure: **/
	memset(&ipHeader, 0, sizeof(IPv4Header));
    /** IP Header configuraton: **/
    ipHeader.SetIPHeaderLength(20);   /** Since in IPv4 its size is 20 **/
	ipHeader.SetIPVersion(4);         /** Trivial                      **/
	ipHeader.SetServiceType(typeOfService);
	ipHeader.SetPacketLength(sizeof(IPv4Header) + sizeof(TCPHeader) + tcpOptsLength + tcpDataLength);
	ipHeader.SetPacketId(packetId);
	ipHeader.SetTimeToLive(ttl);
	ipHeader.SetProtocol(IPPROTO_TCP);
	ipHeader.SetChecksum(0);
	ipHeader.SetDontFragment(1);
	ipHeader.SetSourceAddress(sourceAddress);
	ipHeader.SetDestAddress(destAddress);
	/** Calculate the IP Header Checksum: **/
	ipHeader.SetChecksum(this->Checksum((unsigned short*)(&ipHeader), sizeof(IPv4Header)));
	
	/** Prepare TCP Header data structures: **/
	memset(&tcpHeader, 0, sizeof(TCPHeader));
    memset(tcpOptsPayload, 0, sizeof(tcpOptsPayload));
    /** TCP Header configuraton: **/
	tcpHeader.SetSourcePort(sourcePort);
	tcpHeader.SetDestinationPort(destPort);
	tcpHeader.SetWindow(window);
	tcpHeader.SetAcknowledgeSeqNum(acknowledge);
	tcpHeader.SetSequenceNum(sequence);
	tcpHeader.SetDataOffset(sizeof(TCPHeader) + tcpOptsLength);
	tcpHeader.SetFlag_URG(0);
	tcpHeader.SetFlag_ACK(ACK);
	tcpHeader.SetFlag_PSH(PSH);
	tcpHeader.SetFlag_RST(RST);
	tcpHeader.SetFlag_SYN(SYN);
	tcpHeader.SetFlag_FYN(FIN);
	tcpHeader.SetChecksum(0);
	tcpHeader.SetUrgentPointer(0);
	tcpHeader.SetChecksum(0);
	tcpHeader.SetChecksum(CalcChecksum(&ipHeader, &tcpHeader, tcpOptions, tcpData, tcpDataLength));
	if (tcpOptsLength) 
        memcpy(tcpOptsPayload, tcpOptions, tcpOptsLength);
	if (tcpDataLength) 
		memcpy(tcpOptsPayload  + tcpOptsLength, tcpData, tcpDataLength);
}			
					
