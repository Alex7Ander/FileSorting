#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

condition_variable nextStep;
bool step;
bool stepDone(){
	return step;
}

struct fileCrtParams{
	fileCrtParams(string _Name, int _Size, int _Step) : fileName(_Name), size(_Size), step(_Step){}
	string fileName;
	int size;
	int step;
};

void CreateFile(fileCrtParams &params);

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

		fileCrtParams params(filePath, size, 0);
		thread creatingThread(CreateFile, std::ref(params));
		do{
			mutex mtx;
			unique_lock<mutex> uLock(mtx);
			nextStep.wait(uLock, stepDone);
			cout << "Progress: " << params.step << " %\r";
			cout.flush();
		}while(params.step<100);		
		creatingThread.join();
		cout << endl << "DONE" << endl;
		return 0;
	}
	else{
		cout << "Wrong count of parametrs" << endl;
		cout << "CreateFile [File_Path] [Usefull_Data_Size]" << endl;
		return -1;
	}
}

void CreateFile(fileCrtParams &params)
{
	mutex mtx;
	ofstream fOut;
	fOut.open(params.fileName.c_str());
	if (fOut.is_open()){
		int countOfDigits = params.size/sizeof(int);
		params.step = 0;
		for (int i = 0; i < countOfDigits; i++){
	  		fOut << rand();
	  		if ((i+1)%10 == 0) fOut << "\n";
	  		else fOut << "\t";	  		
	  		int stC = countOfDigits/99;
	  		if (i >= stC*params.step){
	  			++params.step;
	  			step = true;
	  			nextStep.notify_one();
	  		}
	  		else{
	  			step = false;
	  			nextStep.notify_one();	  			
	  		}
    	}
    	nextStep.notify_one();
    	step = true;
		fOut.close();
		return;
	}
	else{
		params.step = -1;
		return;
	}
}