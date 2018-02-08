
/*!
 * \file NetServer.h
 *
 * \author duxunzhi
 * \date ���� 2017
 *
 * ����������ļ̳�ʵ��
 * ʹ��boost�Ļ��Ʒ��ʵ�֣������Լ�ʵ��IOCP����LINUXepoll�������
 *
 */


#pragma once
#include "NetServiceInterface.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <vector>
using boost::asio::ip::tcp;
using namespace std;


#include "Listener.h"




/*!
 * \class classname
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: ʹ��boost����ʵ�ֵķ�����ʵ��ʵ�֡�
 *       ���������������������ܺ��Լ�������������
 *
 * \note 
 *
 * \author duxunzhi
 *
 * \version 1.0
 *
 * \date ���� 2017
 *
 * Contact: duxunzhi@supernano.com
 *
 */


class CNetServer :
	public INetService
{
public:
	CNetServer();
	~CNetServer();

	 void Init() override;

	 void Destory() override;


	 void addAcceptService(const char* ip, int port, IAccpetorHandler* acceptorhandler) override;
	 bool postConnectService(const char* szAddr, int nPort, ITCPClientHandler* pHandler) override;
	 
	 void handle_accept(const boost::system::error_code& error);

	 void runService() override;

	 


///////////////////////////////////////
	 
public:
	//CNetServer(boost::asio::io_service& io_service)
	//	: io_service_(io_service),
	//	acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
	//{
	//	//start_accept();
	//}


private:
	
	boost::asio::io_service io_service_;

	//�������ü�����ָ��
	vector<share_listener_ptr>  m_vecListener;


	tcp::acceptor* acceptor_;
private:

};

