#include "Room.h"
#include "define.h"
#include "IDgenerator.h"

#include "RoomManager.h"

CRoom::CRoom(CNetPlayer* player)
{


	m_ihostID = player->getID();
	m_iroomID = CIDgenerator::getInstance()->getNewestID(CIDgenerator::ID_TYPE_ROOM);

	m_vecPlayers.clear();

}

CRoom::CRoom()
{
	m_ihostID = INVALID_ID;
	m_iroomID = CIDgenerator::getInstance()->getNewestID(CIDgenerator::ID_TYPE_ROOM);
	m_vecPlayers.clear();

}

CRoom::~CRoom()
{

	printf("~CRoom\n");
	m_ihostID = INVALID_ID;
	m_iroomID = INVALID_ID;
	m_vecPlayers.clear();
}

void CRoom::erasePlayer(CNetPlayer* player)
{
	//vector<CNetPlayer*>::iterator  iter = m_vecPlayers.begin();
	//for (; iter != m_vecPlayers.end();++iter)
	//{
	//	if ((*iter) == player)
	//	{
	//		(*iter)->setRoom(nullptr);

	//		m_vecPlayers.erase(iter);
	//		break;
	//	}
	//}

	vector<CNetPlayer*>::iterator  iter = std::find(m_vecPlayers.begin(), m_vecPlayers.end(), player);

	if (iter != m_vecPlayers.end())
	{
		//设定房间
		(*iter)->setRoom(nullptr);
		//登录状态出去
		CRoomManager::getInstance();// ->SignoutPlayer((*iter)->getID());

		m_vecPlayers.erase(iter);
	}


}

void CRoom::broadcastToRoom(const char* message)
{

	//std::vector<int>  incvect;

	//incvect.push_back(1);
	//incvect.push_back(2);
	//incvect.push_back(3);

	//std::vector<int>::iterator  iter = incvect.begin();

	//for (; iter != incvect.end(); ++iter)
	//{
	//	printf("iter content is [%d]\n",*iter);
	//}

	//CNetPlayer player1(NULL);
	//CNetPlayer player2(NULL);

	////std::vector<CNetPlayer*> m_vecPlayers;
	//m_vecPlayers.clear();
	//
	//m_vecPlayers.push_back(&player1);
	//m_vecPlayers.push_back(&player2);

	std::vector<CNetPlayer*>::iterator  iter = m_vecPlayers.begin();

	printf("m_vecPlayers size is = [%d]\n", m_vecPlayers.size());
	printf("*tier = [%d]\n", (*iter)->getID());

	for (; iter != m_vecPlayers.end(); ++iter)
	{
		std::string message = "this is room message";
		(*iter)->sendData(message.c_str(), message.length());
	}
}

void CRoom::pushPlayerIDToRoomManager()
{
	vector<CNetPlayer*>::iterator  iter = m_vecPlayers.begin();
	for (; iter != m_vecPlayers.end(); ++iter)
	{
		CRoomManager::getInstance()->SignInPlayer((*iter)->getID());
		//rm::SignInPlayer((*iter)->getID());
	}
}
