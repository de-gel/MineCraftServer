/*!
 * \file TCPSession.h
 * \date 2017/06/27 14:08
 *
 * \author duxunzhi
 * 
 *
 *
 * 封装一个TCPSession类，使得该类主要处理连接和信息收发的问题
 * 
 *
 * \note
*/

#pragma once

#include "../../libNetEngine/libNetEngine/NetServiceInterface.h"


#include <iostream>



using namespace std;

class CServerBase;


#define   SESSION_BUF_SIZE   1024

class CTCPSession: public ITCPClientHandler
{
public:
	CTCPSession(CServerBase* pServer);
	virtual ~CTCPSession();

	
	//bool SendData(const char* pszData, int iLen);
	bool SendData(char* pszData, int iLen);


	bool getLocalAddr(unsigned long& addr, int& iPort) ;

	bool getRemoteAddr(unsigned long& addr, int& iPort);

	//bool SendData1(const char*  pszData);
	bool isConnect() { return m_bConnect; }

	void setConnect(bool bConnect) { m_bConnect = bConnect; }

	//from ITCPClientHandler
	//从基类继承过来的接口
	virtual void OnDisconnect() override;
	virtual void OnConnect(ITCPClient* pClient) override;
	virtual int OnRead(const void* pBuff, unsigned int nSize) override;


	//self 提供给外部继承的session接口
	virtual void OnSessionConnect() {}
	virtual void OnSessionDisconnect() {}
	virtual int OnSessionRead(const char* buf, unsigned short size){ return size; };



	ITCPClient* getTcpClient() const{ return m_pTcpClient; }
	void setTcpClient(ITCPClient* pClient) { m_pTcpClient = pClient; }

private:
	//知道自己属于哪个服务器
	CServerBase* m_pServerbase;

	//
	ITCPClient*  m_pTcpClient;

	//是否链接
	bool		 m_bConnect;

	//
	char         m_sessionbuf[SESSION_BUF_SIZE];
	char         m_recvsessionbuf[SESSION_BUF_SIZE];
};

