#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Bullet/Bullet.h"
#include "cocos2d.h"
#include "Monster/BaseMonster.h"
#include "Tower/BaseTower.h"
#include "Layer/TouchLayer.h"

USING_NS_CC;

class GameManager
{
public:
    void CreateGameManager(int slot);

    Vector<BaseMonster*> monsterVector;
    //Vector<Bullet*> bulletVector;
    //Vector<BaseTower*> towerVector;
    
	static GameManager* getInstance();


	//ĳ�浵�Ƿ��Ѿ��½���true��ʾ�½���false��ʾδ�½�
	char SLOTX_ISEXIT[20];

    //ĳ�ؿ��Ƿ����,0��ʾδ��ɣ�1��ʾ���
	char LEVELX_ISDOWN[20];

	//ĳ�ؿ��õ���������Ŀ
	char LEVELX_STARNUM[20];
	//ʣ��������Ŀ
	char SLOTX_STARLEFT[20];
	//ĳ�浵ͨ����
	char SLOTX_DOWNCOUNT[20];

	//ĳ�浵���¿�����
	char LEVELX_NEWDOWN[20];

	//��������
	char SLOTX_STAR[20];

	//�̵�
	char SLOTX_SHOP[20];

	//��ʯ
	char SLOTX_GEM[20];
	int SLOTNUM;
	//ʵʱ��Ǯ
	int MONEY;
	//ʵʱ����
	int LIFE;
	
	int LEVEL;

	void setInstance(int tag);
	static void eraseAll();
private:
	static GameManager * instance;
};
#endif /* defined(__thiefTD__GameManager__) */
