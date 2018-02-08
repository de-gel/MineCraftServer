#pragma once

/*!
 * \file GamesServer.h
 * \date 2017/06/27 14:12
 *
 * \author duxunzhi
 * Contact: duxunzhi@supernano.com
 *
 *  
 *
 * TODO: 游戏server服务器
 *
 * \note
*/


#include "../../ServerFramework/ServerFramework/ServerBase.h"

#include "RoomManager.h"

#include "NetPlayerManager.h"


#include "../../Protos/Protos/NetAnalyser.h"

#include "mineCraft.h"
#include "Object/Root.h"

using namespace MINE_CRAFT;


class CRoomManager;
class CNetPlayerManager;


class CGamesServer :
	public CServerBase
{
public:
	CGamesServer();
	~CGamesServer();


	////callback//////////////////////////////////////////
	 bool OnInit() override;

	 bool OnBeforeStart() override;

	 bool OnAfterStart() override;

	 void OnStop() override;

	 void OnRun() override;
 
	 virtual bool Init() override;

	 
	 

	 CRoomManager* getRoomManager() const { return m_roomManager; }
	 void setRoomManager(CRoomManager* val) { m_roomManager = val; }

	 CNetPlayerManager* getNetPlayerManager() const { return m_netPlayerManager; }
	 void setNetPlayerManager(CNetPlayerManager* val) { m_netPlayerManager = val; }
private:
	
	//初始化mc世界
	void initMCWorld();


	//房间管理
	CRoomManager* m_roomManager;

	//玩家管理
	CNetPlayerManager* m_netPlayerManager;

	//我的世界
	MineCraft*    m_mcWorld;

};

