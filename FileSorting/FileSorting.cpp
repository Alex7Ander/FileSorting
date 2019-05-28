#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <thread>
#include <stdio.h>

using namespace std;

struct mergingFilesStruct{
	string fileName1;
	string fileName2;
	string outName;
};

void MergeSorting(vector<int>& array, int left, int right);
int  FileSize(string fileName);
int  SplitingIntoSortedParts(string initialFileName, vector<string> &outFilesNames, int countOfNumbers, vector<int> &values);
void WriteFile(string fileName, vector<int>& data, int size);
void MergeTwoFiles(mergingFilesStruct mergingInfo);
void MergeFiles(vector<string> &fileNames, string SavingFilePath);

int main(int argc, char* argv[])
{
	cout << "Version of 27.05 (1)" << endl;
	string initialFilePath;
	string savingFilePath;
	int ramLimit;
    
	if (argc==4){
		cout << "START" << endl; 
		initialFilePath = argv[1];
		savingFilePath = argv[2];
		ramLimit = atoi(argv[3]);
		cout << "Initial file is " << initialFilePath << endl;
		cout << "Sorted file will ba saved in: " << savingFilePath << endl;
		cout << "RAM limit is: " << ramLimit << endl;
		ramLimit *= 1024;
		ramLimit *= 1024;
		int availableSize = ramLimit / 2;

		int fromIndex = 0;
		int fileIndex = 0;

		int CountOfNumbers = availableSize / sizeof(int);
		vector<int> ValuesNumbers;
		vector<string> OutFilesNames;
	
		int resOfSpliting = SplitingIntoSortedParts(initialFilePath, OutFilesNames, CountOfNumbers, ValuesNumbers);
		if (!resOfSpliting) 
			std::cout << "Error opening file! Maybe it doesn't exist anymore?" << std::endl;
		
		MergeFiles(OutFilesNames, savingFilePath);
		std::cout << "Done" << endl;
		
		return 0;
	}
	else{
		cout << "Wrong parametrs" << endl;
		return -1;
	}
}

int FileSize(string fileName)
{
	ifstream fIn;
	fIn.open(fileName.c_str());
	int size = 0;
	fIn.seekg(0, std::ios::end);
	size = fIn.tellg();
	fIn.close();
	return size;
}

int SplitingIntoSortedParts(string fileName, vector<string> &outFilesNames, int countOfNumbers, vector<int> &values)
{
	ifstream fIn;
	int countOfRead = 0;
	fIn.open(fileName.c_str());
	if (fIn.is_open()) {
		values.clear();
		char buffer[20];		
		int countOfParts = 0;
		std::cout << "Start splitting" << std::endl;
		while (!fIn.eof()){			
			values.clear();
			for (int i = 0; i < countOfNumbers; i++){
				if (!fIn.eof()){
					fIn >> buffer;
					int value = atoi(buffer);
					values.push_back(value);
				}
				else{
					break;
				}								
			}
			countOfParts++;
			std::cout << "Part number " << countOfParts + 1 << " was read\t";
			MergeSorting(values, 0, values.size()-1);
			std::cout << "sorted\t";
			stringstream numStr;
			numStr << countOfParts;
			string fileOutPath = "sFile" + numStr.str();
			WriteFile(fileOutPath.c_str(), values, values.size());
			outFilesNames.push_back(fileOutPath);
			std::cout << "writen." << std::endl << "------------------------" << std::endl;
		}
		return countOfParts;
	}
	else {
		return -1;
	}
}

void WriteFile(string fileName, vector<int>& data, int size)
{
	ofstream fOut;
	fOut.open(fileName.c_str());
	for (int i = 0; i < size-1; i++) {
		fOut << data[i];
		if ((i + 1) % 10 == 0) fOut << "\n";
		else fOut << "\t";
	}
	fOut << data[size-1];
	//fOut << endl;
	fOut.close();
	return;
}

void MergeSorting(vector<int> & array, int left, int right)
{
	if (left == right) return;
	if (right - left == 1) {
		if (array[left] > array[right]) swap(array[left], array[right]);
		return;
	}
	int mid = (right + left) / 2;
	MergeSorting(array, left, mid);
	MergeSorting(array, mid + 1, right);
	vector<int> tempArray;
	int i = left;
	int j = mid + 1;
	for (int step = 0; step < right - left + 1; step++) {
		if ((j > right) || ((i <= mid) && (array[i] < array[j]))) {
			tempArray.push_back(array[i]);
			i++;
		}
		else {
			tempArray.push_back(array[j]);
			j++;
		}
	}
	for (int step = 0; step < right - left + 1; step++)
		array[left + step] = tempArray[step];
}

void MergeTwoFiles(mergingFilesStruct mergingInfo)
{	
	ifstream file1;
	ifstream file2;
	file1.open(mergingInfo.fileName1.c_str());
	file2.open(mergingInfo.fileName2.c_str());
	if (file1.is_open() && file2.is_open()){
		ofstream fileOut;
		fileOut.open(mergingInfo.outName.c_str());
		if (fileOut.is_open()){
			bool stepFile1 = true; //флаг, указывающий на то, что надо прочитать следующее значение из 1-го файла
			bool stepFile2 = true; //аналогично но для 2-го файла
			int value1;
			int value2;
			int counter = 0;
			bool stop = false;
			while (true){
				char buff[20];
				//если необходимо прочитать значение из 1-го файла
				if (stepFile1){					
					if (file1.eof()){ 	//если дошли до конца файла, то прерываем цикл сравнений
						fileOut << value2;	
						counter++;
						if (!file2.eof()){
							if ((counter + 1) % 10 == 0) fileOut << "\n";
							else fileOut << "\t";	
							while(true){
								file2 >> buff;
								value2 = atoi(buff);
								fileOut << value2;
								counter++;	
								if (file2.eof()) break;	
								if ((counter + 1) % 10 == 0) fileOut << "\n";
								else fileOut << "\t";						
							}
						}
						break;
					}
					file1 >> buff;
					value1 = atoi(buff);
				}
				//а если необходимо прочитать значение из 2-го файла
				if (stepFile2){					
					if (file2.eof()){	
						fileOut << value1;
						counter++;
						if (!file1.eof()){
							if ((counter + 1) % 10 == 0) fileOut << "\n";
							else fileOut << "\t";	
							while(true){
								file1 >> buff;
								value1 = atoi(buff);
								fileOut << value1;
								counter++;		
								if (file1.eof()) break;
								if ((counter + 1) % 10 == 0) fileOut << "\n";
								else fileOut << "\t";
							}
						}
						break;
					}
					file2 >> buff;
					value2 = atoi(buff);
				}
				//сравниваем и меньшее или равное записываем в новый файл
				if (value1 < value2){
					stepFile1 = true; //если в 1-м фале было наименьшее значение, то из 1-го файла надо будет прочитать следующее
					stepFile2 = false; //а из 2-го не надо
					fileOut << value1; //записывам его
				}
				else{
					stepFile1 = false;
					stepFile2 = true;					
					fileOut << value2;
				}
				if ((counter + 1) % 10 == 0) fileOut << "\n";
				else fileOut << "\t";
				counter++;
			}
			file1.close();
			file2.close();
			fileOut.close();
		} //end if (fileOut.is_open())
	}// end if (file1.is_open() && file2.is_open())

	cout << "Out file is " << mergingInfo.outName.c_str() << endl;
}

void MergeFiles(vector<string> &fileNames, string SavingFilePath)
{
	int mergeCounter = 1;
	queue<string> mergingFiles;
	for (int i=0; i<fileNames.size(); i++)
		mergingFiles.push(fileNames[i]);

	do{
		int countOfThreads = mergingFiles.size()/2;
		vector<thread*> mergingThreads;

		for (int i=0; i<countOfThreads; i++){
			mergingFilesStruct mergingStruct;
			mergingStruct.fileName1 = mergingFiles.front();
			mergingFiles.pop();
			mergingStruct.fileName2 = mergingFiles.front();
			mergingFiles.pop();	
			stringstream numStr;
			numStr << mergeCounter;
			mergingStruct.outName = "sFile_" + numStr.str();
			fileNames.push_back(mergingStruct.outName);
			mergingFiles.push(mergingStruct.outName);

			cout << "Thread #" << mergeCounter << ".\t Merging of " <<  mergingStruct.fileName1.c_str() << " and " << mergingStruct.fileName2.c_str() << " into " << mergingStruct.outName.c_str() << endl;
			thread *mergThread = new thread(MergeTwoFiles, mergingStruct);
			mergingThreads.push_back(mergThread);
			mergingThreads[i]->join();
			mergeCounter++;
		}
	}while (mergingFiles.size()>1);

	string oldName = fileNames[fileNames.size() - 1];
	rename(oldName.c_str(), SavingFilePath.c_str());
	for (int i=0; i<fileNames.size()-1; i++) {
		cout << "Deleteing of " << fileNames[i].c_str() << endl;
		remove(fileNames[i].c_str());
	}
}