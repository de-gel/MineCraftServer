#include "ClientAcceptor.h"
#include "ClientSsesion.h"
#include "NetPlayer.h"
#include  "Room.h"
#include "GamesServer.h"
#include "IDgenerator.h"


CClientAcceptorHandler::CClientAcceptorHandler(CServerBase* server)
{
	m_pserver = server;
}

CClientAcceptorHandler::~CClientAcceptorHandler()
{
}

//����֮�󷵻�һ�����õ�tcpclienthandler
ITCPClientHandler* CClientAcceptorHandler::onAcceptor(ITCPClient* pNewClient)
{

	CClientSession* client_session = createClientSession();

	return client_session;
}


CClientSession* CClientAcceptorHandler::createClientSession()
{
	CClientSession* client_session = new CClientSession(m_pserver);
	
	return client_session;
}
