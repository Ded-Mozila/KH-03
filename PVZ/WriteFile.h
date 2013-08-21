#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "DB_structure_TTAA.h"
#include "DB_structure_TTBB.h"
using namespace std;

class recording_and_write
{	
public:


	char nameFile[256];
	list<DateSurfase_TTAA> data_TTAA;
	list<DateSurfase_TTBB> data_TTBB;

	recording_and_write(void);
	~recording_and_write(void);

	void TTAA(char * code);
	void TTBB(char * code);

	WIND_SHIFT WindShift( int GGPPP );

	char * MaxWind( char * code, surfaceWind &new_max_wind,  int GGPPP );

	char * NumberHeight( char * code, NUMBER_HEIGHT& new_height, int i);

	char * DistrictStation( char * code, DISTRICT_STATION& new_number);

	char * DateTime( char * code, DATA_TIME& new_data_tim );
			
	char * Pressure( char * code, int& press );								// Значение давления

	char * ReturnSurface( char * code , surface& info );						// Забивает данными о температуре и о ветре  type surfase

	char * TempDewpoint( char * code, TEMP_DEWPOINT& new_info_temp );		// Дает данные от температуре и дефеците росы возвращает код строки (строка с кодом, структура в которую сохраниться данные о температуре и дефиците росы

	char * Wind( char * code, WIND& new_wind );								// Значение ветра

	double Temp( bool presence_dewpoint,const int TTTDD );					// Выделение температуры

	double DefinitionTenthTemp( int m );									// Определение данных о температуре

	double DewPoint( int TTTDD );											// Дефицит росы



	//Функции записи данных в файл.
	//////////////////////////////////////////////////////////////////////////
	void WriteFile(const char * file);
	void WriteLand(const TTAA_Database time_data, fstream & inFile);			// Функция записи данных на уровни земли 
	void WriteStandateSurfase(const TTAA_Database time_data, fstream & inFile);	// Функция записи стандартных изобарических поверхностей поверхностей
	void WriteSpecialPoints(const TTAA_Database time_data, fstream & inFile);	// Функция записи специальных пунктов кода ТТВВ			
};

#endif // !WRITEFILE_H