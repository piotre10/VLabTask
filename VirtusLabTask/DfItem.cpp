#include "DfItem.h"
#include "DfException.h"
#include "util.h"
#include <sstream>

DfItem::DfItem(int NumFields)
{
	for (int i = 0; i < NumFields; i++) 
		fields.push_back(NULL_FIELD);
}

DfItem& DfItem::operator = (const DfItem& it)
{
	fields = it.GetFields();
	return *this;
}
std::istream& operator >> (std::istream& in, DfItem& dfit)
{
	std::string buff,temp;

	getline(in, buff);

	std::stringstream ss;
	ss << buff;

	dfit.Clear();

	while (!ss.eof())
	{
		getline(ss, temp, DELIM);
		dfit.AddField(StripQuotes(temp));
	}

	return in;
}
	
std::ostream& operator << (std::ostream& out, const DfItem& dfit)
{

	for (auto field =dfit.fields.begin(); field < dfit.fields.end() - 1; field++)
	{
		if (*field != NULL_FIELD)
			out << (*field);
		out << DELIM;
	}
	auto field = dfit.fields.end() - 1;
	if (*field != NULL_FIELD)
		out << (*field);

	return out;
}

DfItem operator + (const DfItem& it1, const DfItem& it2)
{
	std::vector<std::string> v1, v2;
	v1 = it1.GetFields();
	v2 = it2.GetFields();
	v1.insert(v1.end(), v2.begin(), v2.end());
	DfItem res(v1);
	return res;
}

bool operator == (const DfItem& it1, const DfItem& it2)
{
	if (it1.GetSize() != it2.GetSize())
		return 0;

	if (it1.GetFields() == it2.GetFields())
		return 1;

	return 0;
}

const std::string& DfItem::operator [] (int index) const
{
	if (index < 0 || index >= GetSize())
		throw DfException(ERR_INVALID_INDEX);

	return fields[index];
}

std::string& DfItem::operator [] (int index)
{
	if (index < 0 || index >= GetSize())
		throw DfException(ERR_INVALID_INDEX);

	return fields[index];
}

int DfItem::FindValue(std::string value) const
{
	for (int i = 0; i < GetSize(); i++)
		if ((*this)[i] == value)
			return i;

	return -1;
}
