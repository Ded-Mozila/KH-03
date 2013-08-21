#include "readingFile.h"
#include <string.h>
#pragma warning(disable : 4996)

readingFile::readingFile(void)
{
}
readingFile::readingFile(char * name, char * file_next)
{
	file.open( name , ios::in);
	if(!file)
	{
		perror("Error open file!");
		cin.get();
		exit(1);
	}
	else
	{
		readF();
		file.close();
		TTXX.WriteFile(file_next);	
	}
}

void readingFile::readF()
{
	char * T = new char[2000];
	char * TXX = new char[5];
	while (!file.getline( T, 2000, 'T' ).eof())
	{
		file.getline( TXX, 5 ,' ');
		SelectionCipher( TXX );
		strcpy(TXX, "");
		strcpy(T,"");
	}
	cout << "Good!";
	TTXX.data_TTAA.sort();
	TTXX.data_TTBB.sort();

}
void readingFile::SelectionCipher( char* TXX )
{
	char * TTX = new char[1000] ;
	switch (TXX[1])
	{
	case  'A':
		{
			file.getline(TTX,1000,'=');
			TTXX.TTAA(TTX);
			break;
		}
	case  'B':
		{
			file.getline(TTX,1000,'=');
			TTXX.TTBB(TTX);			
			break;
		}
	case  'C':
		{
			file.getline(TTX,1000,'=');
			break;
		}
	case  'D':
		{
			file.getline(TTX,1000,'=');
			break;
		}
	default: 
		{	
			cout << "Not good" <<'\n';
			file.getline(TTX,1000,'=');
			cout << TTX << endl;
			break;
		}
	}
}

readingFile::~readingFile( void )
{

}
