#pragma once

#include "util_structures.h"
//****************************************************************************************************************************
void getSOPClassUID(InstanceNode* node);
void setService(InstanceNode* node);
void setSOPInstanceUID(InstanceNode* node);
void sendMessage(int A_associationID, InstanceNode* node);
//****************************************************************************************************************************

class SendImage {
public:
	static SAMP_BOOLEAN send(STORAGE_OPTIONS* A_options, int A_associationID, InstanceNode* A_node);
};
