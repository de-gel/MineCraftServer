#include "GamesServer.h"


#include "ClientAcceptor.h"

#include "NetPlayer.h"

#include "RoomManager.h"


#include <iostream>
using namespace std;



CGamesServer::CGamesServer()
{
}


CGamesServer::~CGamesServer()
{
}


bool CGamesServer::OnInit()
{
	printf("CGamesServer::OnInit\n");

	


	return true;
}

bool CGamesServer::OnBeforeStart()
{
	return true;
}

bool CGamesServer::OnAfterStart()
{

	if (!GetNetSevice())
	{
		return false;
	}

	std::string  strIP = "127.0.0.1";
	int port = 6601;

	IAccpetorHandler* pAccepothandler = new CClientAcceptorHandler(this);
	GetNetSevice()->addAcceptService(strIP.c_str(), port, pAccepothandler);

	return true;
}

void CGamesServer::OnStop()
{
	//SAFE_DELETE(m_pNetService);
}

void CGamesServer::OnRun()
{
	static unsigned int  nLoopCount = 0;

	nLoopCount++;
}

void CGamesServer::initMCWorld()
{
	//LORD::ROOT
	LordNew(LORD::Root);

	//为网络做一种逻辑最简单优化
	LORD::Root::Instance()->initialize_mini();

	//初始化一些必要组件
	MineCraft::initialize();

	//新建一个世界
	m_mcWorld = LordNew MineCraft();


	m_mcWorld = MineCraft::Instance();

	//初始化
	m_mcWorld->init();


	i64 seed = m_mcWorld->getSeed();
	printf("the seed is [%lld]\n", seed);
}



bool CGamesServer::Init()
{
	if (!CServerBase::Init())
		return false;
	

	//初始化各个管理
	setRoomManager(CRoomManager::getInstance());

	setNetPlayerManager(CNetPlayerManager::getInstance());

	initMCWorld();
	

	return true;
}

