#pragma once

#include "DataFrame.h"
#include "DfException.h"

DataFrame* ReadFromCsv(std::string FilePath);
void WriteToCsv(std::string FilePath, DataFrame df);

DataFrame InnerJoin(DataFrame df1, DataFrame df2, std::string ColName);
DataFrame LeftOuterJoin(DataFrame df1, DataFrame df2, std::string ColName);
DataFrame RightOuterJoin(DataFrame df1, DataFrame df2, std::string ColName);
std::string StripQuotes(std::string str);




