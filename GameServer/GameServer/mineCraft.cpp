#include "World/World.h"
#include "Minecraft.h"
#include "World/GameSettings.h"
#include "World/Chunk.h"
#include "World/Section.h"
#include "World/WorldSettings.h"
#include "World/WorldProvider.h"

#include "Block/BlockManager.h"
#include "WorldGenerator/BiomeGen.h"
#include "WorldGenerator/GenLayer.h"
#include "WorldGenerator/StructurePieces.h"
#include "WorldGenerator/ChunkProvider.h"
#include "WorldGenerator/WorldGenerator.h"
#include "Util/Facing.h"
#include "TileEntity/TileEntity.h"
#include "Entity/Attributes.h"
#include "Entity/DamageSource.h"
#include "Entity/Enchantment.h"
#include "Entity/EntityLivingBase.h"
#include "Item/Item.h"
#include "Item/Items.h"
#include "Item/Potion.h"
#include "Stats/StatList.h"
#include "Inventory/InventoryPlayer.h"
#include "Item/ItemStack.h"
#include "Block/Block.h"
#include "Block/BlockManager.h"
#include "Inventory/Container.h"
#include "Inventory/CraftingManager.h"
#include "Object/Root.h"


namespace MINE_CRAFT
{

	const float MineCraft::s_tickFPS = 1.f / 20.f;

	void MineCraft::initialize()
	{
		BiomeGenBase::initialize();
		StructureMineshaftPieces::initialize();
		StructureNetherBridgePieces::initialize();
		WorldGenDungeons::initialize();

		BlockManager::initialize();
		CraftingManager* pCrafting = LordNew CraftingManager();
		TileEntity::initialize();
		SharedMonsterAttributes::initialize();
		DamageSource::initialize();
		Enchantment::initialize();
		EnchantmentHelper::initialize();
		EntityLivingBase::initialize();
		ToolMaterial::initialize();
		ArmorMaterial::initialize();
		Potion::initialize();
		Item::initialize();
		PotionHelper::initialize();
		StatList::initialize();
		Facing::initialize();
	}

	void MineCraft::unInitialize()
	{
		StatList::unInitialize();
		Potion::unInitialize();
		ArmorMaterial::unInitialize();
		ToolMaterial::unInitialize();
		EntityLivingBase::unInitialize();
		DamageSource::unInitialize();
		SharedMonsterAttributes::unInitialize();
		EnchantmentHelper::unInitalize();
		Enchantment::unInitialize();
		WorldGenDungeons::uninitialize();
		StructureNetherBridgePieces::uninitialize();
		StructureMineshaftPieces::uninitialize();
		BiomeGenBase::uninitialize();
		Facing::unInitialize();
		Item::unInitialize();
		LordDelete(CraftingManager::Instance());
		BlockManager::unInitialize();
	}

	MineCraft::MineCraft()
		: m_pWorld(NULL)
		, m_worldSettings(NULL)
		, m_gameSettings(NULL)
		, m_worldProvider(NULL)
	{
		m_worldName = "newWorld1";
		m_logicSystemTime = getSystemTime();
	}

	MineCraft::~MineCraft()
	{
		// delete all the backgroud thread chunkProvide request.	
		Root::Instance()->enableStreamThread(false);
		LordSafeDelete(m_pWorld);
		LordSafeDelete(m_gameSettings);
		LordSafeDelete(m_worldSettings);
		LordSafeDelete(m_worldProvider);
	}

	i64 test_rand[] = {
		3315535095586843436LL,
		7811472220827660346LL,
		27977402478636135LL,
		-2961405825330349164LL,
		-9039153669293870600LL,
		6727893985866532711LL,
		-1777905325754646240LL,
		-3969516832809676251LL,
		-3378829271918789601LL,
		-2720273531442913371LL
	};

	Vector3i spwanPos[] = {
		Vector3i(153, 64, 219),
		Vector3i(-76, 64, 132),
		Vector3i(-24, 64, 256),
		Vector3i(215, 64, 264),
		Vector3i(335, 64, -101),
		Vector3i(-240, 64, 240),
		Vector3i(-475, 64, 60),
		Vector3i(224, 64, 248),
		Vector3i(289, 65, -67),
		Vector3i(-180, 64, 256)
	};

	int testIndex = 4;


	void MineCraft::init()
	{
		const i64 seed = test_rand[testIndex];
		m_worldSettings = LordNew WorldSettings(seed, GAME_TYPE_SURVIVAL, false, false, TERRAIN_TYPE_DEFAULT);
		m_gameSettings = LordNew GameSettings();
		m_worldProvider = WorldProvider::getProviderForDimension(0);
		m_pWorld = LordNew World(m_worldName, m_worldProvider, *m_worldSettings, m_gameSettings->getLoadChunksRange());
		// virtual function World::createChunkProvider must call obviously.
		m_pWorld->createChunkProvider(m_gameSettings->getLoadChunksRange());

		m_tickTime = 0.f;
		m_render_dt = 0.f;
	}

	void MineCraft::tick(float dt)
	{
		if (dt > 0.4f)
			dt = 0.4f;

		//Camera* mainCamera = SceneManager::Instance()->getMainCamera();
		//Vector3 pos = mainCamera->getPosition();
		//m_pWorld->m_pChunkProvider->setCentrol(int(Math::Floor(pos.x)) >> 4, int(Math::Floor(pos.z)) >> 4);
		m_pWorld->tick();
		//// m_entityRender->updateRenderer();

		m_tickTime += dt;
		//while (m_tickTime >= s_tickFPS)
		//{
		//	runTick();
		//	m_tickTime -= s_tickFPS;
		//}

		//// make sure debug mode has a stable frame rate.
		//m_render_dt = m_tickTime / s_tickFPS;
	}

	void MineCraft::runTick()
	{
		m_pWorld->setWorldTime(m_pWorld->getWorldTime() + 1); // accelerate the time...

		m_logicSystemTime = getSystemTime();
	}

	void MineCraft::generateWorld()
	{
		m_pWorld->setSpawnLocation(spwanPos[testIndex].x, spwanPos[testIndex].y, spwanPos[testIndex].z); // the params is from mc.java
		// m_pWorld->setSpawnLocation(0, 0, 0);

		bool var1 = true;
		bool var2 = true;
		bool var3 = true;
		bool var4 = true;
		int var5 = 0;

		i8 var6 = 0;
		LordLogInfo("Preparing start region for level %d", var6);

		Vector3i var8 = m_pWorld->getSpawnPoint();
		i64 var9 = Time::Instance()->getMillisecondsCPU();

		int loadWide;
		loadWide = 64 << (3 - m_gameSettings->renderDistance);
		loadWide = loadWide / 2;
		loadWide = 32;  // for speed in debug mode.  //modify by maxicheng 128->32

		for (int var11 = -loadWide; var11 <= loadWide; var11 += 16)
		{
			for (int var12 = -loadWide; var12 <= loadWide; var12 += 16)
			{
				i64 var13 = Time::Instance()->getMillisecondsCPU();

				if (var13 - var9 > 1000L)
				{
					int allCount = int(Math::Pow(float((loadWide / 16) * 2 + 1), 2.f));
					LordLogInfo("Preparing spawn area %d (%d/%d)", var5 * 100 / allCount, var5, allCount);
					var9 = var13;
				}

				++var5;
				m_pWorld->m_pChunkProvider->loadChunk((var8.x + var11) >> 4, (var8.z + var12) >> 4);
				// m_pWorld->m_pChunkProvider->updateSkyLight((var8.x + var11) >> 4, (var8.z + var12) >> 4);
				// m_pWorld->m_pChunkProvider->reBuildVisibility((var8.x + var11) >> 4, (var8.z + var12) >> 4);
			}
		}
	}


	i32 MineCraft::getSystemTime()
	{
		return Root::Instance()->getCurrentTime();
	}

	LORD::i64 MineCraft::getSeed()
	{
		return m_worldSettings->getSeed();
	}

	//modify by maxicheng
	void MineCraft::saveChunks()
	{
		ChunkProviderServer* pProvider = (ChunkProviderServer*)m_pWorld->m_pChunkProvider;

		String fileName = "Chunks_CPP_seed_";
		fileName += StringUtil::Format("%lld", test_rand[testIndex]);

		// create folder.
#if LORD_PLATFORM == LORD_PLATFORM_WINDOWS
		CreateDirectory(fileName.c_str(), NULL);

		Chunk** pChunkArr = pProvider->getChunksArr();
		int loadRange = pProvider->getChunksLoadRange();
		for (int i = 0; i < loadRange * loadRange; ++i)
		{
			Chunk* pChunk = pChunkArr[i];
			if (!pChunk)
				continue;

			int x = pChunk->m_posX;
			int z = pChunk->m_posZ;
			char filename[128];
			std::fstream fstream;
#if 1
			sprintf_s(filename, 128, "%s/chunk_%03d_%03d_blockId.cpp", fileName.c_str(), x, z);
			fstream.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
			LORD::DataStream* filePtrBlockId(LordNew LORD::FileStreamDataStream(&fstream, false));

			Section* pSection = NULL;
			for (int i = 0; i < 16; ++i)
			{
				pSection = pChunk->m_pSections[i];
				if (!pSection)
					continue;
				i8* pLBArray = pSection->getBlockLSBArray();
				String txt;
				for (int y = 0; y < 16; ++y)
				{
					for (int z = 0; z < 16; ++z)
					{
						txt += "section:" + StringUtil::ToString(i);
						txt += " y:" + StringUtil::ToString(y);
						txt += " z:" + StringUtil::ToString(z);
						txt += " x: ";
						for (int x = 0; x < 16; ++x)
						{
							int bkid = pSection->getBlockID(BlockPos(x, y, z));
							txt += StringUtil::ToString(bkid);
							if (x != 15)
								txt += ", ";
						}
						txt += "\r\n";

					}
				}
				filePtrBlockId->write(txt.c_str(), txt.length());
			}
			LordDelete filePtrBlockId;
			fstream.close();
#endif 

#if 1
			sprintf_s(filename, 128, "%s/chunk_%03d_%03d_metadata.cpp", fileName.c_str(), x, z);
			fstream.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
			LORD::DataStream* filePtrMetadata(LordNew LORD::FileStreamDataStream(&fstream, false));

			for (int i = 0; i < 16; ++i)
			{
				pSection = pChunk->m_pSections[i];
				if (!pSection)
					continue;
				i8* pLBArray = pSection->getBlockLSBArray();
				String txt;
				for (int y = 0; y < 16; ++y)
				{
					for (int z = 0; z < 16; ++z)
					{
						txt += "section:" + StringUtil::ToString(i);
						txt += " y:" + StringUtil::ToString(y);
						txt += " z:" + StringUtil::ToString(z);
						txt += " x: ";
						for (int x = 0; x < 16; ++x)
						{
							int bkid = pSection->getBlockMeta(BlockPos(x, y, z));
							txt += StringUtil::ToString(bkid);
							if (x != 15)
								txt += ", ";
						}
						txt += "\r\n";

					}
				}
				filePtrMetadata->write(txt.c_str(), txt.length());
			}
			LordDelete filePtrMetadata;
			fstream.close();

#endif 
		}
#endif
	}

}
