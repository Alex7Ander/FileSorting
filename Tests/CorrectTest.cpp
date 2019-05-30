#include <iostream>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>
#include <SortingFunctions.h>

using namespace std;

void FillUnsortedIntVector(vector<int> &Values, int size){
	Values.clear();
	srand(size);
	for (int i=0; i<size; i++){
		bool isExist;
		int val;
		do{
			isExist = false;
			val = rand()%size+1;
			for (int j=0; j<i; j++){
				if(val == Values[j]) {
					isExist = true;
					break;
				}
			}
		}while(isExist);
		Values.push_back(val);
	}
return;
}

void CreateFilesForMerging(string file_1_Name, string file_2_Name, vector<int> &values)
{
	ofstream file1, file2;
	file1.open(file_1_Name.c_str());
	file2.open(file_2_Name.c_str());
	if (file1.is_open() && file2.is_open()){
		int i=0;
		int f1Count = 1;
		int f2Count = 1;
		while(i<values.size()){
			if (i%2==0){
				file1 << values[i];
				if(f1Count!=50){
					if ((f1Count) % 10 == 0) file1 << "\n";
					else file1 << "\t";
					f1Count++;
				}
			} 
			else {
				file2 << values[i];
				if(f2Count!=50){
					if ((f2Count) % 10 == 0) file2 << "\n";
					else file2 << "\t";
					f2Count++;
				}
			}
			i++;
		}
		file1.close();
		file2.close();
	}
return;
}

//Тестирование алгоритма сортировки вставками
//применялся для сортировки значений во временных файлах
TEST(SortingAlgTest, _30valuesTest)
{
	vector<int> values;
	int size = 30;
	FillUnsortedIntVector(values, size);
	FileSorter *testSorter = new FileSorter("","", 0);
	testSorter->MergeSorting(values, 0, values.size()-1);
	for (int i=0; i<size; i++){
		int realValue = values[i];
		int expectedValue = i+1;
		ASSERT_TRUE(realValue==expectedValue);
	}
}

//аналогично, но для большего количеств значений, проверка относительно алгоритма из STL
TEST(CorrectTest, TestBySTLSort)
{
	int size = 10000;
	vector<int> realValues(size);
	vector<int> expectedValues(size);
	srand(1);
	int g = 0;
	generate(realValues.begin(), realValues.end(), [](){return rand();});	
	copy(realValues.begin(), realValues.end(), expectedValues.begin());
	FileSorter *testSorter = new FileSorter("","", 0);
	testSorter->MergeSorting(realValues, 0, realValues.size()-1);
	sort(expectedValues.begin(), expectedValues.end());
	for (int i=0; i<size-1; i++){
		ASSERT_TRUE(realValues[i] == expectedValues[i]);
	}
}

//тест алгоритма слияния 2-х файлов
TEST(MergingTest, FileMergingAlgTest)
{
	vector<int> values;
	FillUnsortedIntVector(values, 100);
	sort(values.begin(), values.end());
	CreateFilesForMerging("file_1", "file_2", values);
	FileSorter *testSorter = new FileSorter("","", 0);
	testSorter->MergeTwoFiles("file_1", "file_2", "out_file");
	ifstream fileIn;
	fileIn.open("out_file");
	if(fileIn.is_open()){
		int i = 0;
		while(!fileIn.eof()){
			char buff[10];
			fileIn >> buff;
			int val = atoi(buff);
			ASSERT_TRUE(val == values[i]);
			i++;
		}
	}
	fileIn.close();
}

int main(int argc, char **argv)
{
	cout << "Let's start testing!!!" << endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}