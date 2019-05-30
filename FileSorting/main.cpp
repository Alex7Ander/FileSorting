#include "SortingFunctions.h"

using namespace std;

//condition_variable nextStep;

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
			return 0;
		}
		else{
			cout << "Error opening file! Maybe it doesn't exist anymore?" << endl;
			return -2;
		}		
	}
	else{
		cout << "Wrong parametrs" << endl;
		return -1;
	}
}