/*!
* \file ServerBase.h
*
* \author duxunzhi
* \date ���� 2017
*
*  ���������࣬���з��������Ӵ˷���������ϼ̳С�
*  ��������gate��lobby��game����������
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

	//��ʼ��������
	virtual bool Init();
	virtual void Destroy();

	//����������
	virtual bool Start();
	virtual void Stop();

	//����������
	virtual void Run();


	
	//������̳У���������������
	// ��ʼ��ʱ�����Լ����Լ������Ĳ���
	//����������õĵط���
	virtual bool OnInit() { return true; }
	// ������iocp ����֮ǰ,��Ӷ���Ĳ���
	virtual bool OnBeforeStart() { return true; }
	// ������iocp ����֮����Ӷ������
	virtual bool OnAfterStart() { return true; }
	// ������ֹͣ��ʱ����ã������ͷ���Դ
	virtual void OnStop() {}

	virtual void OnRun() {}



	//�����������ӿ�
	INetService* GetNetSevice() { return m_pNetService; }


	void addConnection(CTCPSession* pSession);
	void addDisconnection(CTCPSession* pSession);


private:
	bool processConnect();


	INetService*  m_pNetService;


	vector<CTCPSession> m_queConnection; // �ȴ���������Ӷ���

	bool          m_bStop;
};

