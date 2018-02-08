#include "NetPlayer.h"
#include "define.h"
#include "IDgenerator.h"

#include "protobuf/ClientAndGame.pb.h"
#include <google/protobuf/message_lite.h>
#include <MessageDefine.h>
#include "NetPlayerManager.h"
#include  "RoomManager.h"
#include "Minecraft.h"


CNetPlayer::CNetPlayer(CClientSession* session)
{
	m_pSession = session;

	m_ipID = CIDgenerator::getInstance()->getNewestID(CIDgenerator::ID_TYPE_PLAYER);

	m_pRoom = nullptr;


	//每一个player都要一个消息解析????
	m_net_analyser = new  CNetAnalyser();
	m_netanalyser_init_param.classself = this;
	m_netanalyser_init_param.pfunc_on_prase_response_playerinfo = onPraseResponsePlayerinfo;
	m_netanalyser_init_param.pfunc_on_praserequestroomid = onPraseRequestRoomid;
	m_netanalyser_init_param.pfunc_on_prase_response_roomid = onPraseResponseRoomid;
	m_netanalyser_init_param.pfunc_on_prase_request_seed = onPraseRequestSeed;
	

	m_net_analyser->Init(m_netanalyser_init_param);
	
}

CNetPlayer::~CNetPlayer()
{
	m_pSession = nullptr;
}

void CNetPlayer::sendData(const char*  data, int len)
{
	if (m_pSession == nullptr)
		return;


	m_pSession->SendData(const_cast<char*>(data), len);
}



void CNetPlayer::responsePlayerID()
{
	tutorial::S2CPlayerInfo  request;
	request.set_playerid(m_ipID);

	clearSendBuf();
	request.SerializeToArray(sendbuf, SEND_BUF_LEN);

	tutorial::ContainerMessage container = CNetAnalyser::wrapMessageToContainer(MESSAGE_RESEPONSE_PLAYER_INFO, sendbuf, SEND_BUF_LEN);

	std::string  strContainersMsg;
	container.SerializeToString(&strContainersMsg);
	sendData(strContainersMsg.c_str(), strContainersMsg.length());
}





void CNetPlayer::onPraseResponsePlayerinfo(int playerid,void* self)
{
	printf("CNetAnalyser::onPraseResponsePlayerinfo,playerid [%d]\n", playerid);
}

void CNetPlayer::onPraseRequestRoomid(int playerid, void* self)
{
	printf("CNetAnalyser::onPraseRequestRoomid,playerid [%d]\n", playerid);

	int hostid = INVALID_ID;
	int roomid = INVALID_ID;

	CNetPlayer* player = CNetPlayerManager::getInstance()->getPlayerByPID(playerid);
	//验证playerid
	if ((playerid != ((CNetPlayer*)self)->m_ipID) || (player == nullptr))
	{
		printf("wrong game id\n");
		return;
	}

	//
	if (player->getRoom()== nullptr)
	{
		//创建roomid
		CRoom* room = CRoomManager::getInstance()->createRoom();
		if ((room == nullptr))
		{
			printf("wrong room id\n");
			return;
		}
		room->sethostID(playerid);
		player->setRoom(room);
		hostid = playerid;
		roomid = room->getroomID();

		CRoomManager::getInstance()->addRoom(room);
	}
	else
	{
		if (!CRoomManager::getInstance()->getRoomByID(player->getRoom()->getroomID()))
		{
			printf("wrong room id\n");
			return;
		}

		hostid = player->getRoom()->gethostID();
	}

	if (hostid==INVALID_ID||roomid == INVALID_ID)
	{
		printf("wrong room id or host id\n");
		return;
	}

	//返回
	tutorial::S2CResponseRoomInfo  response;
	response.set_hostid(playerid);
	response.set_roomid(roomid);

	((CNetPlayer*)self)->clearSendBuf();
	response.SerializeToArray(((CNetPlayer*)self)->sendbuf, SEND_BUF_LEN);

	tutorial::ContainerMessage container = CNetAnalyser::wrapMessageToContainer(MESSAGE_RESEPONSE_ROOM_ID, ((CNetPlayer*)self)->sendbuf, SEND_BUF_LEN);

	std::string  strContainersMsg;
	container.SerializeToString(&strContainersMsg);
	((CNetPlayer*)self)->sendData(strContainersMsg.c_str(), strContainersMsg.length());


}

void CNetPlayer::onPraseResponseRoomid(int roomid, int hostid, void* self)
{
	printf("CNetAnalyser::onPraseResponseRoomid,roomid [%d]\n", roomid);
}

void CNetPlayer::onPraseRequestSeed(int playerid, int roomid, void* self)
{
	printf("CNetAnalyser::onPraseRequestSeed,playerid [%d],roomid [%d]\n", playerid, roomid);

	CNetPlayer* player = CNetPlayerManager::getInstance()->getPlayerByPID(playerid);
	//验证playerid
	if ((playerid != ((CNetPlayer*)self)->m_ipID) || (player == nullptr))
	{
		printf("wrong game id\n");
		return;
	}

	CRoom* room = CRoomManager::getInstance()->getRoomByID(roomid);
	assert(room != nullptr);


	//返回
	tutorial::S2CResponseSeedInfo  response;
	i64 seed = MINE_CRAFT::MineCraft::Instance()->getSeed();
	response.set_seedid(seed);

	printf("seed is [%lld]\n",seed);
	
	((CNetPlayer*)self)->clearSendBuf();
	response.SerializeToArray(((CNetPlayer*)self)->sendbuf, SEND_BUF_LEN);

	tutorial::ContainerMessage container = CNetAnalyser::wrapMessageToContainer(MESSAGE_RESEPONSE_SEED, ((CNetPlayer*)self)->sendbuf, SEND_BUF_LEN);

	std::string  strContainersMsg;
	container.SerializeToString(&strContainersMsg);
	((CNetPlayer*)self)->sendData(strContainersMsg.c_str(), strContainersMsg.length());
	
	
}
