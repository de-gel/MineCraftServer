/*!
 * \file TCPSession.h
 * \date 2017/06/27 14:08
 *
 * \author duxunzhi
 * 
 *
 *
 * ��װһ��TCPSession�࣬ʹ�ø�����Ҫ�������Ӻ���Ϣ�շ�������
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
	//�ӻ���̳й����Ľӿ�
	virtual void OnDisconnect() override;
	virtual void OnConnect(ITCPClient* pClient) override;
	virtual int OnRead(const void* pBuff, unsigned int nSize) override;


	//self �ṩ���ⲿ�̳е�session�ӿ�
	virtual void OnSessionConnect() {}
	virtual void OnSessionDisconnect() {}
	virtual int OnSessionRead(const char* buf, unsigned short size){ return size; };



	ITCPClient* getTcpClient() const{ return m_pTcpClient; }
	void setTcpClient(ITCPClient* pClient) { m_pTcpClient = pClient; }

private:
	//֪���Լ������ĸ�������
	CServerBase* m_pServerbase;

	//
	ITCPClient*  m_pTcpClient;

	//�Ƿ�����
	bool		 m_bConnect;

	//
	char         m_sessionbuf[SESSION_BUF_SIZE];
	char         m_recvsessionbuf[SESSION_BUF_SIZE];
};

