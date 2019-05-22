#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <mutex>
#include <stdio.h>

using namespace std;

void MergeSorting(vector<int>& array, int left, int right);
int  FileSize(string fileName);
int  SplitingIntoSortedParts(string initialFileName, vector<string> &outFilesNames, int countOfNumbers, vector<int> &values);
void WriteFile(string fileName, vector<int>& data, int size);
void MergeTwoFiles(string fileName1, string fileName2, string outName);
void MergeFiles(vector<string> &fileNames, string SavingFilePath);

int main(int argc, char* argv[])
{
	string initialFilePath;
	string savingFilePath;
	int ramLimit;

	if (argc==4){
		initialFilePath = argv[1];
		savingFilePath = argv[2];
		ramLimit = atoi(argv[3]);
		//std::cout << "Input file path, which should be sorted: " << endl;	
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
			string fileOutPath = "C:\\Users\\Alex\\Desktop\\testPartFileReading\\largeFileSorting  20.05\\largeFileSorting\\largeFileSorting\\Sorting\\outFile" + numStr.str();
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
	for (int i = 0; i < size; i++) {
		fOut << data[i];
		if ((i + 1) % 10 == 0) fOut << "\n";
		else fOut << "\t";
	}
	fOut << endl;
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

void MergeTwoFiles(string fileName1, string fileName2, string outName)
{
	ifstream file1;
	ifstream file2;
	file1.open(fileName1);
	file2.open(fileName2);
	if (file1.is_open() && file2.is_open()){
		ofstream fileOut;
		fileOut.open(outName);
		if (fileOut.is_open()){
			bool stepFile1 = true;
			bool stepFile2 = true;
			char buff1[20];
			char buff2[20];
			int value1;
			int value2;
			int counter = 0;
			bool stop = false;
			while (!stop){
				if (stepFile1){
					file1 >> buff1;
					value1 = atoi(buff1);
				}

				if (stepFile2){
					file2 >> buff2;
					value2 = atoi(buff2);
				}

				if (value1 < value2){
					stepFile1 = true;
					stepFile2 = false;
					fileOut << value1;
					if ((counter + 1) % 10 == 0) fileOut << "\n";
					else fileOut << "\t";
				}
				else{
					stepFile2 = true;
					stepFile1 = false;
					fileOut << value2;
					if ((counter + 1) % 10 == 0) fileOut << "\n";
					else fileOut << "\t";
				}
				counter++;

				if ((file1.eof() && stepFile1) || (file2.eof() && stepFile2)) {
					stop = true;
				}
			}

			if (file1.eof()){
				while (!file2.eof()){
					file2 >> buff2;
					value2 = atoi(buff2);
					fileOut << value2;
					if ((counter + 1) % 10 == 0) fileOut << "\n";
					else fileOut << "\t";
					counter++;
				}
			}
			if (file2.eof()) {
				while (!file1.eof()){
					file1 >> buff1;
					value1 = atoi(buff1);
					fileOut << value1;
					if ((counter + 1) % 10 == 0) fileOut << "\n";
					else fileOut << "\t";
					counter++;
				}
			}
			file1.close();
			file2.close();
			fileOut.close();
		} //end if (fileOut.is_open())
	}// end if (file1.is_open() && file2.is_open())
}

void MergeFiles(vector<string> &fileNames, string SavingFilePath)
{
	int stopIndex = 0;
	while (stopIndex != fileNames.size() - 1){
		stringstream numStr;
		numStr << stopIndex;
		string outName = fileNames[stopIndex] + "_" + numStr.str();
		std::cout << outName << endl;
		fileNames.push_back(outName);
		MergeTwoFiles(fileNames[stopIndex], fileNames[stopIndex + 1], outName);
		remove(fileNames[stopIndex].c_str());
		remove(fileNames[stopIndex+1].c_str());
		stopIndex += 2;
	}
	string oldName = fileNames[fileNames.size() - 1];
	rename(oldName.c_str(), SavingFilePath.c_str());
}
