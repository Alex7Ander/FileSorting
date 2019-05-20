#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void CreateFile(string fileName, int size);

int main()
{
	string filePath;
	cout << "File path: " << endl;
	cin >> filePath;
	if (filePath=="0") filePath = "/home/alex/";
	int size;
	bool notDone = true;
	while(notDone){
	cout << "Usefull data size: " << endl;
		if (cin >> size){
			notDone = false;
			size *= 1024;
			size *= 1024;
			CreateFile(filePath, size);
		}
		else{
			cout << "It is not an integer value. Try one more time: " << endl;	
		}
	}	
	return 0;
}

void CreateFile(string fileName, int size)
{
	ofstream fOut;
	fOut.open(fileName.c_str());
	int countOfDigits = size/sizeof(int);
	for (int i = 0; i < countOfDigits; i++){
	  fOut << rand();//%899+100;
	  if ((i+1)%10 == 0) fOut << "\n";
	  else fOut << "\t";
    }
	fOut.close();
	return;
}