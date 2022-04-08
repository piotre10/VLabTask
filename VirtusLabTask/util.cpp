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

DataFrame InnerJoin(DataFrame df1, DataFrame df2);
DataFrame LeftOuterJoin(DataFrame df1, DataFrame df2);
DataFrame RightOuterJoin(DataFrame df1, DataFrame df2);