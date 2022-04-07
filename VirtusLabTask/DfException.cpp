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
	default:
		return "Undefined error occured";
	}
}