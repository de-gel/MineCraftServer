#pragma once



#include "ClientSsesion.h"
#include <NetAnalyser.h>


#define   SEND_BUF_LEN  512


namespace tutorial{
	class C2SRequestRoomInfo;
}

class CRoom;

class CNetPlayer
{
public:
	CNetPlayer(CClientSession* session);
	~CNetPlayer();



	void sendData(const char* data, int len);

	


	void responsePlayerID();

	
	

	static void onPraseResponsePlayerinfo(int playerid,void* self);
	static void onPraseRequestRoomid(int playerid, void* self);
	static void onPraseResponseRoomid(int roomid, int hostid, void* self);

	static void onPraseRequestSeed(int playerid, int roomid, void* self);

	int getID()  { return m_ipID; }
	void setID(int val) { m_ipID = val; }

	CRoom* getRoom() const { return m_pRoom; }
	void setRoom(CRoom* val) { m_pRoom = val; }
	bool   IsInRoom() const{ return (m_pRoom != nullptr); }




	CNetAnalyser* getNet_analyser() const { return m_net_analyser; }
	void setNet_analyser(CNetAnalyser* val) { m_net_analyser = val; }
private:
	void clearSendBuf(){memset(sendbuf, 0, SEND_BUF_LEN);};


	int     m_ipID;
	CClientSession*  m_pSession;
	CRoom*   m_pRoom;


	char    sendbuf[SEND_BUF_LEN];




	CNetAnalyser*     m_net_analyser;


	NETANALYSER_INIT_PARAM  m_netanalyser_init_param;
};

