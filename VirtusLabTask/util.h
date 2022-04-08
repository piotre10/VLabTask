#pragma once

#include "DataFrame.h"
#include "DfException.h"

DataFrame* ReadFromCsv(std::string FilePath);
void WriteToCsv(std::string FilePath, DataFrame df);

DataFrame InnerJoin(DataFrame df1, DataFrame df2);
DataFrame LeftOuterJoin(DataFrame df1, DataFrame df2);
DataFrame RightOuterJoin(DataFrame df1, DataFrame df2);




