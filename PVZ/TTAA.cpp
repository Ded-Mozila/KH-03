#include "WriteFile.h"

void recording_and_write::TTAA( char * code )
{
	DateSurfase_TTAA new_base_;
	TTAA_Database base;
	base.information = true;
	bool theEnd = false;					// ���������� ���������
	int step = 1;							// ��� ���������� ���������	
	while((*code) != '\0')
	{
		switch (step)
		{
			case 1 : // ���������� ������� � ���� ������� �����
				{
					code = DateTime(code,base.memory);
					step++;
					break;
				}
			case 2 : // ���������� �������� ������ � �������
				{
					code = DistrictStation(code, base.number);
					step++;
					break;
				}

			case 3 : // ���������� � �������� ������������
				{
					if( strstr( code, "NIL" ) == NULL ) //�������� �� ���������� ������
					{
						base.land_surface.information = true;
						code = Pressure(code, base.land_surface.pressure);
						code = ReturnSurface( code , base.land_surface );
					}
					else
					{
						theEnd = true;
						base.information = false;
					}
					step++;
					break;
				}
			case 4 :
				{
					int i = 1;
					while((*code) != '\0')
					{
						standardSurface time_data;
						//1. ���������� ������������ ����������� ������������ � � ������
						code = NumberHeight( code, time_data.height, i );	
						//2. ...
						code = ReturnSurface( code, time_data.data );
						//3. ���������� �������� � ������
						base.level.push_back(time_data);
						if (i==11)break;
						i++;
					}
					step++;
					break;
				}
			case 5 :
				{
					//////////////////////////////////////////////////////////////////////////
					//1. ����������� ��� ���: ������  � ���������� ��� ������ � �����
					while( (*code) != '\0' )
					{
						if((*code+1) != '/')
						{
							int GGPPP = strtol(code, &code, 10);
							int GG = 0;
							if ((*code) == '/')
							{
								code += 3;
								int GG = GGPPP;
							}
							else
							{
								int GG = GGPPP/1000;
							}
							switch (GG)
							{
								case 88 ://������  � ����������
									{
										if ((*code+1) != '/')
										{
											surface new_tropopause;
											if((GGPPP % 1000) != 999)
											{
												new_tropopause.information = true;
												new_tropopause.pressure = GGPPP % 1000;
												code = ReturnSurface( code, new_tropopause );
											}
											else
											{
												new_tropopause.information = false;
											}

											base.tropopause.push_back( new_tropopause );
										}
										
										break;
									}
								case 77 ://������ � �����
									{
										if ((*code+1) != '/')
										{
											surfaceWind new_max_wind;
											new_max_wind.point = GG;
											code = MaxWind( code, new_max_wind, GGPPP );
											base.max_wind.push_back(new_max_wind);
										}
										break;
									}
								case 66://������ � �����
									{
										if ((*code+1) != '/')
										{
											surfaceWind new_max_wind;
											new_max_wind.point = GG;
											code = MaxWind( code, new_max_wind, GGPPP );
											base.max_wind.push_back(new_max_wind);
										}
										break;
									}
								default:
									{
										//base.vertical.push_back(WindShift(GGPPP));
										break;
									}
							}
						}
					}
					break;
				}
		default:
			break;
		}
		if(theEnd  == true)
			break;
	}
	// ��������� ������ ���� �������
	if(data_TTAA.size() == 0) 
	{
		new_base_.date = base.memory.date;
		new_base_.data_.push_back(base);
		data_TTAA.push_back( new_base_ );
	}
	else
	{
		bool check = false;
		list<DateSurfase_TTAA>::iterator i;
		for ( i = data_TTAA.begin(); i != data_TTAA.end(); ++i )
		{
			if( i->date == base.memory.date)
			{
				check = true;
				i->data_.push_back(base);
				break;
			}
		}
		if(check == false)
		{
			new_base_.date = base.memory.date;
			new_base_.data_.push_back(base);
			data_TTAA.push_back( new_base_ );
		}
	}
	
}


