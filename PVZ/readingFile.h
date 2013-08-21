#pragma once

#include "WriteFile.h"
#include <string.h>


class readingFile
{
public:
	fstream file; 								// Имя файла 
	recording_and_write  TTXX;					// Класс разкодирования и записи
	readingFile(void);							// По умолчанию
	readingFile(char * name, char * file_next);	// name - имя входного файла , file_next - имя выходного файла
	char * rName();								//Возвращает деректорию name
	char * rContents();							//возвращает содержанием файла
	void readF();
	void SelectionCipher( char* TXX );
	~readingFile(void);	
};

