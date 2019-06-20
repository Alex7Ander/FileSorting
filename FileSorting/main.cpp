#include "SortingFunctions.h"

using namespace std;

int main(int argc, char* argv[])
{
	string initialFilePath;
	string savingFilePath;
	int ramLimit;

	if (argc!=4){
		cout << "Wrong parametrs" << endl;
		return -1;
	}

	initialFilePath = argv[1];
	savingFilePath = argv[2];
	ramLimit = atoi(argv[3]); 
	if (ramLimit<1){
		cout << "Limit of RAM can not be less then 1 MByte" << endl;
		return -1;
	} 

	cout << "Initial file is " << initialFilePath << endl;
	cout << "Sorted file will be saved in: " << savingFilePath << endl;
	cout << "RAM limit is: " << ramLimit << endl;
	ramLimit *= 1024; // MByte -> kByte
	ramLimit *= 1024; // kByte -> Byte
		
	ifstream fIn;
	FileSorter sorter(initialFilePath, savingFilePath, ramLimit);
	int result = sorter();
	if (!result){
		cout << endl <<"DONE!" << endl;
	}
	else{
		cout << endl << "ERROR!" << endl;
	}
	return result;
}