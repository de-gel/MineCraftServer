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


	//保存侦听器指针
	m_vecListener.push_back(plistener);
}

void CNetServer::runService()
{
	io_service_.run();
}

bool CNetServer::postConnectService(const char* szAddr, int nPort, ITCPClientHandler* pHandler)
{

	//只有初始化时候使用shared_ptr初始化的时候，函数内部才能使用shared_from_this替代this
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

