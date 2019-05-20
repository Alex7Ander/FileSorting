#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>

using namespace std;

void MergeSorting(vector<int>& array, int left, int right);
int  FileSize(string fileName);
int  ReadFilePart(string fileName, int fromIndex, int countOfNumbers, bool &readTillEnd, vector<int> &values);
void WriteFile(string fileName, vector<int>& data, int size);
void MergeTwoFiles(string fileName1, string fileName2, string outName);
void MergeFiles(vector<string> &fileNames);

int main()
{
std::cout << "Input file path, which should be sorted: " << endl;
	string filePath;
	cin >> filePath;
	if (filePath == "0") filePath = "/home/alex/FileForSorting/f";
	int ramLimit;
	std::cout << "Inpit RAM limit, Mb: " << endl;
	cin >> ramLimit;
	ramLimit *= 1024;
	ramLimit *= 1024;
	int availableSize = ramLimit / 2;

	int fromIndex = 0;
	bool ReadTillEnd = false;
	int fileIndex = 0;
	vector<string> fileNames;
	while (!ReadTillEnd){
		std::cout << "Itteration # " << fileIndex << endl;
		int countOfNumbers = availableSize / sizeof(int);
		vector<int> valuesNumbers;

		fromIndex += ReadFilePart(filePath, fromIndex, countOfNumbers, ReadTillEnd, valuesNumbers);
		cout << "File was read" << endl;
		std::cout << "Part number " << fileIndex << " was read \t";
		
		MergeSorting(valuesNumbers, 0, valuesNumbers.size() - 1);
		std::cout << "Sorted \t";

		stringstream numStr;
		numStr << fileIndex;
		string fileOutPath = "/home/alex/FileForSorting/sorted/outFile" + numStr.str();
		WriteFile(fileOutPath.c_str(), valuesNumbers, valuesNumbers.size());
		fileNames.push_back(fileOutPath);
		std::cout << "Writen" << std::endl;
		fileIndex++;
		std::cout << countOfNumbers << endl << "----------------------" << endl;
	}
	MergeFiles(fileNames);
	std::cout << "Done" << endl;
	return 0;
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

int ReadFilePart(string fileName, int fromIndex, int countOfNumbers, bool &readTillEnd, vector<int> &values)
{
	ifstream fIn;
	int countOfRead = 0;
	fIn.open(fileName.c_str());
	if (fIn.is_open()) {
		values.clear();
		char buffer[20];
		for (int i = 0; i < fromIndex + countOfNumbers; i++) {
			if (!fIn.eof()){
				fIn >> buffer;
				if (i >= fromIndex){
					int value = atoi(buffer);
					values.push_back(value);
					countOfRead++;
				}
			}
			else{
				readTillEnd = true;
				break;
			}
		}
		return countOfRead;
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

			if (!file2.eof()){
				while (!file2.eof()){
					file2 >> buff2;
					value2 = atoi(buff2);
					fileOut << value2;
					if ((counter + 1) % 10 == 0) fileOut << "\n";
					else fileOut << "\t";
					counter++;
				}
			}
			if (!file1.eof()) {
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

void MergeFiles(vector<string> &fileNames)
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
	rename(oldName.c_str(), "/home/alex/FileForSorting/sorted/SortedFile");
}
