#include "DataFrame.h"
#include "DfException.h"

DataFrame::DataFrame()
{

}
DataFrame::DataFrame(DfItem header)
{
	records.push_back(header);
}
DataFrame::DataFrame(std::vector<std::string> header)
{
	records.push_back(DfItem(header));
}

std::istream& operator >> (std::istream& in, DataFrame df)
{
	DfItem temp;
	in >> temp;
	df = DataFrame(temp);
	while (in >> temp)
		df.AddRecord(temp);
	return in;
}
std::ostream& operator << (std::ostream& out, DataFrame df)
{
	for (auto record : df.records)
		out << record;
	return out;
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
void DataFrame::SortByColumn(int ColId, int l, int p)
{
	if (l == -1)
		l = 1;
	if (p == -1)
		p = records.size() - 1;

	int i = l;
	int j = p;

	std::string x = (*this)[(l + p) / 2][ColId]; //record No (l+p)/2 DfItem field no ColId
	while (i < j)
	{
		while (x.compare((*this)[i][ColId]) > 0) i++; // field < x
		while (x.compare((*this)[j][ColId]) < 0) j--; // field > x
		
		if (i <= j)
		{
			(*this).SwapRecords(i, j);
			i++; j--;
		}
	}
	if (l < j) SortByColumn(ColId, l, j);
	if (i < p) SortByColumn(ColId, i, p);
}
void DataFrame::SortByColumn(std::string ColName)
{
	SortByColumn(FindColId(ColName));
}
int DataFrame::FindColId(std::string ColName)
{
	return (*this)[0].FindValue(ColName);
}
void DataFrame::SwapColumns(int id1, int id2)
{
	for (auto record : records)
		record.SwapFields(id1, id2);
}
void DataFrame::SwapRecords(int id1, int id2)
{
	if (id1 == 0 || id2 == 0)
		throw DfException(ERR_CANT_MOVE_HEADER);
	DfItem temp = (*this)[id1];
	(*this)[id1] = (*this)[id2];
	(*this)[id2] = temp;

}

void DataFrame::StripNulls(int ColId)
{
	for (auto pRec = records.begin(); pRec < records.end(); pRec++)
		if ((*pRec)[ColId] == NULL_FIELD)
			records.erase(pRec);
}