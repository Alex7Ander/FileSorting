#include <iostream>
#include <thread>

#include "SortingFunctions.h"

using namespace std;

int main(int argc, char* argv[])
{
	string initialFilePath;
	string savingFilePath;
	int ramLimit;
    
	if (argc==4){
		initialFilePath = argv[1];
		savingFilePath = argv[2];
		ramLimit = atoi(argv[3]);
		cout << "Initial file is " << initialFilePath << endl;
		cout << "Sorted file will ba saved in: " << savingFilePath << endl;
		cout << "RAM limit is: " << ramLimit << endl;
		ramLimit *= 1024;
		ramLimit *= 1024;
		int availableSize = ramLimit / 2;

		int CountOfNumbers = availableSize / sizeof(int);
		vector<int> ValuesNumbers;
		vector<string> OutFilesNames;
	
		int resOfSpliting = SplitingIntoSortedParts(initialFilePath, OutFilesNames, CountOfNumbers, ValuesNumbers);
		if (!resOfSpliting){ 
			cout << "Error opening file! Maybe it doesn't exist anymore?" << endl;
			return -2;
		}
		else{
			MergeFiles(OutFilesNames, savingFilePath);
			cout << "Done" << endl;
			return 0;
		}		
	}
	else{
		cout << "Wrong parametrs" << endl;
		return -1;
	}
}