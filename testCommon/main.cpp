#include "mineCraft.h"
#include "Object/Root.h"

using namespace MINE_CRAFT;

void main()
{
	//LORD::ROOT
	LordNew(LORD::Root);

	//Ϊ������һ���߼�����Ż�
	LORD::Root::Instance()->initialize_mini();

	//��ʼ��һЩ��Ҫ���
	MineCraft::initialize();

	//�½�һ������
	MineCraft* mc = LordNew MineCraft();
	
	//��ʼ��
	mc->init();
	

	printf("now generateWorld all mc\n");
	//��������
	mc->generateWorld();


	printf("now saveChunks all mc\n");
	//�洢chunk��Ϣ
	mc->saveChunks();
		
////////////////////////////////////////////////////
	while (true)
	{
		mc->tick(1000/60);
	}


	printf("now delete all mc\n");
	//ɾ�����
	LordSafeDelete(mc);
	MineCraft::unInitialize();

	LordDelete(LORD::Root::Instance());
}