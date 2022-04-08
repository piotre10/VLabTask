#pragma once

#include <iostream>

#define ERR_UNDEF 1
#define ERR_INVALID_INDEX 2
#define ERR_ALLOCATION 3
#define ERR_INCOMPATIBLE_SIZE 4
#define ERR_CANT_MOVE_HEADER 5
#define ERR_FILE 6

class DfException
{
public:
	int ExceptionID;

	DfException(int errId = ERR_UNDEF) { ExceptionID = errId; };

	std::string GetReason();
	void PrintReason() { std::cout << "Error: " << GetReason() << std::endl; };
};

