/*!
 * \file NetServiceInterface.h
 *
 * \author duxunzhi
 * \date ���� 2017
 *
 * ����ⲿ����ӿ�
 */


#pragma once

 

#ifndef NULL
#define  NULL   0
#endif


#define  SAFE_DELETE(p)     if(p!=NULL){delete p; p = NULL;}


enum OUTPACKET_RESULT
{
	OUTPACKET_RESULT_SUCCESS = 1,
	OUTPACKET_RESULT_NO_ROOM_IN_BUFFER = 2,
	OUTPACKET_RESULT_NOT_CONNECTED = 3,
	OUTPACKET_RESULT_SOCKET_ERROR = 4,
};


/*!
 * \class ITCPClient
 *
 * \brief 
 *
 * \author duxunzhi
 * \date ���� 2017
 * ����һ��tcp���ӵĽӿ�
*/
class ITCPClient
{
public:
	// �õ���ǰ���socket���
	//virtual unsigned int GetHandler() = 0;

	//��������
	virtual unsigned long SendData(const char* pszData, int iLen) = 0;
	
	// �ر�����
	virtual bool closeConnection() = 0; 


	//// dwAddr Ϊ�����ַ, nPort Ϊ���ص�ַ
	// ��ȡ���ص�ַ
	//ע�� ipv4
	virtual bool getLocalAddr(unsigned long& addr, int& iPort) = 0; 
	
	// ��ȡ�Զ˵�ַ
	//ע�� ipv4
	virtual bool getRemoteAddr(unsigned long& addr, int& iPort) = 0;

	//virtual void SetRecvBuffMaxLen(int iMaxLen) = 0; // ���ý��ջ��������С
	//virtual void SetSendBuffMaxLen(int iMaxLen) = 0; // ���÷��ͻ�������С 
	//virtual DWORD GetTotalSendBytes() = 0;
	//virtual DWORD GetTotalRecvBytes() = 0;
	//virtual void SetOption(DWORD dwOption, DWORD dwValue) = 0; // ���ø�socket��һЩ���� 
};



/*!
* \class ITCPClientHandler
*
* \brief
*
* \author duxunzhi
* \date ���� 2017
* ����һ��tcp���ӵĻص�
*/
class ITCPClientHandler
{
public:
	//�û�����disconnectʱ�ص�����
	virtual void  OnDisconnect() = 0;
	// �û�Post���ӳɹ�ʱ����Ҫ�õ���ǰ��TcpClient�����Է�������
	virtual void  OnConnect(ITCPClient* pClient) = 0;
	// ���ض�ȡ�����ݴ�С
	virtual int  OnRead(const void* pBuff, unsigned int nSize) = 0;
};

/*!
* \class IAccpetorHandler
*
* \brief
*
* \author duxunzhi
* \date ���� 2017
* ����һ��tcp���ӵĻص�
*/

class IAccpetorHandler
{
public:
	virtual ITCPClientHandler* onAcceptor(ITCPClient* pNewClient) = 0;
};


/*!
* \class INetService
*
* \brief
*
* \author duxunzhi
* \date ���� 2017
* ������ʵ�����ӿ�
*/
class INetService
{
	
public:
	//
	virtual void Init() = 0;

	virtual void Destory() = 0;

	virtual void runService() = 0;

	//���һ��
	virtual void addAcceptService(const char* ip,int port ,IAccpetorHandler* acceptorhandler) = 0;

	//���ӵ�һ��Ŀ�������
	virtual bool postConnectService(const char* szAddr, int nPort, ITCPClientHandler* pHandler) = 0;
	


};


// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBNETENGINE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBNETENGINE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef LIBNETENGINE_EXPORTS
#define LIBNETENGINE_API __declspec(dllexport)
#else
#define LIBNETENGINE_API __declspec(dllimport)
#endif

extern "C" LIBNETENGINE_API INetService*   GetNetEngine();


typedef INetService* (*PFUNC_GETNETENGINE)();