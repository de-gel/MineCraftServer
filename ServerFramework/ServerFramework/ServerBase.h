/*!
* \file ServerBase.h
*
* \author duxunzhi
* \date 六月 2017
*
*  服务器基类，所有服务器都从此服务器框架上继承。
*  可以满足gate，lobby，game等派生需求。
*/

#pragma once

#include "TCPSession.h"

#include <vector>
using namespace std;

class CServerBase
{
public:
	CServerBase();
	virtual ~CServerBase();

	//初始化和销毁
	virtual bool Init();
	virtual void Destroy();

	//服务器开关
	virtual bool Start();
	virtual void Stop();

	//服务器运行
	virtual void Run();


	
	//由子类继承，可以做其他事情
	// 初始化时，可以加入自己想做的操作
	//基类决定调用的地方。
	virtual bool OnInit() { return true; }
	// 在启动iocp 服务之前,添加额外的操作
	virtual bool OnBeforeStart() { return true; }
	// 在启动iocp 服务之后，添加额外操作
	virtual bool OnAfterStart() { return true; }
	// 服务器停止的时候调用，用来释放资源
	virtual void OnStop() {}

	virtual void OnRun() {}



	//返回网络服务接口
	INetService* GetNetSevice() { return m_pNetService; }


	void addConnection(CTCPSession* pSession);
	void addDisconnection(CTCPSession* pSession);


private:
	bool processConnect();


	INetService*  m_pNetService;


	vector<CTCPSession> m_queConnection; // 等待处理的连接队列

	bool          m_bStop;
};

