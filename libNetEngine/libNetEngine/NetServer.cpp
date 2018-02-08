#include "NetServer.h"
#include "TCPClient.h"


INetService* GetNetEngine()
{
	return new CNetServer();
}


CNetServer::CNetServer()
{


}


CNetServer::~CNetServer()
{
}

void CNetServer::Init()
{
	m_vecListener.clear();
	acceptor_ = NULL;

}

void CNetServer::Destory()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CNetServer::addAcceptService(const char* ip, int port, IAccpetorHandler* acceptorhandler)
{
	printf("the ip is %s,port is  %d\n", ip, port);

	share_listener_ptr  plistener(new CListener());
	
	plistener->Init(io_service_, ip, port, acceptorhandler);


	//plistener->startAccept();


	//����������ָ��
	m_vecListener.push_back(plistener);
}

void CNetServer::runService()
{
	io_service_.run();
}

bool CNetServer::postConnectService(const char* szAddr, int nPort, ITCPClientHandler* pHandler)
{

	//ֻ�г�ʼ��ʱ��ʹ��shared_ptr��ʼ����ʱ�򣬺����ڲ�����ʹ��shared_from_this���this
	//shared_ptr<CTCPClient> client(new CTCPClient());
	//boost::shared_ptr<CTCPClient> client(new CTCPClient());


	CTCPClient* client = new CTCPClient();

	if (!client)return false;

	if (!client->postConnect(io_service_, szAddr, nPort, pHandler))
	{
		return false;
	}
		

	
	return true;


}

