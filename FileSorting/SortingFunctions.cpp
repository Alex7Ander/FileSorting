#include "SortingFunctions.h"
//----------------------------------------------------------------
Monitor* Monitor::instanceMonitor = nullptr;
//----------------------------------------------------------------
int FileSorter::makeSorting()
{
	if (this->SplitingIntoSortedParts()){		
		return 1;
	}
	if(this->MergeFiles()){
		return 1;
	}	
	return 0;
}
//----------------------------------------------------------------
int FileSorter::SplitingIntoSortedParts()
{
	ifstream fIn;
	int countOfRead = 0;
	fIn.open(this->initialFileName.c_str());
	if (fIn.is_open()) {
		vector<int> values;
		char buffer[20] = {0};
		int countOfParts = 0;
		while (!fIn.eof()){
			stringstream message;
			message <<  "Part №: " << countOfParts;
			this->monitor->ShowMessage(message.str());		
			values.clear();
			for (int i = 0; i < this->countOfValues; i++){
				if (!fIn.eof()){ 
					int value = {0};
					try{
						fIn >> value; 
					}
					catch(...){
						return 1;
					}
					values.push_back(value);
				}
				else{
					break;
				}								
			}
			countOfParts++;
			std::sort(values.begin(), values.end());
			stringstream numStr;
			numStr << "sFile" << countOfParts;
			this->WriteFile(numStr.str().c_str(), values);
			this->mergingFiles.push(numStr.str());
		}
		return 0;
	}
	else{
		return 1;
	}
}
//----------------------------------------------------------------
int FileSorter::MergeFiles()
{ 
	int mergeCounter = 1;
	while (mergingFiles.size()>1){
		stringstream message;		
		message <<  "Number of files to merge: " << mergingFiles.size();
		this->monitor->ShowMessage(message.str());	
		int countOfThreads = mergingFiles.size()/2;
		vector<string> filesForRemoving;
		int *results = new int[countOfThreads];
		for (int i=0; i<countOfThreads; i++){
			string fileName1 = mergingFiles.front();
			mergingFiles.pop();
			filesForRemoving.push_back(fileName1);

			string fileName2 = mergingFiles.front();
			mergingFiles.pop();	
			filesForRemoving.push_back(fileName2);

			stringstream numStr;
			numStr << mergeCounter;
			string outName = "sFile_" + numStr.str();
			this->mergingFiles.push(outName);
			thread mergThr([this, results, &i, &fileName1, &fileName2, &outName](){results[i]=this->MergeTwoFiles(fileName1, fileName2, outName);});
			mergThr.join();
			mergeCounter++;
		}
		for (int i=0; i<filesForRemoving.size(); i++) remove(filesForRemoving[i].c_str());	//Удаляем файлы, кторые только что соединяли			
		for (int i=0; i<countOfThreads; i++) {												//Проверяем результат каждого из слияний		
			if (results[i] != 0) {															//Если хоть одно из слияний завершилось некорректно, то 
				for (int j = mergingFiles.size(); j>0; j--){
					string remFile = mergingFiles.front();
					mergingFiles.pop();
					remove(remFile.c_str());												//Удаляем все оставшиесся файлы
				}
				return 1;															
			} 
		}			
	}
	string oldName = mergingFiles.front();
	mergingFiles.pop();	
	rename(oldName.c_str(), this->outFileName.c_str());
	this->monitor->ShowMessage("Merging done");
	return 0;
}
//----------------------------------------------------------------
int inline FileSorter::MergeTwoFiles(const string fileName1, const string fileName2, const string outName)
{	
	std::ifstream inFile1(fileName1.c_str());
	std::ifstream inFile2(fileName2.c_str());
	std::ofstream outFile(outName.c_str());
	if (!(inFile1.is_open() && inFile2.is_open() && outFile.is_open())) {
		return 1;
	}
	int resOfMerge = 0;
	try{
		std::merge(std::istream_iterator<int>(inFile1), {}, std::istream_iterator<int>(inFile2), {}, std::ostream_iterator<int>(outFile, "\t"));
	}
	catch(...){
		resOfMerge = 1;
	}
	inFile1.close();
	inFile2.close();
	outFile.close();
	return resOfMerge;
}
//----------------------------------------------------------------
void inline FileSorter::WriteFile(const string& fileName, const vector<int>& data) /// Параметры передаются не по const&
{
	ofstream outFile;
	outFile.open(fileName.c_str());
	if (outFile.is_open()){
		std::copy(data.begin(), data.end(), std::ostream_iterator<int>(outFile, "\t"));	
	}
	outFile.close();
}
//----------------------------------------------------------------