#include "DfException.h"

std::string DfException::GetReason()
{
	switch (ExceptionID)
	{
	case ERR_UNDEF:
		return "Undefined error occured";
	case ERR_INVALID_INDEX:
		return "Invalid Index";
	case ERR_ALLOCATION:
		return "Allocation error";
	case ERR_INCOMPATIBLE_SIZE:
		return "Incompatible size";
	case ERR_CANT_MOVE_HEADER:
		return "Cannot move header of dataframe";
	case ERR_FILE:
		return "Trouble with file";
	default:
		return "Undefined error";
	}
}