#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <thread>
#include <stdio.h>

using namespace std;

struct mergingFilesStruct{
	string fileName1;
	string fileName2;
	string outName;
};

int  SplitingIntoSortedParts(string initialFileName, vector<string> &outFilesNames, int countOfNumbers, vector<int> &values);
void MergeSorting(vector<int>& array, int left, int right);
void WriteFile(string fileName, vector<int>& data, int size);
void MergeTwoFiles(mergingFilesStruct mergingInfo);
void MergeFiles(vector<string> &fileNames, string SavingFilePath);