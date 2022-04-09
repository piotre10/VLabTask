
#include <iostream>
#include <string>

#include "util.h"

int main(int argc, char* argv[])
{
	std::string file1, file2, colname;
	int jointype = -1; // 1 - innerjoin 2 - left outer join  3 - right outer

	switch (argc)
	{
	case 4: {
		file1 = argv[1];
		file2 = argv[2];
		colname = argv[3];
		jointype = 1;
	}
	case 5: {
		file1 = argv[1];
		file2 = argv[2];
		colname = argv[3];
		if (strcmp(argv[4],"inner") == 0 || strcmp(argv[4], "in") == 0)
			jointype = 1;
		else if (strcmp(argv[4], "left-outer") == 0 || strcmp(argv[4], "lo") == 0)
			jointype = 2;
		else if (strcmp(argv[4], "right-outer") == 0 || strcmp(argv[4], "ro") == 0)
			jointype = 3;
		else
		{
			std::cerr << "Usage: Wrong join type try [inner|in] [left-outer|lo] [right-outer|ro] for inner left outer and right outer joins accordingly" << std::endl;
			return -1;
		}
		break;
	}
	default: std::cerr << "Usage: join file1 file2 colname [jointype]" << std::endl; return -1;
	}

	DataFrame* pDf1 = NULL;
	DataFrame* pDf2 = NULL;

	try {
		pDf1 = ReadFromCsv(file1);
		pDf2 = ReadFromCsv(file2);
	}
	catch (DfException e) {
		std::cout << "Error: " << e.GetReason() << ". Occured while trying to read files";
		return -2;
	}
	try
	{
		DataFrame res;
		switch (jointype)
		{
		case 1: {
			res = InnerJoin(*pDf1, *pDf2, colname);
			break;
		}
		case 2: {
			res = LeftOuterJoin(*pDf1, *pDf2, colname);
			break;
		}
		case 3: {
			res = RightOuterJoin(*pDf1, *pDf2, colname);
			break;
		}
		default: std::cerr << "Error wrong jointype"; return -3;
		}
		std::cout << res;
	}
	catch (DfException e) {
		std::cout << "Error: " << e.GetReason() << ". Occured while joining csv-s";
		return -4;
	}

	return 0;
}
