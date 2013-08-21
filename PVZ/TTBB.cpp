#include "WriteFile.h"

void recording_and_write::TTBB(char * code)
{

	DateSurfase_TTBB new_base_;
	TTBB_Database base;
	base.information = true;
	bool theEnd = false;					// Завершение программы
	if (code == NULL)theEnd = true;
	int step = 1;							// Шаг выполнения программы	
	while ((*code) != '\0' && theEnd !=true )
	{
		switch (step)
		{
		case 1 : // Нахождение времени и даты запуска зонда
			{
				code = DateTime(code,base.memory);
				step++;
				break;
			}
		case 2:// Находжение большого района и станции
			{
				code = DistrictStation(code, base.number);
				step++;
			}
			  
		case 3:
			{
				if( strstr( code, "NIL" ) == NULL ) //Проверка на отсутствие данных
				{

					bool key = true;
					int GGPPP = strtol(code, &code, 10);
					while( (*code) != '\0' )
					{
						Temp_Base new_level;
						if ((*code) == '/') 
						{
							code +=3;
							new_level.number = GGPPP ;
						} 
						else
						{
							new_level.number = GGPPP / 1000;
							new_level.pressure = GGPPP % 1000; 
						}
						new_level.information = true;	
						code = TempDewpoint(code, new_level.info_temp);
 						base.level.push_front(new_level);
						GGPPP = strtol(code, &code, 10);
						if (GGPPP == 21212)
						{
							step++;
							theEnd = true;
							break;
						}
					}				
				}
				else
				{
					theEnd = true;
					step++;
					base.information = false;
				}
				step++;
				break;
			}
		case 4 :
			{
				int GGPPP = strtol(code, &code, 10);
				while( (*code) != '\0' && GGPPP != 31313 )
				{
					list<Wind_Base> new_wind;
					Wind_Base old_wind;
					while (GGPPP != 31313 && (*code) != '\0' )
					{
						old_wind.number = GGPPP / 1000;
						old_wind.information = true;
						old_wind.pressure = GGPPP % 1000;
						code = Wind( code, old_wind.wind );
						new_wind.push_front(old_wind);
						GGPPP = strtol(code, &code, 10);
					}
					base.level_wind.push_back(new_wind);
				}
				step++;
				break;
			}	
		case 5 :	
			{
				step++;
				//case 4 : 31313 или 41414
			}
		default:
			{
				theEnd = true;
				break;
			}
			
		}
		if (theEnd == true)
		{
			break;
		}
	}
	// Заполение списка ТТBB данными
	if(data_TTBB.size() == 0) 
	{
		new_base_.date = base.memory.date;
		new_base_.data_.push_back(base);
		data_TTBB.push_back( new_base_ );
	}
	else
	{
		bool check = false;
		list<DateSurfase_TTBB>::iterator i;
		for ( i = data_TTBB.begin(); i != data_TTBB.end(); ++i )
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
			data_TTBB.push_back( new_base_ );
		}
	}
	
}