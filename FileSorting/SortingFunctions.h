#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <thread>
#include <algorithm>
#include <iterator>
#include <stdio.h>

using namespace std;

class Monitor
{
private:
	string empty;
	int prevLenght;
	static Monitor *instanceMonitor;

	Monitor(){
		prevLenght = 0;		
	}
	void setEmptyString(){
		empty.clear();
		for (int i = 0; i < prevLenght; i++)
			empty.push_back(' ');
	}

public:
	static Monitor *getInstanceMonitor(){
		if (instanceMonitor == nullptr){
			instanceMonitor = new Monitor();
		}
		return instanceMonitor;
	}

	void ShowMessage(string _Message){
		Monitor::setEmptyString();
		cout << empty << "\r";
		cout<< _Message.c_str()  << "\r";
		prevLenght = _Message.length();
		cout.flush();
	}
};

class FileSorter{
private:
	Monitor *monitor;
	string initialFileName;
	string outFileName;
	queue<string> mergingFiles;
	int countOfValues;

	void inline WriteFile(const string& fileName, const vector<int>& data);
	int inline MergeTwoFiles(const string fileName1, const string fileName2, const string outName);

	int SplitingIntoSortedParts();
	int MergeFiles();

public:
	FileSorter(string _InitialFileName, string _OutFileName, int _RamLimit, Monitor* _ExternalMonitor) :
	initialFileName(_InitialFileName), outFileName(_OutFileName), monitor(_ExternalMonitor){
		countOfValues = _RamLimit/(sizeof(int));
	}
	int makeSorting();
};