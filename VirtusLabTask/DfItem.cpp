#include "DfItem.h"
#include "DfException.h"

DfItem::DfItem(int NumFields)
{
	NoFields = NumFields;
	fields = new(std::nothrow) std::string[NoFields];
	if (!fields)
		throw DfException(ERR_ALLOCATION);
}
DfItem::DfItem(std::vector<std::string> FieldsVec)
{
	NoFields = FieldsVec.size();
	fields = new(std::nothrow) std::string[NoFields];
	if (!fields)
		throw DfException(ERR_ALLOCATION);
	std::copy(FieldsVec.begin(), FieldsVec.end(), fields);
}

DfItem::~DfItem()
{
	delete[] fields;
}

bool operator == (const DfItem& it1, const DfItem& it2)
{
	if (it1.NoFields != it2.NoFields)
		return 0;

	for (int i = 0; i < it1.NoFields; i++)
		if (it1[i] != it2[i])
			return 0;

	return 1;
}
bool operator != (const DfItem& it1, const DfItem& it2)
{
	return !(it1 == it2);
}

const std::string& DfItem::operator [] (int index) const
{
	if (index < 0 || index >= NoFields)
		throw DfException(ERR_INVALID_INDEX);

	return fields[index];
}
std::string& DfItem::operator [] (int index)
{
	if (index < 0 || index >= NoFields)
		throw DfException(ERR_INVALID_INDEX);

	return fields[index];
}

int DfItem::FindValue(std::string value)
{
	for (int i = 0; i < NoFields; i++)
		if ((*this)[i] == value)
			return i;

	return -1;
}

void DfItem::SwapFields(int id1, int id2)
{
	std::string temp = (*this)[id1];
	(*this)[id1] = (*this)[id2];
	(*this)[id2] = temp;
}