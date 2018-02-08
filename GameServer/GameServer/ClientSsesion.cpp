#include "ClientSsesion.h"

#include "RoomManager.h"
#include "NetPlayerManager.h"



#include "../../Protos/Protos/protobuf/ClientAndGame.pb.h"
#include <MessageDefine.h>
#include <Winsock2.h>

using namespace tutorial;


CClientSession::CClientSession(CServerBase* pServer) :CTCPSession(pServer)
{

}

CClientSession::~CClientSession()
{

}

void CClientSession::OnSessionConnect()
{
	
	unsigned long  address = 0;
	int port = 0;

	bool res = getLocalAddr(address, port);

	struct in_addr addr1, addr2;
	unsigned long l1, l2;
	l1 = address;
	
	memcpy(&addr1, &l1, 4);
	
	printf("%s\n", inet_ntoa(addr1)); //ע����һ������н��   
	printf("%s\n", inet_ntoa(addr1));
	

	if (res)
	{
		printf("local address is [%d],port is [%d]\n", address, port);

	}



	unsigned long  raddress = 0;
	int rport = 0;

	bool rres = getRemoteAddr(raddress, rport);

	l2 = raddress;
	memcpy(&addr2, &l2, 4);

	printf("%s\n", inet_ntoa(addr2));

	if (rres)
	{
		printf("remote address is [%d],port is [%d]\n", raddress, rport);

	}

	player = createPlayer();
	player->responsePlayerID();



	//std::string str = "welcome to minicraft";
	//player->sendData(str.c_str(), str.length());


	


	//player->responsePlayerID(&request);


	//if (room->getIhostID() == INVALID_ID)
	//{
	//	//�����µ�session
	//	client_session = createClientSession();
	//	//�����µ�player
	//	

	//	//��������
	//	room->setIhostID(player->getID());
	//	room->setIroomID(CIDgenerator::getInstance()->getNewestID(CIDgenerator::ID_TYPE_ROOM));
	//	room->addPlayer(player);


	//	player->setRoom(room);


	//	

	//}
	//else if (!room->IsFull())//��iD�����Ƿ�player�����ڴ˷��䣬���ߴ˷����Ƿ��Ѿ�����,��ʱûʲô�ã������Ժ���ܻ�����������
	//{
	//	//�����µ�session
	//	client_session = createClientSession();
	//	//�����µ�player
	//	CNetPlayer* player = createPlayer(client_session);

	//	//����û�����ұ��˲��ڷ���
	//	if (!room->hasPlayer(player))
	//	{
	//		room->addPlayer(player);
	//	}
	//	else
	//	{
	//		//����Ҫ����Ķ�������
	//	}
	//}
	//else //��������
	//{
	//	//�����·����߼�
	//}


	//room->broadcastToRoom("CClientAcceptorHandler,this is message from room\n");


}

void CClientSession::OnSessionDisconnect()
{
	throw std::logic_error("The method or operation is not implemented.");
}


CNetPlayer* CClientSession::createPlayer()
{
	CNetPlayer* player = CNetPlayerManager::getInstance()->createPlayer(this);
	CNetPlayerManager::getInstance()->addPlayer(player);
	return player;
}

int CClientSession::OnSessionRead(const char* buf, unsigned short size)
{
	if (0 == strcmp(buf, "welcome to minicraft"))
	{
		printf("client get message\n");
	}
	else
	{
		std::string  strcontainer(buf);


		//������container
		tutorial::ContainerMessage container;
		container.ParseFromString(strcontainer);

		player->getNet_analyser()->praseContainerPakage(&container);



		//switch(container.msgid())
		//{1`
		//case MESSAGE_RESEPONSE_PLAYER_INFO:

		//	//std::string  strMsg(container.buf());

		//	

		//	break;
		//default:
		//	break;
		//}


	}

	return size;
}
