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


#include "SsesionMgr.h"

CSsesionMgr*  CSsesionMgr::m_pInstance = 0;

void CSsesionMgr::addSsesion(chat_session_ptr pssesion)
{
	m_setSsesion.insert(pssesion);
}

void CSsesionMgr::removieSsesion(chat_session_ptr pssesion)
{
	m_setSsesion.erase(pssesion);
}

