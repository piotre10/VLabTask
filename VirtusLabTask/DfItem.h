#pragma once

#include <vector>
#include <string>

class DfItem
{
private:
	int NoFields;
	std::string* fields;

public:
	DfItem(int NumFields);
	DfItem(std::vector<std::string> FieldsVec);
	~DfItem();

	friend bool operator == (const DfItem& it1, const DfItem& it2);
	friend bool operator != (const DfItem& it1, const DfItem& it2);
	const std::string& operator [] (int index) const;
	std::string& operator [] (int index);

	int GetSize() { return NoFields; };
	int FindValue(std::string value);
	void SwapFields(int id1, int id2);

};

