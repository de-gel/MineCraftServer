#include "Listener.h"

#include "TCPClient.h"


CListener::~CListener()
{
	Destroy();
}

void CListener::Destroy()
{
	//SAFE_DELETE(m_pSocket);
	//不是自己new出来的
	//SAFE_DELETE(m_pAcceptHandler);
	SAFE_DELETE(acceptor_);

}


void CListener::Init( boost::asio::io_service& io_service_, const char* ip, int port, IAccpetorHandler* acceptorhandler)
{



	//转换一次ip地址
	boost::asio::ip::address address;
	address = address.from_string(ip);
	tcp::endpoint  endpoint(address, port);

	//先测试方法1
	acceptor_ = new tcp::acceptor(io_service_, endpoint);

	//acceptor_->open(endpoint.protocol());
	//acceptor_->set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	//acceptor_->bind(endpoint);
	//acceptor_->listen();
	p_io_service_    = &io_service_;
	m_pAcceptHandler = acceptorhandler;



	startAccept();


	
}





void CListener::handle_accept(tcp::socket* psocket,const boost::system::error_code& error)
{
	if (!error)
	{

		printf("the client [%s], port is [%d] connected\n", psocket->remote_endpoint().address().to_string().c_str(), psocket->remote_endpoint().port());
		CTCPClient* tcpclient = new CTCPClient();



		ITCPClientHandler* pClientHandler =   m_pAcceptHandler->onAcceptor(tcpclient);

		if (!pClientHandler)
		{
			printf("pClientHandler not exist,delete socket\n");
			psocket->close();
		}

		tcpclient->SetTcpClientHandler(pClientHandler);
		tcpclient->SetSocket(psocket);
		tcpclient->OnConnect();

		//添加连接计数
		acceptCount++;
	}

	startAccept();

	//start_accept();
}

void CListener::startAccept()
{
	//m_pSocket = new tcp::socket(*p_io_service_);

	tcp::socket* m_pSocket = new tcp::socket(*p_io_service_);

	acceptor_->async_accept(*m_pSocket,
		boost::bind(&CListener::handle_accept, this, m_pSocket,
		boost::asio::placeholders::error));
}
