#pragma once

#include "DfItem.h"
#include <vector>

class DataFrame
{
	std::vector<DfItem> records; // first record consists of labels/titles

	DataFrame(DfItem header);
	DataFrame(std::vector<std::string> header);

	const DfItem& operator [] (int index) const;
	DfItem& operator [] (int index);

	void AddRecord(DfItem record);
	DfItem PopRecord(int index);
	int FindRecord(DfItem record);
	void SortByColumn(int ColId);
	void SortByColumn(std::string ColName);
	int FindColId(std::string ColName);

};

