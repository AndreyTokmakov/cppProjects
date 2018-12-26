//============================================================================
// Name        : ICMPHeader.cpp
// Created on  : May 19, 2015
// Author      : Tokmakov Andrey
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include "ICMPHeader.h"

ICMPHeader::ICMPHeader(void)
{
}

ICMPHeader::~ICMPHeader(void)
{
}

unsigned short ICMPHeader::GetType(void) const {
	return this->type;
}

void ICMPHeader::SetType(unsigned short type) {
	this->type = type;
}

unsigned short ICMPHeader::GetCode(void) const {
	return this->code;
}

void ICMPHeader::SetCode(unsigned short code) {
	this->code = code;
}
	
unsigned short ICMPHeader::GetChecksum(void) const {
	return htons(this->checksum);
}

void ICMPHeader::SetChecksum(unsigned short chsm) {
	//this->checksum = htons(chsm);
	this->checksum = chsm;
}
	
unsigned short ICMPHeader::GetIdentifier(void) const {
	return htons(this->identifier);
}

void ICMPHeader::SetIdentifier(unsigned short id) {
	this->identifier = htons(id);
}
	
unsigned short ICMPHeader::GetSequence(void) const{
	return htons(this->sequence);
}

void ICMPHeader::SetSequence(unsigned short seq) {
	this->sequence = htons(seq);
}	
