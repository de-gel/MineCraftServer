#pragma once


#include "../../Utils/Utils/Sington.h"

class CIDgenerator:public CSington<CIDgenerator>
{
	

public:

	CIDgenerator()
	{
		m_playeridCount = 10001;
		m_roomidCount = 91001;

	};
	~CIDgenerator(){};

	enum EID_TYPE
	{
		ID_TYPE_PLAYER = 1,
		ID_TYPE_ROOM = 2,
	};



	int  getNewestID(int type)
	{
		
		switch (type)
		{
		case ID_TYPE_PLAYER:
			return m_playeridCount++;
		case ID_TYPE_ROOM:
			return m_roomidCount++;
		default:break;

		}
	
			
		return -1;

	}

private:

	int m_playeridCount;
	int m_roomidCount;


};



