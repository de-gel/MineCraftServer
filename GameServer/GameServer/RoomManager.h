#pragma once

#include "Room.h"

#include <boost/unordered_map.hpp>
#include "MacroInclude.h"

#include  "algorithm"
#include "../../Utils/Utils/Sington.h"

class CRoomManager :public CSington<CRoomManager>
{
public:
	CRoomManager();
	~CRoomManager();

	void addRoom(CRoom* Room)
	{
		m_RoomMap.insert(make_pair(Room->getroomID(), Room));
		m_PIDRoomMap.insert(make_pair(Room->gethostID(), Room));

		
	};


	void removeRoom(CRoom* Room)
	{
		removeRoombyID(Room->getroomID());
		removeRoombyPID(Room->gethostID());
	};




	CRoom* getRoomByPID(int pid)
	{
		std::map<int, CRoom*>::iterator iter = m_PIDRoomMap.find(pid);

		if (iter == m_PIDRoomMap.end())
		{
			return nullptr;
		}

		CRoom* Room = iter->second;
		return Room;
	}

	CRoom* getRoomByID(int roomid)
	{
		std::map<int, CRoom*>::iterator iter = m_RoomMap.find(roomid);

		if (iter == m_RoomMap.end())
		{
			return nullptr;
		}
		CRoom* Room = iter->second;
		return Room;
	}



	CRoom* createRoom(CNetPlayer* host = nullptr)
	{
		CRoom* Room = nullptr;
		if (host == nullptr)
			Room = new CRoom();
		else
			Room = new CRoom(host);

		return Room;
	}


	void SignInPlayer(int playerID)
	{
		m_vecPlayer.push_back(playerID);
	}

	void SignoutPlayer(int playerID)
	{
		vector<int>::iterator  iter = std::find(m_vecPlayer.begin(), m_vecPlayer.end(), playerID);
		if (iter != m_vecPlayer.end())
			m_vecPlayer.erase(iter);
	}

private:
	void removeRoombyID(int RoomID)
	{
		m_RoomMap.erase(RoomID);
	};

	void removeRoombyPID(int hostID)
	{
		m_PIDRoomMap.erase(hostID);
	};


	map<int, CRoom*>   m_RoomMap;      //用roomid作为key
	map<int, CRoom*>   m_PIDRoomMap;  //用hostID作为key


	vector<int>           m_vecPlayer;   //用来保存已经开房间的人
	/*vector<CRoom*>  */

};

