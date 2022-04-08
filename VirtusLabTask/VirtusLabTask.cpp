// VirtusLabTask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "util.h"

int main(int argc, char* argv[])
{
	std::string file1, file2, colname;
	int jointype = -1; // 1 - innerjoin 2 - left outer join  3 - right outer

	switch (argc)
	{
	case 1: {
		std::cout << "Welcome in Debug mode" << std::endl;
		return 0;
	}
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
			std::cerr << "Usage: Wrong join type try inner/in left-outer/lo right-outer/ro for inner left outer and right outer joins accordingly" << std::endl;
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
		std::cout << "Error: " << e.GetReason() << " Occured while trying to read files";
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
		std::cout << "Error: " << e.GetReason() << " Occured while joining csv-s";
		return -4;
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
