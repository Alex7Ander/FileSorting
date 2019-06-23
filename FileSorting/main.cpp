#include "SortingFunctions.h"

using namespace std;

int main(int argc, char* argv[])
{
	string initialFilePath;
	string savingFilePath;
	int ramLimit;

	if (argc!=4){
		cout << "\033[33mWrong parametrs\033[0m" << endl;
		cout << "\033[32mFileSorting [InitialFilePath] [sortedFilePath] [RAM_limit]\033[0m" <<endl;
		return -1;
	}

	initialFilePath = argv[1];
	savingFilePath = argv[2];
	ramLimit = atoi(argv[3]); 
	if (ramLimit<1){
		cout << "\033[33mWrong value of RAM limit\033[0m" << endl;
		return -1;
	} 

	cout << "\033[32mInitial file is \033[0m" << initialFilePath << endl;
	cout << "\033[32mSorted file will be saved in: \033[0m" << savingFilePath << endl;
	cout << "\033[32mRAM limit is: \033[0m" << ramLimit << endl;
	ramLimit *= 1024; // MByte -> kByte
	ramLimit *= 1024; // kByte -> Byte
		
	ifstream fIn;
	FileSorter sorter(initialFilePath, savingFilePath, ramLimit, Monitor::getInstanceMonitor());
	int result = sorter.makeSorting();
	if (!result){
		cout << endl <<"\033[32mDONE!\033[0m" << endl;
	}
	else{
		cout << endl << "\033[33mERROR!\033[0m" << endl;
	}
	return result;
}