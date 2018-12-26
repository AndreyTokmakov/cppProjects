//============================================================================
// Name        : EthernetHeader.cpp
// Created on  : Apr 09, 2015
// Author      : Tokmakov Andrey
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include "EthernetHeader.h"

EthernetHeader::EthernetHeader() {
	// TODO Auto-generated constructor stub
}

bool EthernetHeader::SetMACAddress(const char* s, unsigned char* d)
{
	unsigned u[6], i;
	if (sscanf(s, "%02x:%02x:%02x:%02x:%02x:%02x", u+0, u+1, u+2, u+3, u+4, u+5) != 6)
		return false;
	for (i = 0; i < 6; i++) {
		if (u[i] > 255)
			return false;;
		d[i] = u[i];
	}
	return true;
}

void EthernetHeader::PrintMACAddres(unsigned char* mac)
{
	for (int i = 0; i < 5; i++)
		printf("%02x:", mac[i]);
	printf("%02x", mac[5]);
}

std::string EthernetHeader::GetSourceMACAddress(void) const {
	char str[16];
	sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x", 
			this->sourceMac[0], this->sourceMac[1], this->sourceMac[2], this->sourceMac[3], this->sourceMac[4], this->sourceMac[5]);
	return std::string(str);
}

std::string EthernetHeader::DestinationMACAddress(void) const {
	char str[16];
	sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x", 
			this->destMac[0], this->destMac[1], this->destMac[2], this->destMac[3], this->destMac[4], this->destMac[5]);
	return std::string(str);
}

void EthernetHeader::PrintSourceMACAddres(void) {
	PrintMACAddres(this->sourceMac);
}

void EthernetHeader::PrintDestinationMACAddress(void) {
	PrintMACAddres(this->destMac);
}

bool EthernetHeader::SetSourceMACAddress(const std::string& mac) {
	return SetMACAddress(mac.c_str(), this->sourceMac);
}

bool EthernetHeader::SetSourceMACAddress(unsigned char* mac) {
	for (int i = 0; i < 6; i++) {
		if (mac[i] > 255)
			return false;;
		this->sourceMac[i] = mac[i];
	}
	return true;
}

bool EthernetHeader::CompareMacs(const char* s, unsigned char* d) {
	unsigned u[6], i;
	if (sscanf(s, "%02x:%02x:%02x:%02x:%02x:%02x", u+0, u+1, u+2, u+3, u+4, u+5) != 6)
		return false;
	for (i = 0; i < 6; i++) 
		if (d[i] != u[i])
			return false;
	return true;
}

void EthernetHeader::SetType(unsigned short packetType) {
	type[0] = packetType / 256;
	type[1] = packetType % 256;
}

unsigned short EthernetHeader::GetType() {
	return (((unsigned short)(type[0])) * 256 + ((unsigned short)(type[1])));
}

bool EthernetHeader::CompareSourceMac(const std::string& mac) {
	return CompareMacs(mac.c_str(), this->sourceMac);
}

bool EthernetHeader::CompareDestMac(const std::string& mac){
	return CompareMacs(mac.c_str(), this->destMac);
}

bool EthernetHeader::CompareSourceMacFast(const unsigned char* mac){
	return (0 == memcmp(sourceMac, mac, 6)) ? true : false;
}

bool EthernetHeader::CompareDestMacFast(const unsigned char* mac){
	return (0 == memcmp(destMac, mac, 6)) ? true : false;
}

bool EthernetHeader::SetDestinationMACAddress(const std::string& mac)  {
	return SetMACAddress(mac.c_str(), this->destMac);
}
