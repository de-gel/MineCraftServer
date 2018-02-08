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

	//Ϊ������һ���߼�����Ż�
	LORD::Root::Instance()->initialize_mini();

	//��ʼ��һЩ��Ҫ���
	MineCraft::initialize();

	//�½�һ������
	m_mcWorld = LordNew MineCraft();


	m_mcWorld = MineCraft::Instance();

	//��ʼ��
	m_mcWorld->init();


	i64 seed = m_mcWorld->getSeed();
	printf("the seed is [%lld]\n", seed);
}



bool CGamesServer::Init()
{
	if (!CServerBase::Init())
		return false;
	

	//��ʼ����������
	setRoomManager(CRoomManager::getInstance());

	setNetPlayerManager(CNetPlayerManager::getInstance());

	initMCWorld();
	

	return true;
}

