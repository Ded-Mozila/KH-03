#pragma once

#include "WriteFile.h"
#include <string.h>


class readingFile
{
public:
	fstream file; 								// ��� ����� 
	recording_and_write  TTXX;					// ����� �������������� � ������
	readingFile(void);							// �� ���������
	readingFile(char * name, char * file_next);	// name - ��� �������� ����� , file_next - ��� ��������� �����
	char * rName();								//���������� ���������� name
	char * rContents();							//���������� ����������� �����
	void readF();
	void SelectionCipher( char* TXX );
	~readingFile(void);	
};

