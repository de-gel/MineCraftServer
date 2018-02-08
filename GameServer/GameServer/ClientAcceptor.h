#pragma once
/*!
* \file ClientAcceptor.h
* \date 2017/06/27 14:12
*
* \author duxunzhi
* Contact: duxunzhi@supernano.com
*
*
*
* TODO: tcp��acceptor�����������ӽ���ͶϿ�
*
* \note
*/



#include "../../ServerFramework/ServerFramework/ServerBase.h"

class CClientSession;
class CNetPlayer;

class CClientAcceptorHandler :
	public IAccpetorHandler
{
public:
	CClientAcceptorHandler(CServerBase* server);
	virtual ~CClientAcceptorHandler();

	ITCPClientHandler* onAcceptor(ITCPClient* pNewClient) override;


	

private:
	CClientSession* createClientSession();

	CServerBase* m_pserver;
	

};

