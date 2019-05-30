#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <stdio.h>

using namespace std;

class FileSorter{
private:
	void inline WriteFile(string fileName, vector<int>& data, int size);
	bool splitted;
	bool merged;
	string initialFileName;
	string outFileName;
	int ramLimit;
	vector<string> tempOutFilesNames;
	int countOfValues;
	vector<int> values;

public:
	FileSorter(string _InitialFileName, string _OutFileName, int _RamLimit) :
	initialFileName(_InitialFileName), outFileName(_OutFileName), ramLimit(_RamLimit){
		countOfValues = ramLimit/(2*sizeof(int));
		splitted = false;
		merged = false;
	}
	bool getSplittedStatus(){return splitted;}
	bool getMergedStatus(){return merged;}

	void SplitingIntoSortedParts(condition_variable &NextStep);
	void MergeFiles(condition_variable &NextStep);

	void MergeSorting(vector<int>& array, int left, int right);	
	void MergeTwoFiles(string fileName1, string fileName2, string outName);
};