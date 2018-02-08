/*!
* \file GamesServer.h
* \date 2017/06/27 14:12
*
* \author duxunzhi
* Contact: duxunzhi@supernano.com
*
*
*
* TODO: tcpsessionµÄgameserver¼Ì³ÐÊµÏÖ¡£
*
* \note
*/


#pragma once
#include "../../ServerFramework/ServerFramework/TCPSession.h"
#include <protobuf/ClientAndGame.pb.h>

class CNetPlayer;

class CClientSession :
	public CTCPSession
{
public:
	CClientSession(CServerBase* pServer);
	~CClientSession();

	virtual void OnSessionConnect() override;

	virtual void OnSessionDisconnect() override;

	CNetPlayer* createPlayer();

	virtual int OnSessionRead(const char* buf, unsigned short size) override;


	

private:
private:
	CNetPlayer* player;

	
};

