#include "util.h"
#include <fstream>



DataFrame* ReadFromCsv(std::string FilePath)
{
	std::ifstream fin;
	fin.open(FilePath);
	if (!fin.good())
		throw DfException(ERR_FILE);
	DataFrame* pRes = new DataFrame;
	fin >> (*pRes);
	return pRes;
}
void WriteToCsv(std::string FilePath, DataFrame df)
{
	std::ofstream fout;
	fout.open(FilePath);
	if (!fout.good())
		throw DfException(ERR_FILE);
	fout << df;
}

DataFrame InnerJoin(DataFrame df1, DataFrame df2, std::string ColName)
{
	int ColId1 = df1.FindColId(ColName);
	int ColId2 = df2.FindColId(ColName);
	df1.SortByColumn(ColId1);
	df2.SortByColumn(ColId2);

	DfItem record;

	DfItem temp = df2[0];
	temp.RemoveField(ColId2);
	record = df1[0] + temp;
	DataFrame res(record);

	int i = 1, j = 1;
	
	while (i < df1.GetSize() && j < df2.GetSize())
	{
		if (df1[i][ColId1].compare(df2[j][ColId2]) < 0)
			i++;

		else if (df1[i][ColId1].compare(df2[j][ColId2]) > 0)
			j++;
		else
		{
			int temp = j;
			while (j < df2.GetSize() && df1[i][ColId1] == df2[j][ColId2])
			{
				DfItem temp = df2[j];
				temp.RemoveField(ColId2);
				record = df1[i] + temp;
				res.AddRecord(record);
				j++;
			}
			j = temp;
			i++;
		}
		
	}

	return res;
}
DataFrame LeftOuterJoin(DataFrame df1, DataFrame df2, std::string ColName)
{
	int ColId1 = df1.FindColId(ColName);
	int ColId2 = df2.FindColId(ColName);
	df1.SortByColumn(ColId1);
	df2.SortByColumn(ColId2);

	DfItem record;

	DfItem temp = df2[0];
	temp.RemoveField(ColId2);
	DfItem empty_end(temp.GetSize());
	record = df1[0] + temp;
	DataFrame res(record);

	int i = 1, j = 1;

	while (i < df1.GetSize() && j < df2.GetSize())
	{
		if (df1[i][ColId1].compare(df2[j][ColId2]) < 0)
		{
			res.AddRecord(df1[i] + empty_end);
			i++;
		}

		else if (df1[i][ColId1].compare(df2[j][ColId2]) > 0)
			j++;
		else
		{
			int temp = j;
			while (j < df2.GetSize() && df1[i][ColId1] == df2[j][ColId2])
			{
				DfItem temp = df2[j];
				temp.RemoveField(ColId2);
				record = df1[i] + temp;
				res.AddRecord(record);
				j++;
			}
			j = temp;
			i++;
		}

	}
	while (i < df1.GetSize())
	{
		res.AddRecord(df1[i] + empty_end);
		i++;
	}

	return res;
}
DataFrame RightOuterJoin(DataFrame df1, DataFrame df2, std::string ColName)
{
	return LeftOuterJoin(df2, df1, ColName);
}

std::string StripQuotes(std::string str)
{
	{
		str.erase(remove(str.begin(), str.end(), '"'), str.end());
		return str;
	}
}