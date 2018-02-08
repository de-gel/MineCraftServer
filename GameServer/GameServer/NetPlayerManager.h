#pragma once


#include "MacroInclude.h"
#include "NetPlayer.h"
#include <boost/unordered_map.hpp>
#include "../../Utils/Utils/Sington.h"

class CGameServer;

class CNetPlayerManager :
	 public CSington<CNetPlayerManager>
{
public:

	void addPlayer(CNetPlayer* player)
	{
		m_playerMap.insert(make_pair(player->getID(), player));
	};


	void removePlayer(CNetPlayer* player)
	{
		removePlayer(player->getID());
	};

	void removePlayer(int playerID)
	{
		m_playerMap.erase(playerID);
	};


	CNetPlayer* getPlayerByPID(int pid)
	{
		std::map<int, CNetPlayer*>::iterator iter = m_playerMap.find(pid);

		if (iter == m_playerMap.end())
		{
			return nullptr;
		}

		CNetPlayer* player = iter->second;
		return player;
	}

	CNetPlayer* createPlayer(CClientSession* client_session)
	{
		CNetPlayer* player = new CNetPlayer(client_session);
		return player;
	}


private:

	std::map<int, CNetPlayer*>  m_playerMap;

};

