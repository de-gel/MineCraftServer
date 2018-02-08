#pragma once


#include "../../ServerFramework/ServerFramework/ServerBase.h"

class CNetPlayer;

class CGameSession :
	public CTCPSession
{
public:
	CGameSession(CServerBase* pserver) :CTCPSession(pserver){};
	~CGameSession();

	virtual void OnSessionConnect() override;

	virtual void OnSessionDisconnect() override;




};

