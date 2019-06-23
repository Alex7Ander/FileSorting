#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int CreateFile(string _FileName, int _Size);

int main(int argc, char* argv[])
{
	if (argc == 3){
		string fileName = argv[1];
		int size = atoi(argv[2]);
		if (size<=0){
			cout << "\033[33mWrong size parametr\033[0m" << endl;
			return -3;
		}
		size *= 1024;
		size *= 1024;

		if (!CreateFile(fileName, size)){
			cout << endl << "\033[32mDONE\033[0m" << endl;
		}
		else{
			cout << endl << "\033[33mERROR\033[0m" << endl << "\033[32mTry one more time!\033[0m" << endl;
		}
		return 0;
	}
	else{
		cout << "\033[33mWrong count of parametrs\033[0m" << endl;
		cout << "\033[32mCreateFile [File_Path] [Usefull_Data_Size]\033[0m" << endl;
		return 1;
	}
}

int CreateFile(string _FileName, int _Size)
{
	ofstream fOut;
	fOut.open(_FileName.c_str());
	if (fOut.is_open()){
		int countOfDigits = _Size / sizeof(int);
		int step = 0;
		for (int i = 0; i < countOfDigits; ++i){
			fOut << rand() << "\t";
			if(fOut.fail()) return 2;	
			int stC = countOfDigits / 99;
			if (i >= stC*step){
				++step;
				cout << "Progress: " << step << " %\r";
				cout.flush();
			}	
		}
		fOut.close();
		return 0;
	}
	else{
		return 1;
	}
}