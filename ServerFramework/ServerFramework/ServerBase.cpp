#include "ServerBase.h"

//--from windows
#include <iostream>
#include <windows.h>
using namespace std; // For strlen and memcpy.

CServerBase::CServerBase()
{
	m_pNetService = NULL;
}


CServerBase::~CServerBase()
{

}
bool CServerBase::Init()
{
	printf("before CServerBase");
	m_bStop = true;
	HMODULE hdll;

	hdll = LoadLibrary("libNetEngine.dll");//加载动态链接库MyDll.dll文件；

	if (hdll == NULL)
	{
		FreeLibrary(hdll);
		return 0;
	}

	PFUNC_GETNETENGINE	pfunc;

	pfunc = (PFUNC_GETNETENGINE)GetProcAddress(hdll, "GetNetEngine");
	printf("before pfunc");
	if (pfunc == NULL)
	{
		FreeLibrary(hdll);
		return 0;
	}


	m_pNetService = pfunc();


	printf("before OnINit");
	OnInit();

	return true;



}

void CServerBase::Destroy()
{
	SAFE_DELETE(m_pNetService)

}


bool CServerBase::Start()
{

	if (!OnBeforeStart())
	{

		return false;
	}


	if (!m_pNetService)
	{
		return false;
	}

	m_pNetService->Init();
	



	if (!OnAfterStart())
	{
		return false;
	}



	return true;

}

void CServerBase::Stop()
{

}

void CServerBase::Run()
{

	m_bStop = false;

	m_pNetService->runService();

	while (!m_bStop)
	{
		processConnect();
		Sleep(100);

	}

	


}


void CServerBase::addConnection(CTCPSession* pSession)
{
	m_queConnection.push_back(*pSession);
}

void CServerBase::addDisconnection(CTCPSession* pSession)
{

}

bool CServerBase::processConnect()
{
	vector<CTCPSession>::iterator iter = m_queConnection.begin();

	for (; iter != m_queConnection.end(); ++iter)
	{
		(*iter).OnSessionConnect();
	}

	return true;
}
