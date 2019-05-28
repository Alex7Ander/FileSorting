#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

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
		int prevStep = 0;
		do{
			cout << "Progress: " << params.step << " %\r";
			cout.flush();
			//this_thread::sleep_for(std::chrono::milliseconds(5));
			if (params.step == -1) {
				cout << "Error on file writing" << endl;	
				return -2;
			}
			if (params.step==100){
				cout << "Progress: " << params.step << " %\r";
				cout.flush();
				break;
			}
		}while(true);
		
		creatingThread.join();
		cout << endl << "DONE" << endl;
		return 0;
	}
	else{
		cout << "Wrong count of parametrs" << endl;
		cout << "CreateFile filepath usefullDataSize" << endl;
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
		for (int i = 0; i < countOfDigits; i++){
	  		fOut << rand();//%899+100;
	  		if ((i+1)%10 == 0) fOut << "\n";
	  		else fOut << "\t";

	  		int stC = countOfDigits/100;
	  		if (i >= stC*params.step){
	  			lock_guard<mutex> lG(mtx);
	  			++params.step;
	  		}
    	}
		fOut.close();
		return;
	}
	else{
		params.step = -1;
		return;
	}
}