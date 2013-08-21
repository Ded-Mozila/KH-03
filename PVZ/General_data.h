#pragma once

struct WIND
{
	int wind_direction;					// ����������� �����
	int wind_speed;						// �������� �����;
};

struct DATA_TIME
{
	int date;							// ���� �������
	int time;							// ����� �������
	char id_surface;					// ��� ������������� �������������� ������������
};

struct DISTRICT_STATION
{
	int district_number;				// ����� �������� ������
	int station_number;					// ����� ���������������������� �������
};

struct TEMP_DEWPOINT
{
	double temp;						// �������� �����������
	double dewpoint;					// ������� ����� ����
};

struct  WIND_SHIFT					// �������� � ������������ ������ �����
{
	int up_speed;						// ���������� �������� ��������� �������� � �/� ��  ������ ��������� � ����� �� 1 �� ���� ����
	int below_speed;					// ���������� �������� ��������� �������� � � /� ��  ������ ��������� � ����� �� 1 �� ���� ����
};

struct NUMBER_HEIGHT
{
	int number;							// ����� ������
	int height;							// ������ ��� ������� ����
};