//============================================================================
// Name        : VlanEthernetHeader.cpp
// Created on  : May 26, 2015
// Author      : Tokmakov Andrey
// Version     : 1.0 
// Copyright   : Your copyright notice
// Description : VLAN ethernet header class definition
//============================================================================

#include "VlanEthernetHeader.h"

VlanEthernetHeader::VlanEthernetHeader() {
	// TODO Auto-generated constructor stub
}

void VlanEthernetHeader::SetVlanPacketType(unsigned short type) {
	vlanTag.type[0] = type / 256;
	vlanTag.type[1] = type % 256;
}

void VlanEthernetHeader::SetVlanId(unsigned short vlanId) {
	vlanTag.id = 0;
	vlanTag.cfi = 0;
	vlanTag.id = vlanId;	
}

void VlanEthernetHeader::SetPriority(unsigned short priority) {
	vlanTag.priority = priority;
}

unsigned short VlanEthernetHeader::GetPriority() {
	return vlanTag.priority;
}