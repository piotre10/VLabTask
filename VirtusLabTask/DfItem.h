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
	DfItem(std::vector<std::string> FieldsVec){ fields = FieldsVec; };
	DfItem(const DfItem&  it){ (*this) = it; };
	virtual ~DfItem() {};

	DfItem& operator = (const DfItem& it);
	friend std::istream& operator >> (std::istream& in, DfItem& dfit);
	friend std::ostream& operator << (std::ostream & out, const DfItem& dfit);
	friend DfItem operator + (const DfItem& it1, const DfItem& it2);
	friend bool operator == (const DfItem& it1, const DfItem& it2);
	friend bool operator != (const DfItem& it1, const DfItem& it2) { return !(it1 == it2); };
	const std::string& operator [] (int index) const;
	std::string& operator [] (int index);

	int GetSize() const { return (int)fields.size(); };
	int FindValue(std::string value) const;
	void SwapFields(int id1, int id2){ std::swap((*this)[id1], (*this)[id2]); };
	void RemoveField(int index = 0) { fields.erase(std::next(fields.begin(), index)); };
	void Clear() { while (GetSize() > 0) RemoveField(); };
	void AddField(std::string val){ fields.push_back(val); };
	std::vector<std::string> GetFields() const { return fields; };
};

