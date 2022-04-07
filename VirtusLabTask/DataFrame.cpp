#include "DataFrame.h"
#include "DfException.h"

DataFrame::DataFrame(DfItem header)
{
	records.push_back(header);
}
DataFrame::DataFrame(std::vector<std::string> header)
{
	records.push_back(DfItem(header));
}

const DfItem& DataFrame::operator [] (int index) const
{
	if (index >= 0 && index < records.size())
		return  records[index];

	throw DfException(ERR_INVALID_INDEX);
}
DfItem& DataFrame::operator [] (int index)
{
	if (index >= 0 && index < records.size())
		return  records[index];

	throw DfException(ERR_INVALID_INDEX);
}

void DataFrame::AddRecord(DfItem record)
{
	if ((*this)[0].GetSize() != record.GetSize())
		throw DfException(ERR_INCOMPATIBLE_SIZE);

	records.push_back(record);
}

DfItem DataFrame::PopRecord(int index)
{
	if (index > 0 && index < records.size())
		return  (*this)[index];

	throw DfException(ERR_INVALID_INDEX);
}
int DataFrame::FindRecord(DfItem recordtofind)
{
	int i = 0;
	for (const auto& rec : records)
	{
		if (rec == recordtofind)
			return i;

		i++;
	}
	return -1;

}
void DataFrame::SortByColumn(int ColId)
{

}
void DataFrame::SortByColumn(std::string ColName)
{
	SortByColumn(FindColId(ColName);
}
int DataFrame::FindColId(std::string ColName)
{
	return (*this)[0].FindValue(ColName);
}