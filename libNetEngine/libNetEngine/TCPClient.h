/*!
 * \file TCPClient.h
 *
 * \author duxunzhi
 * \date  2017
 *
 * TCP请求的实际实现类。
 */

#pragma once
#include "NetServiceInterface.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>
#include "Buffer.h"

#define BUF_SIZE  1024



#include <vector>
using boost::asio::ip::tcp;
using namespace std;

class CTCPClient :
	public ITCPClient//, public boost::enable_shared_from_this<CTCPClient>
{
public:
	CTCPClient();
	~CTCPClient();

	//itcpinterface
	unsigned long SendData(const char* pszData, int iLen) override;

	bool closeConnection();

	// 获取本地地址
	bool getLocalAddr(unsigned long& addr, int& iPort); 

	// 获取远端地址
	bool getRemoteAddr(unsigned long& addr, int& iPort);


	//
	bool postConnect(boost::asio::io_service& io_service_, const char* ip, int port, ITCPClientHandler* pHandler);

	unsigned int postSend(const char* pszBuff, int iLen);

	bool postRecv();

	
	//
	void SetTcpClientHandler(ITCPClientHandler* pHandler){ m_pHandler = pHandler; }


	//socket相关继承，看有么有必要设置socketbase类封装
	bool CreateSocket(boost::asio::io_service& io_service_);
	void SetSocket(tcp::socket* s){ m_pSocket = s; };

	void OnConnect();
	void OnDisconnect();


	


private:

	//////////////////
	//内部实现
	void Disconnect();

	void handle_connect(const boost::system::error_code& error);

	void handle_send(const boost::system::error_code& error, size_t bytes_transferred);

	bool handle_recv(const boost::system::error_code& error);
	bool RecvEx();

	
	
	


	
	ITCPClientHandler* m_pHandler;
	tcp::socket*	m_pSocket;

	//CBuffer         m_inbuffer;
	//CBuffer         m_outbuffer;

	char            m_szbuf[BUF_SIZE];
	

};

