#ifndef _MECHS_TOWER_H_
#define _MECHS_TOWER_H_

#include "cocos2d.h"
#include "Tower/BaseBarracksTower.h"
#include "Soldier/Mecha.h"
USING_NS_CC;

class MechsTower: public BaseBarracksTower
{
public:

	bool init();
    CREATE_FUNC(MechsTower);
	void setRallyPoint(Point location);
private:
	void initMech();
	Mecha* mecha;
	void showUpdateMenu();
	void playReadySound();
	void sellTower();
};


#endif