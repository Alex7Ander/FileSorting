#include "SortingFunctions.h"
//----------------------------------------------------------------
int FileSorter::operator()()
{
	if (!this->SplitingIntoSortedParts()){
		this->MergeFiles();
		return 0;
	}
	else{
		return 1;
	}	
}
//----------------------------------------------------------------
int FileSorter::SplitingIntoSortedParts()
{
	/// В этом методе отсутвует обработка ошибок
	ifstream fIn;
	int countOfRead = 0;
	fIn.open(this->initialFileName.c_str());
	if (fIn.is_open()) {
		vector<int> values;
		char buffer[20] = {0};		/// = {0}, переменные лучше всегда инициализировать
		int countOfParts = 0;
		while (!fIn.eof()){
			monitor.ShowProgress("Part №: ", countOfParts);		
			values.clear();
			for (int i = 0; i < this->countOfValues; i++){
				if (!fIn.eof()){ /// Это можно унести в for
					int value = {0};
					try{
						fIn >> value; /// Почему не читать сразу в int?
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
			numStr << "sFile" << countOfParts; /// Может сразу << "sFile" << countOfParts и переменная fileOutPath не нужна
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
	do{
		monitor.ShowProgress("Files for merging: ", mergingFiles.size());
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
			std::thread mergThr([this, results, &i, &fileName1, &fileName2, &outName](){results[i]=this->MergeTwoFiles(fileName1, fileName2, outName);});
			mergThr.join(); /// Зачем создавать поток и ждать его?
			mergeCounter++;
		}
		for (int i=0; i<filesForRemoving.size(); i++) remove(filesForRemoving[i].c_str());
	}while (mergingFiles.size()>1);

	string oldName = mergingFiles.front();
	mergingFiles.pop();	
	rename(oldName.c_str(), this->outFileName.c_str());
	return 0;
}
//----------------------------------------------------------------
int FileSorter::MergeTwoFiles(string fileName1, string fileName2, string outName)
{	
	std::ifstream inFile1(fileName1.c_str());
	std::ifstream inFile2(fileName2.c_str());
	std::ofstream outFile(outName.c_str());
	if (!(inFile1.is_open() && inFile2.is_open() && outFile.is_open())) {
		return 1;
	}
	std::merge(std::istream_iterator<int>(inFile1), {}, std::istream_iterator<int>(inFile2), {}, std::ostream_iterator<int>(outFile, "\t"));
	inFile1.close();
	inFile2.close();
	outFile.close();
	return 0;
}
//----------------------------------------------------------------
void inline FileSorter::WriteFile(const string& fileName, const vector<int>& data) /// Параметры передаются не по const&
{
	ofstream outFile;
	outFile.open(fileName.c_str()); /// Тут нет проверки is_open, не думаю, что это правильный способ использования fstream, но все же
	if (outFile.is_open()){
		std::copy(data.begin(), data.end(), std::ostream_iterator<int>(outFile, "\t"));	
	}
	outFile.close();
}
//----------------------------------------------------------------