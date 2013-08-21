#include "WriteFile.h"
#include <cstdlib>
#include <string>
#pragma warning(disable : 4996)

void recording_and_write::WriteLand( const TTAA_Database time_data,fstream & inFile )
{
	surface DAT = time_data.land_surface;
	double temp = DAT.info_temp.temp;
	inFile <<  time_data.number.district_number<<time_data.number.station_number <<" " ;
	if ( DAT.information == true )
	{
		inFile << "Pzem=";
		if((DAT.pressure) < 1000)inFile << " ";
		inFile << DAT.pressure << " ";
		inFile << "Tzem=";
		if ( temp >= 0 )
		{
			inFile << " ";
		} 
		if (fabs(temp) < 10) inFile << " ";
		inFile << temp; 
		if((temp - (int)temp) == 0) inFile << ".0";
		inFile << '\n' ;
	} 
	else
	{
		inFile << "Нет данных\n";
	}
}

void recording_and_write::WriteStandateSurfase( const TTAA_Database time_data, fstream & inFile )
{
	TTAA_Database date = time_data;

	list<standardSurface>::iterator i;
	if (date.information == true)
	{
		for(i = date.level.begin(); i != date.level.end(); ++i )
		{

			standardSurface new_surfase = *i;
			int stop = 99999;
			if (new_surfase.data.info_temp.temp == stop || new_surfase.data.info_temp.dewpoint == stop *\
				new_surfase.data.wind.wind_speed == stop || new_surfase.data.wind.wind_direction == stop)
			{
				new_surfase.data.information = false;
			}
			if (new_surfase.data.information != false)
			{
				double temp = new_surfase.data.info_temp.temp;				//Температура
				int number = new_surfase.height.number;						//Номер уровня
				WIND wind = new_surfase.data.wind;

				inFile << "IND="<<  time_data.number.district_number<<time_data.number.station_number <<" ";
				inFile << "P=";
				if (number != 0)inFile << " ";
				else inFile << "10";
				inFile << number;
				if( number == 92 ) inFile << "5";
				else inFile << "0";

				///температура
				inFile << " T=";
				if (temp >= 0 ) inFile << " ";
				if (fabs(temp)< 10) inFile << " ";
				inFile << temp;
				if((temp - (int)temp) == 0) inFile << ".0";

				//направление ветра
				inFile << " d=";
				if (wind.wind_direction < 100)inFile << " ";
				if(wind.wind_direction < 10 )inFile << " ";
				inFile << wind.wind_direction;

				//скороть ветра
				inFile << " f=";
				if (abs(wind.wind_speed) < 100)inFile << " ";
				if(abs(wind.wind_speed) < 10 )inFile << " ";
				inFile << wind.wind_speed;

				//дефицит точки росы
				inFile << " D=";
				double dewpoint = new_surfase.data.info_temp.dewpoint;
				if (abs(dewpoint) < 100)inFile << " ";
				if(abs(dewpoint) < 10 )inFile << " ";
				inFile << dewpoint;
				if((dewpoint  - (int)dewpoint ) == 0) inFile << ".0";
				inFile << "0";
				inFile << "\n" ;	
			}
		}
		inFile << "\n" ;
	}
}

void recording_and_write::WriteFile(const char * _file )
{
	data_TTAA.sort();
	data_TTBB.sort();
	list<DateSurfase_TTAA>::iterator i;
	list<DateSurfase_TTBB>::iterator k;
	char * txt = new char;
	txt = (".txt");

	for ( i = data_TTAA.begin(); i !=data_TTAA.end();++i )
	{
		i->data_.sort();
		char * name = new char;
		char * date = new char;
		date = itoa(i->date,date,10);
		strcpy(name,_file);
		strcat(name,date);
		strcat(name,txt);
		fstream inFile( name, ios::out);
		if(!inFile)
		{
			perror("Error open file!");
			cin.get();
			exit(1);
		}
		inFile << "Выборка за период: " ;
		if(i->date < 10)inFile << "0";
		inFile<< i->date << "." << "ММ" << "." << "ГГГГ" ;
		inFile << "\n\n";
		list<TTAA_Database>::iterator j;
		for ( j = i->data_.begin(); j != i->data_.end(); ++j )
		{
			WriteLand( *j , inFile );
			
		}
		inFile << '\n' <<  "StandartLevels" << "\n\n";
		for ( j = i->data_.begin(); j != i->data_.end(); ++j )
		{
			WriteStandateSurfase( *j , inFile );
		}
		inFile.close();
	}
	for (k = data_TTBB.begin(); k != data_TTBB.end(); ++k)
	{
		char * name = new char;
		char * date = new char;
		date = itoa(k->date,date,10);
		strcpy(name,_file);
		strcat(name,date);
		strcat(name,txt);
		fstream inFile( name, ios::app);
		if(!inFile)
		{
			perror("Error open file!");
			cin.get();
			exit(1);
		}
		list<TTBB_Database>::iterator j;
		
		inFile << '\n' << "SpecialPoints" << "\n\n";
		for ( j = k->data_.begin(); j != k->data_.end(); ++j )
		{
			list<Temp_Base>::iterator L;
			for (L = j->level.begin(); L != j->level.end(); ++L)
			{
				inFile <<  "IND=" << j->number.district_number<<j->number.station_number <<" " ;
				int pressure = L->pressure;
				inFile <<  "P=" ;
				if (pressure < 1000)inFile << " ";
				if (pressure < 100)inFile << " ";
				if (pressure < 10)inFile << " ";
				inFile << pressure << " ";
				double temp = L->info_temp.temp;
				if (temp > 0 )inFile << " ";
				if (fabs(temp) < 10)inFile << " ";
				if (fabs(temp) == 0)inFile << " ";
				inFile << temp;
				if((temp - (int)temp) == 0) inFile << ".0";
				inFile << '\n' ;
			}
			inFile << '\n' ;
		}
		inFile.close();
	}
	
}