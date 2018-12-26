//============================================================================
// Name        : TCPHeader.cpp
// Created on  : Dec 04, 2014
// Author      : Tokmakov Andrey
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : TCP Header class definition
//============================================================================

#include "TCPHeader.h"

TCPHeader::TCPHeader(void)
{
    this->reserved2 = 0;
    this->reserved_part1 = 0;
}

TCPHeader::~TCPHeader(void)
{
}

unsigned short TCPHeader::GetDataOffset(void) const {
	return dataOffset * 4;
}
void TCPHeader::SetDataOffset(unsigned short offset) {
	this->dataOffset = offset / 4;
}

unsigned short TCPHeader::GetSourcePort(void) {
	return htons(this->sourcePort);
}

void TCPHeader::SetSourcePort(unsigned short port) {
	this->sourcePort = htons(port);
}

unsigned short TCPHeader::GetDestinationPort(void) {
	return htons(this->destinationPort);
}

void TCPHeader::SetDestinationPort(unsigned short port) {
	this->destinationPort = htons(port);
}

unsigned short TCPHeader::GetWindow(void) {
	return htons(this->window);
}

void TCPHeader::SetWindow(unsigned short wnd) {
	this->window = htons(wnd);
}

unsigned int TCPHeader::GetAcknowledgeSeqNum(void) {
	return htonl(this->acknowledge);
}

void TCPHeader::SetAcknowledgeSeqNum(unsigned int ackSeq) {
	this->acknowledge = htonl( ackSeq);
}

unsigned int TCPHeader::GetSequenceNum(void) {
	return htonl(this->sequence);
}

void TCPHeader::SetSequenceNum(unsigned int seq) {
	this->sequence = htonl(seq);
}

bool TCPHeader::GetFlag_SYN(void) {
	return ((unsigned short)(this->SYN)) == 1 ? true : false;
}

void TCPHeader::SetFlag_SYN(bool state) {
	this->SYN = (unsigned short)state;
}

bool TCPHeader::GetFlag_ACK(void) {
	return ((unsigned short)(this->ACK)) == 1 ? true : false;
}

void TCPHeader::SetFlag_ACK(bool state) {
	this->ACK = (unsigned short)state;
}

bool TCPHeader::GetFlag_FYN(void) {
	return ((unsigned short)(this->FYN)) == 1 ? true : false;
}

void TCPHeader::SetFlag_FYN(bool state) {
	this->FYN = (unsigned short)state;
}

bool TCPHeader::GetFlag_RST(void) {
	return ((unsigned short)(this->RST)) == 1 ? true : false;
}

void TCPHeader::SetFlag_RST(bool state) {
	this->RST = (unsigned short)state;
}

bool TCPHeader::GetFlag_PSH(void) {
	return ((unsigned short)(this->PSH)) == 1 ? true : false;
}

void TCPHeader::SetFlag_PSH(bool state) {
	this->PSH = (unsigned short)state;
}

bool TCPHeader::GetFlag_URG(void) {
	return ((unsigned short)(this->URG)) == 1 ? true : false;
}

void TCPHeader::SetFlag_URG(bool state) {
	this->URG = (unsigned short)state;
}

unsigned short TCPHeader::GetChecksum(void) {
	return htons(this->checksum);
}

void TCPHeader::SetChecksum(unsigned short chsm) {
	//this->checksum = htons(chsm);
	this->checksum = (chsm);
}

unsigned short TCPHeader::GetUrgentPointer(void){
	return htons(this->urgent_pointer);
}

void TCPHeader::SetUrgentPointer(unsigned short urgPtr){
	this->urgent_pointer = htons(urgPtr);
}

