#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void CreateFile(string fileName, int size);
void MergeSorting(int *array, int left, int right);
int  FileSize(string fileName);
void ReadFile(string fileName, int size, vector<int> &digits);
void WriteFile(string fileName, int *data, int size);

int main()
{
	int fileSize, ramLimit, countOfParts;
	cout << "Hello World!" << endl;
	cout << "Inpit file size, Mb: " << endl;
	cin >> fileSize;
	cout << "Inpit RAM limit, Mb: " << endl;
	cin >> ramLimit;

	fileSize *= 1024;
	fileSize *= 1024;
	ramLimit *= 1024;
	ramLimit *= 1024;

	countOfParts = fileSize/ramLimit;
	if (fileSize%ramLimit != 0) countOfParts++;

	string filePath = "/home/alex/file";
	CreateFile(filePath, fileSize);
	cout << "File created" << endl;
	int realSize = FileSize(filePath);
	vector<int> digits;
	ReadFile(filePath, realSize, digits);
	cout << "File was read" << endl;
	int size = digits.size();
	cout << "Size of data array is " << size << endl;
	int *valueArray = new int[size];
	for (int i = 0; i < size; i++){
		valueArray[i] = digits.at(i);
	}
	MergeSorting(valueArray, 0, size-1);
	WriteFile("/home/alex/file2", valueArray, size);
	cout << "Done" << endl;
	return 0;
}

void CreateFile(string fileName, int size)
{
	ofstream fOut;
	fOut.open(fileName.c_str());
	int countOfDigits = size/sizeof(int);
	for (int i = 0; i < countOfDigits; i++){
	  fOut << rand()%899+100;
	  if ((i+1)%10 == 0) fOut << "\n";
	  else fOut << "\t";
    }
	fOut.close();
	return;
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

void ReadFile(string fileName, int size, vector<int> &digits)
{
	ifstream fIn;
	vector<string> strings;
	fIn.open(fileName.c_str());
	while (!fIn.eof()){
		char buff[256];
		fIn.getline(buff, 256);
		string str = buff;
		str.push_back('\t');
		strings.push_back(str);
	}	
	for (int stringCount = 0; stringCount < strings.size(); stringCount++){
		int startPos = 0;
		int stopPos = 0;
		string str = strings[stringCount];
		do{
			for (int i = stopPos; i < str.length(); i++){
				if ((str[i] == '\t') && i>stopPos) {
					if (stopPos>0) startPos = stopPos + 1;
					else  startPos = stopPos;
					stopPos = i;
					break;
				}
			}
			int charCount = stopPos - startPos;
			if (charCount > 1){
				char *newValue = new char[charCount];
				for (int i = 0; i < stopPos - startPos; i++){
					char c0 = str.at(startPos + i);
					newValue[i] = str[startPos + i];
				}
				int value = atoi(newValue);
				digits.push_back(value);
			} 
		}while (stopPos != str.length()-1);
	}
	fIn.close();
	return;
}

void WriteFile(string fileName, int *data, int size)
{
	ofstream fOut;
	fOut.open(fileName.c_str());
	for (int i=0; i<size; i++){
		fOut << data[i];
		if ((i+1)%10 == 0) fOut << "\n";
		else fOut << "\t";
	}
	fOut << endl;
	fOut.close();	
	return;
}

void MergeSorting(int *array, int left, int right)
{
	if (left == right) return;
	if (right - left == 1){
		if (array[left] > array[right]) swap(array[left], array[right]);
		return;
	}
	int mid = (right+left) / 2;
	MergeSorting(array, left, mid);
	MergeSorting(array, mid + 1, right);
	int *tempArray = new int[right];
	int i = left;
	int j = mid + 1;
	for (int step = 0; step < right - left + 1; step++) {
		if ((j > right) || ((i <= mid) && (array[i] < array[j]))){
			tempArray[step] = array[i];
			i++;
		}
		else{
			tempArray[step] = array[j];
			j++;
		}
	}
	for (int step = 0; step < right - left + 1; step++)
		array[left + step] = tempArray[step];
}