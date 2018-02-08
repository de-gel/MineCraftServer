// GameServer.cpp : 定义控制台应用程序的入口点。
//


#include "GamesServer.h"
#include "GateServer.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>



using boost::asio::ip::tcp;
using namespace std;

////初始化单例子




class testclass
{

public:
	testclass()
	{
		
		acceptor_ = new tcp::acceptor(io_service_, tcp::endpoint(tcp::v4(), 6601));
		m_pSocket = new tcp::socket(io_service_);
	}


	void run()
	{
		//转换一次ip地址
		//boost::asio::ip::address address;
		//address = address.from_string(ip);

		
	
		


		//tcp::endpoint  endpoint(tcp::v4(), 6601);

		//先测试方法1
		

		//acceptor_->open(endpoint.protocol());
		//acceptor_->set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		//acceptor_->bind(endpoint);
		//acceptor_->listen();


		// 存储回调
		//m_pSocket = new tcp::socket(io_service_);
		//m_pAcceptHandler = acceptorhandler;

		//
		
		acceptor_->async_accept(*m_pSocket,
			boost::bind(&testclass::handle_accept, this,
			boost::asio::placeholders::error));



		io_service_.run();
	
	}


	void testclass::handle_accept(const boost::system::error_code& error)
	{

		printf("CListener::handle_accept\n");

		if (!error)
		{
			printf("success CListener::handle_accept\n");
			//printf("the client [%s], port is [%d] connected\n", session->socket().remote_endpoint().address().to_string().c_str(), session->socket().remote_endpoint().port());


			//session->start();

			getchar();

			//m_pAcceptHandler->onAcceptor(NULL);
		}
		else
		{
			printf("error CListener::handle_accept\n");
		}

		//start_accept();
	}

private:
	
	//tcp acceptor
	tcp::acceptor* acceptor_;

	tcp::socket*   m_pSocket;

	boost::asio::io_service io_service_;
};


void RunServer(CServerBase* g_server)
{
	if (!g_server->Init())
	{
		g_server->Destroy();
	}


	if (!g_server->Start())
	{
		g_server->Destroy();
	}

	//asio服务

	//testclass tc;

	//tc.run();

	g_server->Run();
}

int main(int argc, char* argv[])
{

	CServerBase* pserver = new  CGamesServer();


	//CServerBase* pserver = new  CGateServer();
	

	RunServer(pserver);


	


	


	/*g_server.Destroy();*/



	return 0;
}

