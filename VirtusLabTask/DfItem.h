#pragma once

#include <vector>
#include <string>


#define NULL_FIELD ""
#define DELIM ','

class DfItem
{
private:
	std::vector<std::string> fields;

public:
	DfItem(int NumFields = 1);
	DfItem(std::vector<std::string> FieldsVec);
	DfItem(const DfItem&  it);
	~DfItem() {};

	DfItem& operator = (const DfItem& it);
	friend std::istream& operator >> (std::istream& in, DfItem& dfit);
	friend std::ostream& operator << (std::ostream & out, DfItem& dfit);
	friend bool operator == (const DfItem& it1, const DfItem& it2);
	friend bool operator != (const DfItem& it1, const DfItem& it2);
	friend DfItem operator + (const DfItem& it1, const DfItem& it2);
	const std::string& operator [] (int index) const;
	std::string& operator [] (int index);

	int GetSize() const{ return fields.size(); };
	int FindValue(std::string value);
	void SwapFields(int id1, int id2);
	void RemoveField(int index=0);
	void Clear();
	void AddField(std::string val);
	std::vector<std::string> GetFields() const;
};

