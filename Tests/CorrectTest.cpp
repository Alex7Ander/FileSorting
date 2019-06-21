#include <iostream>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>
#include <SortingFunctions.h>

using namespace std;

TEST(CorrectTest, TestOfSortingFile)
{
	ifstream testFile;
	testFile.open("./sortedTestFile");
	if (testFile.is_open()){
		int prevValue;
		testFile >> prevValue;
		while(!testFile.eof()){
			int currentValue;
			testFile >> currentValue;
			ASSERT_TRUE(prevValue <= currentValue);
			prevValue = currentValue;
		}
	}
	else{
		cout << "NO File" << endl;
		ASSERT_TRUE(false);
	}
}

int main(int argc, char **argv)
{
	cout << "Let's start testing!!!" << endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}