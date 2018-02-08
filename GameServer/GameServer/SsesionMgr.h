/*!
* \file SsesionMgr.h
* \date 2017/06/01 18:01
*
* \author alex.d
* Contact: duxunzhi@supernano.com
*
* \brief  Manage all ssesion
*
* TODO: long description
*
* \note
*/

#pragma once

#include "Sssesion.h"
#include <set>

class CSsesionMgr
{
public:
	void addSsesion(chat_session_ptr pssesion);

	void removieSsesion(chat_session_ptr pssesion);


	chat_session_ptr getSsesion(chat_session_ptr pssesion)
	{
		return *(m_setSsesion.find(pssesion));
	}

	
	void testall(const std::string& ip_address, int port)
	{
		char strport[8];
		_itoa(port, strport, 10);
	
		std::string msg = "a new connect from [" + ip_address + "], port is[" + strport + "]\n";


		for (std::set<chat_session_ptr>::iterator iter = m_setSsesion.begin();
			iter != m_setSsesion.end();iter++)
		{
			(*iter)->send(msg.c_str());
		}


	}
	
	static CSsesionMgr* getInstance()
	{
		if (m_pInstance == 0)
		{
			m_pInstance = new CSsesionMgr();
		}

		return m_pInstance;
	}


	~CSsesionMgr()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
		}
	};


private:
	CSsesionMgr()
	{

	};


	static CSsesionMgr*  m_pInstance;

	//使用带有引用计数的ssesion_ptr 代替 
	std::set<chat_session_ptr>  m_setSsesion;

};

