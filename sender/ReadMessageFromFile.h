#pragma once

#include "util_structures.h"

static MC_STATUS NOEXP_FUNC StreamToMsgObj(int A_msgID,
	void*      A_CBinformation,
	int        A_isFirst,
	int*       A_dataSize,
	void**     A_dataBuffer,
	int*       A_isLast);
SAMP_BOOLEAN isFirstFile(int isFirstFlag, CBinfo* A_cbinfo);
SAMP_BOOLEAN isLastFile(int eof, int* isLast);

void openEmptyMessage(int* A_msgID);
void openFile(CBinfo* A_cbinfo, char* A_filename, int* A_msgID);
void setIOBuffer(CBinfo* A_cbinfo);
void setBufferLength(CBinfo* A_cbinfo);
void allocateMemoryToBuffer(CBinfo* A_cbinfo);
void openEmptyMessage(int* A_msgID);
void closeFile(CBinfo* A_cbinfo);
void freeBuffer(CBinfo* A_cbinfo);


class ReadMessageFromFile {
public:
	static SAMP_BOOLEAN readFromFile(STORAGE_OPTIONS*  A_options,
		char*             A_filename,
		FORMAT_ENUM       A_format,
		int*              A_msgID,
		TRANSFER_SYNTAX*  A_syntax,
		size_t*           A_bytesRead);
};
