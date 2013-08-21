#pragma once
#include <list>
#include "General_data.h"
using namespace std;
struct surface						// ��� ����������� ������ ��� ���� �����������
{
	bool information;					// ������������� ������������� ������  
	TEMP_DEWPOINT info_temp;			// ���������� � ������ ����������� � ������� ����� ����
	WIND wind;							// ������ �� �����
	int pressure;						// �������� �� ������ 99
};


struct standardSurface					// ����������� ������ 00 92 85 70 50 40 30 25 20 15 10
{
	NUMBER_HEIGHT height;				// ������ � ������ �� ������
	surface data;						// ������ � ������
};

struct surfaceWind						// ������  � ������������ ��������� ����� 77 66
{
	int point;							// 66 ��� 77
	bool information;					// ���������� ����������
	surface data;						// ������ � ������
};
class TTAA_Database						// ����� ��� �������� � ��������� ������ �� ���� TTAA
{
public:
	bool information;					// ���������� ����������
	DATA_TIME memory;					// ������ � ������� � ���� ������� � + ��������������
	DISTRICT_STATION number;			// ������ � ��������� ������� ����� � ������� 
	surface land_surface;				// ����������� ����� 99 
	list<standardSurface> level ;		// ����������� ������ 00 92 85 70 50 40 30 25 20 15 10
	list<surface> tropopause;			// �������� � ���������� 88
	list<surfaceWind> max_wind;			// �������� � ������������ ����� 77 66 
	list<WIND_SHIFT> vertical;			// �������� � ������������ ������ ����� 4
	bool operator< (const TTAA_Database & right) 
	{
		int m = ((right.number.district_number*1000) + right.number.station_number);
		int n = ((number.district_number*1000) + number.station_number);
		return n<m;
	} ;
	
};

 class DateSurfase_TTAA
{
public:
	int date;
	list<TTAA_Database> data_;
	bool operator< (const DateSurfase_TTAA & right) 
	{
		return date < right.date;
	} ;
};
