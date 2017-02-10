#ifndef __Enemy_SCENE_H__
#define __Enemy_SCENE_H__

#include "cocos2d.h"
#include "Scene/Introduction/EnemyDesc.h"
USING_NS_CC;

class Enemy : public cocos2d::Layer
{
	public:
		static cocos2d::Scene* createScene();
		virtual bool init();

		//��ҳ
		void lastPage(Ref* pSender);
		void nextPage(Ref* pSender);

		virtual bool onTouchBegan(Touch* touch, Event* event);
		virtual void onTouchEnded(Touch* touch, Event* event);

		CREATE_FUNC(Enemy);
	private:
		int enemyId;
		MenuItemSprite* spriteLeftButton;
		MenuItemSprite* spriteRightButton;
		Layer* ccmenuCreep[3];

		Label* labelPage;

		Label* labelName;
		//��������
		Label* labelBloodValue;
		Label* labelAttackValue;
		Label* labelDefenseValue;

		Label* labelMagicDefenseValue;
		Label* labelMovementSpeed;
		Label* labelLifeNumber;
		
		Label* labelNotice;

		//����ֵ
		Label* labelBloodValue1;
		Label* labelAttackValue1;
		Label* labelDefenseValue1;

		Label* labelMagicDefenseValue1;
		Label* labelMovementSpeed1;
		Label* labelLifeNumber1;

		Label* labelNotice1;

		//�������
		Sprite* creepFrame;

		Size visibleSize;

		char enemyIdString[8];
		Sprite* bigSprite;

		MoveTo *moveFrame;
			
		EnemyDesc* enemyDesc[50];

};

#endif // __Enemy_SCENE_H__
