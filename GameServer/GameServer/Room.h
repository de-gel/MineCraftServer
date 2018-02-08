#pragma once

#include "NetPlayer.h"

#include <vector>
#include <algorithm>
using namespace std;


class CRoomManager;

class CRoom
{
public:
	static const int  room_size = 4;

	//enum E_ROOM_STATE
	//{
	//	E_ROOM_STATE_EMPTY    =1,
	//	E_ROOM_STATE_WELCOME  =2,
	//	E_ROOM_STATE_FULL     =3,
	//	E_ROOM_STATE_LOCKED   =4

	//};


	CRoom();
	CRoom(CNetPlayer* player);
	~CRoom();


	void addPlayer(CNetPlayer* player)
	{
		m_vecPlayers.push_back(player);

		player->setRoom(this);

	}
	void erasePlayer(CNetPlayer* player);
	
	void clearAllPlayer()
	{
		m_vecPlayers.clear();
	}


	void broadcastToRoom(const char* message);


	//获取房间id
	int getroomID() const { return m_iroomID; }
	void setroomID(int val) { m_iroomID = val; }

	//获取房主id
	int gethostID() const { return m_ihostID; }
	void sethostID(int val) { m_ihostID = val; }

	bool IsFull() const { return (m_vecPlayers.size() == room_size); }
	bool IsEmpty() const { return (m_vecPlayers.size() == 0); }

	//
	bool  hasPlayer(CNetPlayer* player)
	{
		vector<CNetPlayer*>::iterator  iter = m_vecPlayers.begin();
		for (; iter != m_vecPlayers.end(); ++iter)
		{
			if ((*iter)->getID() == player->getID())
			{
				return true;
			}
		}
		return false;
	}

	void pushPlayerIDToRoomManager();


private:
	int                    m_iroomID;
	int                    m_ihostID;
	vector<CNetPlayer*>    m_vecPlayers;
};

