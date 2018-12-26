//============================================================================
// Name        : GREHeader.cpp
// Created on  : Jan 25, 2015
// Author      : Tokmakov Andrey
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include "GREHeader.h"

GREHeader::GREHeader(void) {
}

GREHeader::~GREHeader(void) {
}

void GREHeader::SetProtocol(unsigned short proto) {
	this->protocol[0] = proto / 256;
	this->protocol[1] = proto % 256;
}

unsigned short GREHeader::GetProtocol() {
	return (((unsigned short)(protocol[0])) * 256 + ((unsigned short)(protocol[1])));
}

/*
unsigned short IPv4Header::GetIPVersion(void) {
	return this->ipVersion;
}

void IPv4Header::SetIPVersion(unsigned short version) {
	this->ipVersion = 4;
}

unsigned short IPv4Header::GetIPHeaderLength(void) {
	return (this->ipHeaderLength * 4);
}

void IPv4Header::SetIPHeaderLength(unsigned short len) {
	this->ipHeaderLength = (len / 4);
}

unsigned short IPv4Header::GetServiceType(void) {
	return this->serviceType;
}

void IPv4Header::SetServiceType(unsigned short tos) {
	this->serviceType = (unsigned char)tos;
}

unsigned short IPv4Header::GetPacketLength() {
	return ntohs(packetLength);
}

void IPv4Header::SetPacketLength(unsigned short length) {
	packetLength = htons(length);
}

unsigned short IPv4Header::GetPacketId(void) {
	return htons(this->packetId);
}

void IPv4Header::SetPacketId(unsigned short id) {
	this->packetId = htons(id);
}

unsigned short IPv4Header::GetTimeToLive(void) {
	return this->timeToLive;
}

void IPv4Header::SetTimeToLive(unsigned short ttl) {
	this->timeToLive = (unsigned char)ttl;
}

unsigned short IPv4Header::GetProtocol(void) {
	return this->protocol;
}
void IPv4Header::SetProtocol(unsigned short protocol) {
	this->protocol = (unsigned char)protocol;
}

unsigned short IPv4Header::GetChecksum(void) {
	return (this->checksum);
}

void IPv4Header::SetChecksum(unsigned short csum) {
	this->checksum = (csum);
}

unsigned short IPv4Header::GetDontFragment() {
	return this->dont_fragment;
}

void IPv4Header::SetDontFragment(unsigned short fragment) {
	this->dont_fragment = (unsigned char)fragment;
}

std::string IPv4Header::GetSourceAddress() const {
	return ResolveAddress(this->srcaddr);
}

void IPv4Header::SetSourceAddress(const std::string &address) {
	this->srcaddr = inet_addr(address.c_str());
}

void IPv4Header::SetSourceAddress(const sockaddr_in &address) {
	this->srcaddr = inet_addr(inet_ntoa(address.sin_addr));
}

std::string IPv4Header::GetDestAddress() const {
	return ResolveAddress(this->destaddr);
}

void IPv4Header::SetDestAddress(const std::string &address) {
	this->destaddr = inet_addr(address.c_str());
}

void IPv4Header::SetDestAddress(const sockaddr_in &address) {
	this->destaddr = inet_addr(inet_ntoa(address.sin_addr));
}

std::string IPv4Header::ResolveAddress(unsigned long address) const {
	in_addr addr;
	addr.s_addr = address;
	return inet_ntoa(addr);
}*/
