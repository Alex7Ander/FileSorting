#include "SortingFunctions.h"

using namespace std;

int main(int argc, char* argv[])
{
	string initialFilePath;
	string savingFilePath;
	int ramLimit;
	/// Большая и ненужная вложенность if-ов
	if (argc==4){
		initialFilePath = argv[1];
		savingFilePath = argv[2];
		ramLimit = atoi(argv[3]); /// Нет проверки на ошибки
		cout << "Initial file is " << initialFilePath << endl;
		cout << "Sorted file will be saved in: " << savingFilePath << endl;
		cout << "RAM limit is: " << ramLimit << endl;
		ramLimit *= 1024; // MByte -> kByte
		ramLimit *= 1024; // kByte -> Byte
		
		condition_variable nextStep;
		ifstream fIn;
		fIn.open(initialFilePath);
		if (fIn.is_open()){
			fIn.close();
			/// Во-первых, эта переменная не освобождается, во-вторых, непонятно зачем нужно динамическое выделение памяти
			FileSorter *sorter = new FileSorter(initialFilePath, savingFilePath, ramLimit);	
			/// Ненужная многопоточность
			thread splittingThread((&FileSorter::SplitingIntoSortedParts), sorter, std::ref(nextStep));		
			char stepSymbols[] = "----------";
			int step = 0;		
			do{			
				if (step>9){ /// magic number
					step = 0;
					for(int i=0; i<10; i++) stepSymbols[i] = '-'; /// magic number
				}
				stepSymbols[step] = '+';
				step++;

				mutex mtx;
				unique_lock<mutex> uLock(mtx);
				nextStep.wait(uLock);
				/// Может в этом месте просто печатать нужное кол-во "+" и "-" и избавится от переменной stepSymbols
				cout << "Splitting " << stepSymbols << "\r";
				cout.flush();
			}while(!sorter->getSplittedStatus()); /// Использование конструкции do ... while плохая практика, т.к. усложняет чтение кода
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
				/// Дублирование кода
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