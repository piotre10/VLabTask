#include "DataFrame.h"
#include "DfException.h"

DataFrame::DataFrame()
{
	DfItem head;
	(*this) = DataFrame(head);
}

DataFrame& DataFrame::operator = (const DataFrame& df)
{
	records = df.records;
	return *this;
}
std::istream& operator >> (std::istream& in, DataFrame& df)
{
	DfItem temp;
	in >> temp;
	df = DataFrame(temp);
	while (in >> temp)
		df.AddRecord(temp);
	return in;
}
std::ostream& operator << (std::ostream& out, const DataFrame& df)
{
	if (df.GetSize() <= 0)
		return out;
	for (auto record : df.records)
		out << record << std::endl;
	return out;
}

const DfItem& DataFrame::operator [] (int index) const
{
	if (index >= 0 && index < GetSize())
		return  records[index];

	throw DfException(ERR_INVALID_INDEX);
}
DfItem& DataFrame::operator [] (int index)
{
	if (index >= 0 && index < GetSize())
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
	if (index > 0 && index < GetSize())
		return  (*this)[index];

	throw DfException(ERR_INVALID_INDEX);
}
int DataFrame::FindRecord(DfItem recordtofind) const
{
	int i = 0;
	for (const auto& rec : records)
	{
		if (rec == recordtofind) return i;
		i++;
	}
	return -1;
}

void DataFrame::SortByColumn(int ColId, int l, int p)
{
	if (l == -1)
		l = 1;
	if (p == -1)
		p = GetSize() - 1;

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

void DataFrame::SwapColumns(int id1, int id2)
{
	for (auto record : records)
		record.SwapFields(id1, id2);
}
void DataFrame::SwapRecords(int id1, int id2)
{
	if (id1 == 0 || id2 == 0)
		throw DfException(ERR_CANT_MOVE_HEADER);

	std::swap((*this)[id1], (*this)[id2]);
}

void DataFrame::StripNulls(int ColId)
{
	for (auto pRec = records.begin(); pRec < records.end(); pRec++)
		if ((*pRec)[ColId] == NULL_FIELD)
			records.erase(pRec);
}

