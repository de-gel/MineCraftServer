/*!
 * \file NetServiceInterface.h
 *
 * \author duxunzhi
 * \date 六月 2017
 *
 * 库的外部网络接口
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
 * \date 六月 2017
 * 代表一个tcp连接的接口
*/
class ITCPClient
{
public:
	// 得到当前这个socket句柄
	//virtual unsigned int GetHandler() = 0;

	//发送数据
	virtual unsigned long SendData(const char* pszData, int iLen) = 0;
	
	// 关闭连接
	virtual bool closeConnection() = 0; 


	//// dwAddr 为网络地址, nPort 为本地地址
	// 获取本地地址
	//注意 ipv4
	virtual bool getLocalAddr(unsigned long& addr, int& iPort) = 0; 
	
	// 获取对端地址
	//注意 ipv4
	virtual bool getRemoteAddr(unsigned long& addr, int& iPort) = 0;

	//virtual void SetRecvBuffMaxLen(int iMaxLen) = 0; // 设置接收缓冲的最大大小
	//virtual void SetSendBuffMaxLen(int iMaxLen) = 0; // 设置发送缓冲最大大小 
	//virtual DWORD GetTotalSendBytes() = 0;
	//virtual DWORD GetTotalRecvBytes() = 0;
	//virtual void SetOption(DWORD dwOption, DWORD dwValue) = 0; // 设置该socket的一些属性 
};



/*!
* \class ITCPClientHandler
*
* \brief
*
* \author duxunzhi
* \date 六月 2017
* 代表一个tcp链接的回调
*/
class ITCPClientHandler
{
public:
	//用户调用disconnect时回调函数
	virtual void  OnDisconnect() = 0;
	// 用户Post连接成功时，需要得到当前的TcpClient对象以发送数据
	virtual void  OnConnect(ITCPClient* pClient) = 0;
	// 返回读取的数据大小
	virtual int  OnRead(const void* pBuff, unsigned int nSize) = 0;
};

/*!
* \class IAccpetorHandler
*
* \brief
*
* \author duxunzhi
* \date 六月 2017
* 代表一个tcp链接的回调
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
* \date 六月 2017
* 服务器实例化接口
*/
class INetService
{
	
public:
	//
	virtual void Init() = 0;

	virtual void Destory() = 0;

	virtual void runService() = 0;

	//添加一个
	virtual void addAcceptService(const char* ip,int port ,IAccpetorHandler* acceptorhandler) = 0;

	//连接到一个目标服务器
	virtual bool postConnectService(const char* szAddr, int nPort, ITCPClientHandler* pHandler) = 0;
	


};


// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LIBNETENGINE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// LIBNETENGINE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef LIBNETENGINE_EXPORTS
#define LIBNETENGINE_API __declspec(dllexport)
#else
#define LIBNETENGINE_API __declspec(dllimport)
#endif

extern "C" LIBNETENGINE_API INetService*   GetNetEngine();


typedef INetService* (*PFUNC_GETNETENGINE)();