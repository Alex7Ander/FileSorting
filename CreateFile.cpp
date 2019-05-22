#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int CreateFile(string fileName, int size);

int main(int argc, char* argv[])
{
	string filePath;
	int size;
	if (argc == 3){
		filePath = argv[1];
		size = atoi(argv[2]);
		if (size<=0){
			cout << "Wrong size parametr" << endl;
			return -3;
		}
		size *= 1024;
		size *= 1024;
		int resOfCreating = CreateFile(filePath, size);
		if (!resOfCreating){
			cout << "DONE" << endl;
			return 0;
		}
		else{
			cout << "Error on file writing" << endl;	
			return -2;
		}	
	}
	else{
		cout << "Wrong count of parametrs" << endl;
		cout << "CreateFile filepath usefullDataSize" << endl;
		return -1;
	}

}

int CreateFile(string fileName, int size)
{
	ofstream fOut;
	fOut.open(fileName.c_str());
	if (fOut.is_open()){
		int countOfDigits = size/sizeof(int);
		for (int i = 0; i < countOfDigits; i++){
	  		fOut << rand();//%899+100;
	  		if ((i+1)%10 == 0) fOut << "\n";
	  		else fOut << "\t";
    	}
		fOut.close();
		return 0;
	}
	else{
		return -1;
	}
}