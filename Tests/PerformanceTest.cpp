#include <iostream>
#include <chrono>
#include <string>
#include <gtest/gtest.h>
#include <SortingFunctions.h>

using namespace std;

chrono::duration<float> SortingProcedure(string initialFilePath, string savingFilePath, int ramLimit){
	auto start = chrono::high_resolution_clock::now();

	ramLimit *= 1024; // MByte -> kByte
	ramLimit *= 1024; // kByte -> Byte
		
	ifstream fIn;
	FileSorter sorter(initialFilePath, savingFilePath, ramLimit);
	int result = sorter();
	if (!result){
		cout << endl <<"DONE!" << endl;
		auto stop = chrono::high_resolution_clock::now();
		return stop - start;
	}
	else{
		cout << endl << "ERROR!" << endl;
		auto stop = chrono::high_resolution_clock::now();
		return stop - start;		
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