/// В файле используются и табы и пробелы для отступов
/// В некоторых местах не хватает пробелов вокруг бинарных операторов
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/// Глобальные переменные это зло

int CreateFile(string _FileName, int _Size);

int main(int argc, char* argv[])
{
	if (argc == 3){
		string fileName = argv[1];
		int size = atoi(argv[2]);
		if (size<=0){
			cout << "Wrong size parametr" << endl;
			return -3;
		}
		size *= 1024;
		size *= 1024;
		if (!CreateFile(fileName, size)){
			cout << endl << "DONE" << endl;
		}
		else{
			cout << endl << "ERROR" << endl;
		}
		return 0;
	}
	else{
		cout << "Wrong count of parametrs" << endl;
		cout << "CreateFile [File_Path] [Usefull_Data_Size]" << endl;
		return 1;
	}
}

int CreateFile(string _FileName, int _Size)
{
	ofstream fOut;
	fOut.open(_FileName.c_str());
	/// Плохая обработка ошибок
	if (fOut.is_open()){
		int countOfDigits = _Size / sizeof(int);
		int step = 0;
		for (int i = 0; i < countOfDigits; ++i){
			fOut << rand();
			/// Тут "\n" вместо endl
			if ((i + 1) % 10 == 0) fOut << endl;
			else fOut << "\t";	  		
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