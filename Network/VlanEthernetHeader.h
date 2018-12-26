//============================================================================
// Name        : VlanEthernetHeader.h
// Created on  : May 26, 2015
// Author      : Tokmakov Andrey
// Version     : 1.0 
// Copyright   : Your copyright notice
// Description : VLAN ethernet header class declaration
//============================================================================

#include "EthernetHeader.h"

#ifndef VLAN_ETHERNET_HEADER_H_
#define VLAN_ETHERNET_HEADER_H_

/** VlanTag class: **/
struct VlanTag {
	unsigned char id_1:4;
	unsigned char cfi:1;
	unsigned char priority:3;
	unsigned char id;
	unsigned char type[2];
};

/** VlanEthernetHeader class: **/
class VlanEthernetHeader: public EthernetHeader
{
private:
	VlanTag vlanTag;
	
public:
	VlanEthernetHeader();
	
	void SetVlanPacketType(unsigned short type);
	void SetVlanId(unsigned short vlanId);
	void SetPriority(unsigned short priority);
	
	unsigned short GetPriority();
};

#endif /* VLAN_ETHERNET_HEADER_H_ */