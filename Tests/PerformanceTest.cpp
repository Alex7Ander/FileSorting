#include <iostream>
#include <chrono>
#include <string>
#include <gtest/gtest.h>
#include <SortingFunctions.h>

using namespace std;

chrono::duration<float> SortingProcedure(string initialFilePath, string savingFilePath, int ramLimit){

	auto start = chrono::high_resolution_clock::now();

	cout << "Initial file is " << initialFilePath << endl;
	cout << "Sorted file will ba saved in: " << savingFilePath << endl;
	cout << "RAM limit is: " << ramLimit << endl;
	ramLimit *= 1024;
	ramLimit *= 1024;

	condition_variable nextStep;
	ifstream fIn;
	fIn.open(initialFilePath);
	if (fIn.is_open()){
		fIn.close();
		FileSorter *sorter = new FileSorter(initialFilePath, savingFilePath, ramLimit);	
		thread splittingThread((&FileSorter::SplitingIntoSortedParts), sorter, std::ref(nextStep));		
		char stepSymbols[] = "----------";
		int step = 0;		
		do{			
			if (step>9){ 
				step = 0;
				for(int i=0; i<10; i++) stepSymbols[i] = '-';
			}
			stepSymbols[step] = '+';
			step++;

			mutex mtx;
			unique_lock<mutex> uLock(mtx);
			nextStep.wait(uLock);
			cout << "Splitting " << stepSymbols << "\r";
			cout.flush();
		}while(!sorter->getSplittedStatus());
		splittingThread.join();
		cout << "\r=== Splitting done ===" << endl;

		for(int i=0; i<10; i++) stepSymbols[i] = '-';
		thread mergingThread((&FileSorter::MergeFiles), sorter, std::ref(nextStep));
		step = 0;
		do{			
			if (step>9){ 
				step = 0;
				for(int i=0; i<10; i++) stepSymbols[i] = '-';
			}
			stepSymbols[step] = '+';
			step++;

			mutex mtx;
			unique_lock<mutex> uLock(mtx);
			nextStep.wait(uLock);
			cout << "Merging " << stepSymbols << "\r";
			cout.flush();
		}while(!sorter->getMergedStatus());
		mergingThread.join();
		cout << "\r=== Merging done ===" << endl;
		auto stop = chrono::high_resolution_clock::now();
		chrono::duration<float> duration = stop - start;
		return duration;
	}
	else{
		cout << "Error opening file! Maybe it doesn't exist anymore?" << endl;
		auto stop = chrono::high_resolution_clock::now();
		chrono::duration<float> duration = stop - start;
		return duration;
	}		
}

TEST(PerformanceTest, timeOfFullWorking)
{
	string initialFilePath = "fileForPerformanceTest";
	string savingFilePath = "OutOfPerformanceTest";
	int ramLimit = 4;
	auto duration = SortingProcedure(initialFilePath, savingFilePath, ramLimit);
	cout << "Time of working is :" << duration.count() << endl;
}

TEST(PerformanceTest, wrongPath)
{
	string initialFilePath = "wrongfileForPerformanceTest";
	string savingFilePath = "OutOfPerformanceTest";
	int ramLimit = 4;
	auto duration = SortingProcedure(initialFilePath, savingFilePath, ramLimit);
	cout << "Time of working till error is :" << duration.count() << endl;
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}