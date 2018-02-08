#pragma once

#include "NetServiceInterface.h"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

#define  SAFE_DELETE(p)     if(p!=NULL){delete p; p = NULL;}

class CListener//: public boost::enable_shared_from_this<CListener>
{
public:
	CListener(){};
	~CListener();

	void Init(boost::asio::io_service& io_service_, const char* ip, int port, IAccpetorHandler* acceptorhandler);
	

	void startAccept();


	void Destroy();


	//»Øµ÷
	void handle_accept(tcp::socket* psocket, const boost::system::error_code& error);
private:
	//tcp::socket*	m_pSocket;
	tcp::acceptor* acceptor_;
	IAccpetorHandler* m_pAcceptHandler;
	boost::asio::io_service* p_io_service_;

	int acceptCount;

};


typedef boost::shared_ptr<CListener> share_listener_ptr;