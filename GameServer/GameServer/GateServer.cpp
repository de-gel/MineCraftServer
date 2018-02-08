#include "GateServer.h"
#include "GameSession.h"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
using boost::asio::ip::tcp;

CGateServer::CGateServer()
{
}


CGateServer::~CGateServer()
{
}

bool CGateServer::OnInit()
{
	printf("CGateServer::OnInit\n");


	return true;
}

bool CGateServer::OnBeforeStart()
{

	printf("CGateServer::OnBeforeStart\n");
	return true;
}

bool CGateServer::OnAfterStart()
{

	if (!GetNetSevice())
	{
		return false;
	}

	std::string  strIP = "127.0.0.1";
	int port = 6601;

	//CGameSession* gamesession = new CGameSession(this);

	CGameSession* pgamesession = new CGameSession(this);

	//shared_ptr<CGameSession> gamesession(pgamesession);


	//if (gamesession._Get() != pgamesession)
	//{
	//	BOOST_ASSERT(gamesession._Get() != pgamesession);
	//}



	GetNetSevice()->postConnectService(strIP.c_str(), port, pgamesession);

	return true;
}

void CGateServer::OnStop()
{
	//SAFE_DELETE(m_pNetService);
}

void CGateServer::OnRun()
{
	static unsigned int  nLoopCount = 0;

	nLoopCount++;
}