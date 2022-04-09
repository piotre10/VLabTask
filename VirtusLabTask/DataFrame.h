#pragma once

#include "DfItem.h"
#include <vector>

class DataFrame
{
private:
	std::vector<DfItem> records; // first record consists of labels/titles

public:
	DataFrame();
	DataFrame(DfItem header) { records.push_back(header); };
	DataFrame(std::vector<std::string> header) { records.push_back(DfItem(header)); };
	DataFrame(const DataFrame& df) { *this = df; };
	virtual ~DataFrame() {};

	DataFrame& operator = (const DataFrame& df);
	friend std::istream& operator >> (std::istream& in, DataFrame& df);
	friend std::ostream& operator << (std::ostream& out, const DataFrame& df);
	const DfItem& operator [] (int index) const;
	DfItem& operator [] (int index);

	void AddRecord(DfItem record);
	DfItem PopRecord(int index);
	int FindRecord(DfItem record) const;
	void SortByColumn(int ColId, int l = -1, int p = -1);
	void SortByColumn(std::string ColName) { SortByColumn(FindColId(ColName)); };
	int FindColId(std::string ColName) const { return (*this)[0].FindValue(ColName); };
	void SwapColumns(int id1, int id2);
	void SwapRecords(int id1, int id2);
	void StripNulls(int ColId);
	void RemoveColumn(int ColId) { for (auto record : records) record.RemoveField(ColId); };
	int GetSize() const { return (int)records.size(); };
};

