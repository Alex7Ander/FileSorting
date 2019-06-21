#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <algorithm>
#include <iterator>
#include <stdio.h>

using namespace std;
class Monitor
{
public:
	void ShowMessage(string _Message){
		cout<< _Message.c_str()  << endl;
	}

	void ShowProgress(string _ProgressString, int _Progress){
		string empty;
		for (int i = 0; i < (_ProgressString.length() + _Progress + 3); i++)
			empty.push_back(' ');
		cout << empty << "\r";
		cout << _ProgressString.c_str() << ": " << _Progress << "\r";
		cout.flush();
	}
};

/// Этот класс очень плохо спроектирован, все методы публичные, интерфейс плохой
class FileSorter{
private:
	Monitor monitor;
	string initialFileName;
	string outFileName;
	queue<string> mergingFiles;
	int countOfValues;

	void inline WriteFile(const string& fileName, const vector<int>& data);
	int inline MergeTwoFiles(string fileName1, string fileName2, string outName);

	int SplitingIntoSortedParts();
	int MergeFiles();

public:
	FileSorter(string _InitialFileName, string _OutFileName, int _RamLimit) :
	initialFileName(_InitialFileName), outFileName(_OutFileName){
		countOfValues = _RamLimit/(2*sizeof(int));
	}
	int operator()();
};