#include "SortingFunctions.h"
//----------------------------------------------------------------
void FileSorter::SplitingIntoSortedParts(condition_variable &NextStep)
{
	/// В этом методе отсутвует обработка ошибок
	ifstream fIn;
	int countOfRead = 0;
	fIn.open(this->initialFileName.c_str());
	if (fIn.is_open()) {
		this->values.clear(); /// values используется только в этом методе, почему она член класса?
		char buffer[20];		/// = {0}, переменные лучше всегда инициализировать
		int countOfParts = 0;
		while (!fIn.eof()){		
			this->values.clear();
			for (int i = 0; i < this->countOfValues; i++){
				if (!fIn.eof()){ /// Это можно унести в for
					fIn >> buffer; /// Почему не читать сразу в int?
					int value = atoi(buffer);
					this->values.push_back(value);
				}
				else{
					break;
				}								
			}
			NextStep.notify_one();
			countOfParts++;
			this->MergeSorting(this->values, 0, this->values.size()-1);
			stringstream numStr;
			numStr << countOfParts; /// Может сразу << "sFile" << countOfParts и переменная fileOutPath не нужна
			string fileOutPath = "sFile" + numStr.str();
			this->WriteFile(fileOutPath.c_str(), this->values, this->values.size());
			this->tempOutFilesNames.push_back(fileOutPath);
		}
		this->splitted = true;
		NextStep.notify_one();
	}
}
//----------------------------------------------------------------
void FileSorter::MergeFiles(condition_variable &NextStep)
{ 
	int mergeCounter = 1;
	queue<string> mergingFiles;
	for (int i=0; i<this->tempOutFilesNames.size(); i++)
		mergingFiles.push(this->tempOutFilesNames[i]); /// Почему сразу не складывать в queue?

	do{
		int countOfThreads = mergingFiles.size()/2;
		for (int i=0; i<countOfThreads; i++){
			string fileName1 = mergingFiles.front();
			mergingFiles.pop();
			string fileName2 = mergingFiles.front();
			mergingFiles.pop();	
			stringstream numStr;
			numStr << mergeCounter;
			string outName = "sFile_" + numStr.str();
			this->tempOutFilesNames.push_back(outName);
			mergingFiles.push(outName);
			thread myThr((&FileSorter::MergeTwoFiles), this, fileName1, fileName2, outName);
			myThr.join(); /// Зачем создавать поток и ждать его?
			mergeCounter++;
			NextStep.notify_one();
		}
	}while (mergingFiles.size()>1);

	string oldName = this->tempOutFilesNames[this->tempOutFilesNames.size() - 1];
	rename(oldName.c_str(), this->outFileName.c_str());
	for (int i=0; i<this->tempOutFilesNames.size()-1; i++) {
		remove(this->tempOutFilesNames[i].c_str());
		NextStep.notify_one();
	}
	this->merged = true;
	NextStep.notify_one();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
void FileSorter::MergeTwoFiles(string fileName1, string fileName2, string outName)
{	/// Отсутсвует обработка ошибок
	/// Длинный, непонятный метод. Может разбить его на части?
	ifstream file1;
	ifstream file2;
	file1.open(fileName1.c_str());
	file2.open(fileName2.c_str());
	/// Много вложенных if-ов
	if (file1.is_open() && file2.is_open()){
		ofstream fileOut;
		fileOut.open(outName.c_str());
		if (fileOut.is_open()){
			bool stepFile1 = true; //флаг, указывающий на то, что надо прочитать следующее значение из 1-го файла
			bool stepFile2 = true; //аналогично но для 2-го файла
			int value1;
			int value2;
			int counter = 0;
			bool stop = false; /// Эта переменная не используется
			while (true){
				char buff[20];
				//если необходимо прочитать значение из 1-го файла
				if (stepFile1){					
					if (file1.eof()){ 	//если дошли до конца файла, то прерываем цикл сравнений
						fileOut << value2;	
						counter++;
						if (!file2.eof()){
							if ((counter + 1) % 10 == 0) fileOut << "\n";
							else fileOut << "\t";	
							while(true){
								file2 >> buff;
								value2 = atoi(buff);
								fileOut << value2;
								counter++;	
								if (file2.eof()) break;	/// Это можно унести в while
								if ((counter + 1) % 10 == 0) fileOut << "\n"; /// Дублирование кода
								else fileOut << "\t";						
							}
						}
						break;
					}
					file1 >> buff;
					value1 = atoi(buff);
				}
				//а если необходимо прочитать значение из 2-го файла
				if (stepFile2){					
					if (file2.eof()){	
						/// Дублирование кода
						fileOut << value1;
						counter++;
						if (!file1.eof()){
							if ((counter + 1) % 10 == 0) fileOut << "\n";
							else fileOut << "\t";	
							while(true){
								file1 >> buff;
								value1 = atoi(buff);
								fileOut << value1;
								counter++;		
								if (file1.eof()) break;
								if ((counter + 1) % 10 == 0) fileOut << "\n";
								else fileOut << "\t";
							}
						}
						break;
					}
					file2 >> buff;
					value2 = atoi(buff);
				}
				//сравниваем и меньшее или равное записываем в новый файл
				if (value1 < value2){
					stepFile1 = true; //если в 1-м фале было наименьшее значение, то из 1-го файла надо будет прочитать следующее
					stepFile2 = false; //а из 2-го не надо
					fileOut << value1; //записывам его
				}
				else{
					stepFile1 = false;
					stepFile2 = true;					
					fileOut << value2;
				}
				if ((counter + 1) % 10 == 0) fileOut << "\n";
				else fileOut << "\t";
				counter++;
			}
			file1.close();
			file2.close();
			fileOut.close();
		} //end if (fileOut.is_open()) 
	}// end if (file1.is_open() && file2.is_open())
}
//----------------------------------------------------------------
/// Я думаю для сортировки кусочка, можно было воспользоватся стандартным алгоритмом сортировки std:sort
void FileSorter::MergeSorting(vector<int> & array, int left, int right) /// Для подобных вещей в алгоритмах нужно использовать итераторы, а не индексы
{
	/// Этот метод не использует this, зачем он член класса, к тому же публичный
	if (left == right) return;
	if (right - left == 1) {
		if (array[left] > array[right]) swap(array[left], array[right]);
		return;
	}
	int mid = (right + left) / 2;
	MergeSorting(array, left, mid); /// Куски могут быть большие поэтому использовать рекурсию не лучший вариант
	MergeSorting(array, mid + 1, right);
	vector<int> tempArray; /// Размер буфера известен, оптимальнее сразу зарезервировать место
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
		array[left + step] = tempArray[step]; /// В таких случаях нужно использовать std:copy
}
//----------------------------------------------------------------
void inline FileSorter::WriteFile(string fileName, vector<int>& data, int size) /// Параметры передаются не по const&
{
	ofstream fOut;
	fOut.open(fileName.c_str()); /// Тут нет проверки is_open, не думаю, что это правильный способ использования fstream, но все же
	for (int i = 0; i < size-1; i++) {
		fOut << data[i]; /// Наверное, тут можно воспользоваться ostream_iterator
		if ((i + 1) % 10 == 0) fOut << "\n";
		else fOut << "\t";
	}
	fOut << data[size-1];
	fOut.close();
	return; /// Это лишнее
}
//----------------------------------------------------------------