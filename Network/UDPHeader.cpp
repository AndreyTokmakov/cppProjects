//============================================================================
// Name        : UDPHeader.cpp
// Created on  : May 19, 2015
// Author      : Tokmakov Andrey
// Version     :
// Copyright   : Your copyright notice
// Description : UDP Header class definitions
//============================================================================

#include "UDPHeader.h"

UDPHeader::UDPHeader(void) {
}

UDPHeader::~UDPHeader(void) {
}

unsigned short UDPHeader::GetSourcePort(void) const {
	return htons(this->sourcePort);
}

void UDPHeader::SetSourcePort(unsigned short port) {
	this->sourcePort = htons(port);
}

unsigned short UDPHeader::GetDestinationPort(void) const {
	return htons(this->destinationPort);
}

void UDPHeader::SetDestinationPort(unsigned short port) {
	this->destinationPort = htons(port);
}

unsigned short UDPHeader::GetPacketLength(void) const {
	return ntohs(length);
}

void UDPHeader::SetPacketLength(unsigned short len) {
	length = htons(len);
}

unsigned short UDPHeader::GetChecksum(void) const {
	return htons(this->checksum);
}

void UDPHeader::SetChecksum(unsigned short chsm) {
	//this->checksum = htons(chsm);
	this->checksum = (chsm);
}