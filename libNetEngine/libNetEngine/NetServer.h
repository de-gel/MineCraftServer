
/*!
 * \file NetServer.h
 *
 * \author duxunzhi
 * \date 六月 2017
 *
 * 网络服务器的继承实现
 * 使用boost的机制封闭实现，可以自己实现IOCP或者LINUXepoll等软代码
 *
 */


#pragma once
#include "NetServiceInterface.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <vector>
using boost::asio::ip::tcp;
using namespace std;


#include "Listener.h"




/*!
 * \class classname
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: 使用boost机制实现的服务器实际实现。
 *       包括连接其他服务器功能和自己做服务器功能
 *
 * \note 
 *
 * \author duxunzhi
 *
 * \version 1.0
 *
 * \date 六月 2017
 *
 * Contact: duxunzhi@supernano.com
 *
 */


class CNetServer :
	public INetService
{
public:
	CNetServer();
	~CNetServer();

	 void Init() override;

	 void Destory() override;


	 void addAcceptService(const char* ip, int port, IAccpetorHandler* acceptorhandler) override;
	 bool postConnectService(const char* szAddr, int nPort, ITCPClientHandler* pHandler) override;
	 
	 void handle_accept(const boost::system::error_code& error);

	 void runService() override;

	 


///////////////////////////////////////
	 
public:
	//CNetServer(boost::asio::io_service& io_service)
	//	: io_service_(io_service),
	//	acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
	//{
	//	//start_accept();
	//}


private:
	
	boost::asio::io_service io_service_;

	//带有引用计数的指针
	vector<share_listener_ptr>  m_vecListener;


	tcp::acceptor* acceptor_;
private:

};

