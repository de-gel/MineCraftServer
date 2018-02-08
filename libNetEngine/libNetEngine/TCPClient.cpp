#include "TCPClient.h"
#include <iostream>

CTCPClient::CTCPClient()
{
	m_pSocket = NULL;
	m_pHandler = NULL;

	//bufferһ��Ҫ��ʼ��������д���ַ���ʱ����strlenͳ�Ƴ��Ȼ������⡣
	memset(m_szbuf, 0, BUF_SIZE);

}


CTCPClient::~CTCPClient()
{
}

unsigned long CTCPClient::SendData(const char* pszData, int iLen)
{
	
	if (!m_pSocket)
	{
		return OUTPACKET_RESULT_NOT_CONNECTED;
	}

	return postSend(pszData, iLen);

}


unsigned int CTCPClient::postSend(const char* pszBuff, int iLen)
{
	// �ϲ㷢���˿հ����ر�����
	if (!pszBuff || iLen <= 0)
	{
		Disconnect();
		return OUTPACKET_RESULT_SOCKET_ERROR;
	}

	m_pSocket->async_send(boost::asio::buffer(pszBuff, iLen),
		boost::bind(&CTCPClient::handle_send, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));

	return OUTPACKET_RESULT_SUCCESS;
}


void CTCPClient::handle_send(const boost::system::error_code& error, size_t bytes_transferred)
{

	if (!error)
	{
		//�ٴζ�ȡdata_������
		printf("handle_send the data is [%d]\n", bytes_transferred);
		//socket_.async_read_some(boost::asio::buffer(data_, max_length),
		//	boost::bind(&session::handle_read, this,
		//	boost::asio::placeholders::error,
		//	boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		m_pSocket->close();
	}
}


void CTCPClient::OnConnect()
{
	if (m_pHandler)
		m_pHandler->OnConnect(this);

	postRecv();
}

void CTCPClient::OnDisconnect()
{
	if (m_pHandler)
	{
		m_pHandler->OnDisconnect();


		//SAFE_DELETE(m_pHandler);
		// ��Handler�Ȳ���գ���OnDestroy��ʱ�������
		m_pHandler = nullptr;
	}

	//�ر�socket
	if (m_pSocket->is_open())
	{
		boost::system::error_code error;
		m_pSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);

		if (error)
		{
			printf(error.message().c_str());
		}	
	}
	

	
}

void CTCPClient::Disconnect()
{
	OnDisconnect();
}

bool CTCPClient::postConnect(boost::asio::io_service& io_service_, const char* ip, int port, ITCPClientHandler* pHandler)
{

	if (!pHandler || !CreateSocket(io_service_))
		return false;

	m_pHandler = pHandler;

	//ת��һ��ip��ַ
	boost::asio::ip::address address;
	address = address.from_string(ip);
	tcp::endpoint  endpoint(address, port);

	m_pSocket->async_connect(endpoint,
		boost::bind(&CTCPClient::handle_connect, this,
		boost::asio::placeholders::error));

	return true;
}


void CTCPClient::handle_connect(const boost::system::error_code& error)
{
	if (!error)
	{
		OnConnect();
	}
	else
	{
		
		printf(error.message().c_str());
	}
}


bool CTCPClient::CreateSocket(boost::asio::io_service& io_service_)
{
	m_pSocket = new tcp::socket(io_service_);
	
	if (m_pSocket == NULL)
		return false;


	//tcp::no_delay option(true);
	//m_pSocket->set_option(option);

	return true;
}

bool CTCPClient::postRecv()
{

	if (!RecvEx())
		return false;

	return true;
}

bool CTCPClient::RecvEx()
{
	m_pSocket->async_receive(boost::asio::buffer(m_szbuf, BUF_SIZE),
		boost::bind(&CTCPClient::handle_recv, this,
		boost::asio::placeholders::error));
		
	return true;
}


bool CTCPClient::handle_recv(const boost::system::error_code& error)
{
	
	if (!error)
	{
		//printf("the buffer elem content is [%s]\n", m_inbuffer.GetData());


		printf("�����ݳ��ȴ���buf_sizeʱ��������Ҫ�������\n");
		printf("the length of m_szbuf is [%d]\n", strlen(m_szbuf));

		int readlen = m_pHandler->OnRead(m_szbuf, strlen(m_szbuf));

		//m_inbuffer.RemoveData(readlen);
	}
	else
	{

		printf(error.message().c_str());
		return false;
	}

	//������������
	postRecv();

	return true;
}

bool CTCPClient::closeConnection()
{
	Disconnect();

	return true;
}

bool CTCPClient::getLocalAddr(unsigned long& addr, int& iPort)
{

	//ת��һ��ip��ַ
	tcp::endpoint  endpoint = m_pSocket->local_endpoint();
	addr = endpoint.address().to_v4().to_ulong();
	iPort = endpoint.port();

	return true;
}


bool CTCPClient::getRemoteAddr(unsigned long& addr, int& iPort)
{
	tcp::endpoint  endpoint = m_pSocket->remote_endpoint();
	addr = endpoint.address().to_v4().to_ulong();
	iPort = endpoint.port();

	return true;
}