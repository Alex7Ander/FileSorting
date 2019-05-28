#include <iostream>
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
}

//Тестирование алгоритма сортировки вставками
//применялся для сортировки значений во временных файлах
TEST(CorrectTest, SortingAlgTest)
{
	vector<int> values;
	int size = 30;
	FillUnsortedIntVector(values, size);
	MergeSorting(values, 0, values.size()-1);
	for (int i=0; i<size; i++){
		int realValue = values[i];
		int expectedValue = i+1;
		ASSERT_TRUE(realValue==expectedValue);
	}
}

int main(int argc, char **argv)
{
	cout << "Let's start testing!!!" << endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}