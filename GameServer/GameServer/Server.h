#pragma once


#include "SsesionMgr.h"

class Server
{
public:
	Server(boost::asio::io_service& io_service, short port)
		: io_service_(io_service),
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
	{
		start_accept();
	}

	

private:
	void start_accept() 
	{
		session* new_session = new session(io_service_);

	

		acceptor_.async_accept(new_session->socket(),
			boost::bind(&Server::handle_accept, this, new_session,
			boost::asio::placeholders::error));
	}

	void handle_accept(session* new_session,
		const boost::system::error_code& error)
	{
		if (!error)
		{

			std::string ip_address = new_session->socket().remote_endpoint().address().to_string();
			int         port = new_session->socket().remote_endpoint().port();

			printf("the client [%s], port is [%d] connected\n", ip_address.c_str(), port);

			CSsesionMgr::getInstance()->addSsesion(static_cast<chat_session_ptr>(new_session));
			new_session->start();

			//一段有人登陆就发送消息给其他人所有人
			CSsesionMgr::getInstance()->testall(ip_address, port );
		}
		else
		{
			delete new_session;
		}

		start_accept();
	}

	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
};


typedef boost::shared_ptr<Server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;