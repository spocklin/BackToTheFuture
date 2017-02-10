#include "SimplePanleLayer.h"
#include "Data/GameManager.h"
#include "Sprite/TowerIcon/BaseBuildIcon.h"

USING_NS_CC;

bool SimplePanleLayer::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
	isBuilt = false;
	planesprite = Sprite::createWithSpriteFrameName("gui_ring.png");
	planesprite->setPosition(Point(0, 0));
	planesprite->setScale(0.5f);
	addChild(planesprite);

	sellIcon = SellIcon::create();
	sellIcon->setPosition(Point(0,-planesprite->getContentSize().height/2));
	sellIcon->setVisible(false);
	sellIcon->setTag(2);
	addChild(sellIcon);
	return true;
}

void SimplePanleLayer::inAnimation()
{
	SoundManager::playTowerMenu();
	planesprite->runAction(Sequence::create(ScaleTo::create(0.1f,1.0f,1.0f),
		CallFuncN::create(CC_CALLBACK_0(SimplePanleLayer::addIcons,this)),
		NULL));	
}

void SimplePanleLayer::addIcons()
{	
	thisLvlCircle = Circle::create();

	thisLvlCircle->setScale(tower->getScope()/160.0f);
	addChild(thisLvlCircle,-1);
	sellIcon->setVisible(true);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SimplePanleLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SimplePanleLayer::onTouchEnded, this);
 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sellIcon);
}

bool SimplePanleLayer::onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<BaseBuildIcon*>(event->getCurrentTarget());
    Point locationInNode = target->convertTouchToNodeSpace(touch);
    Size size = target->baseIcon->getContentSize();
	Rect rect = Rect(0-size.width/2, 0-size.height/2, size.width, size.height);
    if (rect.containsPoint(locationInNode))
    {
		if(target->getIsSelected())//����Ѿ�ѡ�У��ڶ��ΰ��£�
		{
			if(target->getIsAble())//���Ǯ����
			{
				SoundManager::playTowerSell();
				GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY+ (tower->getBuildMoney()/2);
				tower->sellTower();
				this->setVisible(false);
				isBuilt = true;
			}
		}else{//��һ�ΰ���
			target->setSelected();//����Ϊѡ��״̬
		}
        return true;
    }
    return false;
}

void SimplePanleLayer::onTouchEnded(Touch* touch, Event* event)
{
	if(isBuilt)
	{
		removeFromParent();
	}
}
