#include "mineCraft.h"
#include "Object/Root.h"

using namespace MINE_CRAFT;

void main()
{
	//LORD::ROOT
	LordNew(LORD::Root);

	//为网络做一种逻辑最简单优化
	LORD::Root::Instance()->initialize_mini();

	//初始化一些必要组件
	MineCraft::initialize();

	//新建一个世界
	MineCraft* mc = LordNew MineCraft();
	
	//初始化
	mc->init();
	

	printf("now generateWorld all mc\n");
	//生成世界
	mc->generateWorld();


	printf("now saveChunks all mc\n");
	//存储chunk信息
	mc->saveChunks();
		
////////////////////////////////////////////////////
	while (true)
	{
		mc->tick(1000/60);
	}


	printf("now delete all mc\n");
	//删除组件
	LordSafeDelete(mc);
	MineCraft::unInitialize();

	LordDelete(LORD::Root::Instance());
}