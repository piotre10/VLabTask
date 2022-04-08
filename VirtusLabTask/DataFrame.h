#pragma once

#include "DfItem.h"
#include <vector>

class DataFrame
{
private:
	std::vector<DfItem> records; // first record consists of labels/titles

public:
	DataFrame();
	DataFrame(DfItem header);
	DataFrame(std::vector<std::string> header);
	DataFrame(const DataFrame& df);
	~DataFrame();

	DataFrame& operator = (const DataFrame& df);
	friend std::istream& operator >> (std::istream& in, DataFrame& df);
	friend std::ostream& operator << (std::ostream& out, DataFrame& df);
	const DfItem& operator [] (int index) const;
	DfItem& operator [] (int index);

	void AddRecord(DfItem record);
	DfItem PopRecord(int index);
	int FindRecord(DfItem record);
	void SortByColumn(int ColId, int l = -1, int p = -1);
	void SortByColumn(std::string ColName);
	int FindColId(std::string ColName);
	void SwapColumns(int id1, int id2);
	void SwapRecords(int id1, int id2);
	void StripNulls(int ColId);
	void RemoveColumn(int ColId);
	int GetSize();
};

