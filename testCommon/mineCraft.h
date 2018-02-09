/********************************************************************
filename: 	Minecraft.h
file path:	server\testCommon

version:	1
author:		ajohn
company:	supernano
date:		2017-06-20
*********************************************************************/
#ifndef __MINECRAFT_HEADER__
#define __MINECRAFT_HEADER__

#include "MC_TypeDef.h"

namespace MINE_CRAFT
{

class World;
class WorldSettings;
class WorldProvider;
class TextureAtlasRegister;
class RenderGlobal;
class GameSettings;
class RenderEntity;
class PlayerController;
class EntityPlayerSP;
class EntityLivingBase;
class EntityRenderable;
class RightArmRenderable;
class PlayerInteractionManager;
class gui_LayoutManager;
class gui_eventManager;


class MineCraft : public Singleton<MineCraft>, public ObjectAlloc
{
public:
	static void initialize();
	static void unInitialize();

	MineCraft();
	~MineCraft();

	void init();
	void tick(float dt);
	void runTick();
	void generateWorld();
	void saveChunks();
	i32 getSystemTime();

public:
	World*				m_pWorld;
	WorldSettings*		m_worldSettings;
	GameSettings*		m_gameSettings;
	WorldProvider*		m_worldProvider;
	String				m_worldName;

	float				m_tickTime;
	static const float	s_tickFPS;
	float				m_render_dt;
	int					m_logicSystemTime;
};

}

#endif
