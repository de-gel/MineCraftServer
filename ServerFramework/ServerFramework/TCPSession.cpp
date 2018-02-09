#include "TCPSession.h"


#include "ServerBase.h"
//#include "protobuf/BasePROTO.pb.h"
//#include <google/protobuf/message_lite.h>

CTCPSession::CTCPSession(CServerBase* pServer)
{
	m_pTcpClient = NULL;
	m_pServerbase = pServer;
	m_bConnect	  = false;

	memset(m_sessionbuf, 0, SESSION_BUF_SIZE);
	memset(m_recvsessionbuf, 0, SESSION_BUF_SIZE);
}

CTCPSession::~CTCPSession()
{
}

bool CTCPSession::SendData(  char* pszData, int iLen)
{
	if (!m_pTcpClient || !isConnect())
	{
		printf("no client \n");
		return false;
	}
		


	//tutorial::ContainerMessage container;
	//container.set_buf(pszData, iLen);
	//container.set_msgsize(iLen);
	//container.set_msgid(110);

	//container.SerializeToArray(m_sessionbuf, SESSION_BUF_SIZE);


	m_pTcpClient->SendData(pszData, iLen);


	return true;
}

bool CTCPSession::getLocalAddr(unsigned long& addr, int& iPort)
{
	if (!m_pTcpClient || !isConnect())
	{
		printf("no client \n");
		return false;
	}

	return m_pTcpClient->getLocalAddr(addr, iPort);
}

bool CTCPSession::getRemoteAddr(unsigned long& addr, int& iPort)
{
	if (!m_pTcpClient || !isConnect())
	{
		printf("no client \n");
		return false;
	}

	return m_pTcpClient->getRemoteAddr(addr, iPort);

}



void CTCPSession::OnDisconnect()
{
	m_bConnect = false;
}

void CTCPSession::OnConnect(ITCPClient* pClient)
{
	setTcpClient(pClient);


	if (m_pServerbase)
		m_pServerbase->addConnection(this);


	m_bConnect = true;

	OnSessionConnect();
}

int CTCPSession::OnRead(const void* pBuff, unsigned int nSize)
{
	if (nSize > 1024)
	{
		printf("CTcpSession::OnRead收到了底层发上来的超过64k的数据%d.", nSize);
		return -1;
	}

	OnSessionRead((const char*)pBuff, nSize);
	
	/*memcpy_s(m_recvsessionbuf, SESSION_BUF_SIZE, pBuff, nSize);
	tutorial::ContainerMessage containerrecv;

	containerrecv.ParseFromArray(m_recvsessionbuf, 1024);*/
	


	//char* p =&(container.buf().c_str());
	//printf("msgid = [%d],messageid = [%d],content = [%s]\n", containerrecv.msgid(), containerrecv.msgsize(), containerrecv.buf().c_str());



	//char content[256];

	//memset(content, 0, 256);

	//memcpy(content, pBuff, nSize);

	//printf("CTCPSession::OnRead [%s]\n", (char*)content);

	return 	nSize;
		
}
