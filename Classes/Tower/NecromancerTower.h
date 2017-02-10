#ifndef _NECROMANCER_TOWER_H_
#define _NECROMANCER_TOWER_H_

#include "cocos2d.h"
#include "Tower/BaseMageTower.h"
#include "Soldier/DeathKnight.h"

USING_NS_CC;

class NecromancerTower: public BaseMageTower
{
public:
	bool init();
	CREATE_FUNC(NecromancerTower);
	Bullet* MageTowerBullet();
	void Attack(float dt);
	void setRallyPoint(Point location);
private:
	DeathKnight* deathKnight;
	void showUpdateMenu();
	void cureSoldiers(float dt);
	Sprite* glow;
};

#endif