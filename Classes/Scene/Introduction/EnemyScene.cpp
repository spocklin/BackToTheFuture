#include "EnemyScene.h"
#include "Data/SoundManager.h"

USING_NS_CC;

Scene* Enemy::createScene(){
    auto scene = Scene::create();
    auto enemyInfLayer = Enemy::create();
    scene->addChild(enemyInfLayer);
    return scene;
}

bool Enemy::init(){
    if ( !Layer::init() ){
        return false;
    }
	//���������¼����Ͳ���ִ�к���
	auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->setSwallowTouches(true);//�ص�����
	touchListener->onTouchBegan = CC_CALLBACK_2(Enemy::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Enemy::onTouchEnded, this);
	

    //ȡ����Ļ��С
	visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ֻ�������ԭ�������
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// �ڶ����ˣ���ʾ�鱾ͼ��-ɾ���ײ㣬ֱ����ʾ��Ƥ
	for(int i = 0;i<4;i++){
		for(int j =0;j<5;j++){
			auto sprite = Sprite::createWithSpriteFrameName("encyclopedia_bgTile.png");
			sprite->setPosition(Point(i*310,j*150));
			sprite->setAnchorPoint(Point(0,0));
			addChild(sprite);
		}
	}

	// ����-��-�ұ�
    auto sprite1 = Sprite::createWithSpriteFrameName("encyclopedia_book_pg.png");
    sprite1->setPosition(Vec2(visibleSize.width * 3/4 + origin.x, visibleSize.height/2 + origin.y));

	//��-���
    auto sprite2 = Sprite::createWithSpriteFrameName("encyclopedia_book_pg.png");
    sprite2->setPosition(Vec2(visibleSize.width/4 + origin.x, visibleSize.height/2 + origin.y));

	//��ת
	sprite2->setFlippedX(true);
    sprite2->setRotation(360);

	// ���ͼƬ���鵽�����s
    this->addChild(sprite1, 1);
	this->addChild(sprite2, 1);

	//�رղ��
	auto sprite3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"),Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png"));
	sprite3->setPosition(Vec2(visibleSize.width - sprite3->getContentSize().width * 3 / 2  + origin.x, 
								visibleSize.height + origin.y - sprite3->getContentSize().height / 2));

	//���
	sprite3->setCallback([&](Ref *pSender){
		SoundManager::playClickEffect();
		Director::getInstance()->popScene();		
	});
	auto menuclose = Menu::create(sprite3,NULL);
	menuclose->setPosition(Vec2::ZERO);
	this->addChild(menuclose,2);
	creepFrame = Sprite::createWithSpriteFrameName("encyclopedia_creep_thumbs_frame_0002.png");  

    creepFrame->setPosition(Point(visibleSize.width * 0.17, visibleSize.height * 0.75));
	this->addChild(creepFrame,3); 

	//�������ҷ�ҳ����
	auto spriteRight = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0003.png");
	auto spriteLeft = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0003.png");
	//��Чͼ��
	auto spriteRightNull = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0001.png");
	auto spriteLeftNull = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0001.png");
	//����С��ҳ
	auto spriteRightLittle = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0003.png");
	auto spriteLeftLittle = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_arrow_0003.png");

	spriteLeft->setFlippedX(true);
	spriteLeft->setRotation(360);
	spriteLeftNull->setFlippedX(true);
	spriteLeftNull->setRotation(360);
	spriteLeftLittle->setFlippedX(true);
	spriteLeftLittle->setRotation(360);

	//��Ч��Ĵָͼ��
	auto spriteCreepThumbNull = Sprite::createWithSpriteFrameName("encyclopedia_tower_thumbs_0121.png");

	//��ʼ��Ĵָͼ��48��
	for(int i = 0; i < 48; i ++)
	{
		std::string temp1 = "encyclopedia_creep_thumbs_02";
		std::string temp2 = "encyclopedia_creep_02";
		if(i < 9){
			temp1 = temp1 + '0';
			temp2 = temp2 + '0';
		}
		temp1 = temp1 + String::createWithFormat("%d",i+1)->getCString();
		temp2 = temp2 + String::createWithFormat("%d",i+1)->getCString();
		temp1 = temp1 + ".png";
		temp2 = temp2 + ".png";

		enemyDesc[i] = EnemyDesc::createEnemyDesc(temp1);

		enemyDesc[i]->setPosition(Point(visibleSize.width * (0.17 + (i % 4)*0.085), 
												visibleSize.height * (0.75 - ((i / 4) % 4) *0.15)));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), enemyDesc[i]);
		enemyDesc[i]->enemyThumbFileName = temp1;
		enemyDesc[i]->enemyDescFileName = temp2;
		//��ʼ���α�
		enemyDesc[i]->num = i;	
	}
	
	//�����˵�����λ��
	for(int i = 0 ; i < 3 ; i ++){
		ccmenuCreep[i] = Layer::create();
		ccmenuCreep[i]->setPosition(Vec2::ZERO);
		for(int j = 0 ; j < 16; j ++){
			ccmenuCreep[i]->addChild(enemyDesc[16 * i + j],2);
		}
		this->addChild(ccmenuCreep[i],2);
	}
	//��ʼ���˵��ɼ���
	ccmenuCreep[0]->setVisible(true);
	ccmenuCreep[1]->setVisible(false);
	ccmenuCreep[2]->setVisible(false);

	//��ʼ��˵����ͼ
	bigSprite = Sprite::createWithSpriteFrameName(enemyDesc[0]->enemyDescFileName);
	bigSprite->setPosition(Vec2(visibleSize.width * 0.7,visibleSize.height * 0.75));
	this->addChild(bigSprite,2);

	//�����ҳ & ����
	spriteLeftButton = MenuItemSprite::create(spriteLeft,spriteLeftLittle,spriteLeftNull,
		CC_CALLBACK_1(Enemy::lastPage,this));  
    auto ccmenuLeft = Menu::create(spriteLeftButton,NULL);  //ʵ������֮���˳���л�  
    spriteLeftButton->setPosition(Point(visibleSize.width * 0.2, visibleSize.height * 1 / 7));  
	ccmenuLeft->setPosition(Vec2::ZERO);
    this->addChild(ccmenuLeft,2); 
	spriteLeftButton->setEnabled(false);

	//����ҷ�ҳ & ����
	spriteRightButton = MenuItemSprite::create(spriteRight,spriteRightLittle,spriteRightNull,
		CC_CALLBACK_1(Enemy::nextPage,this));  
    auto ccmenuRight = Menu::create(spriteRightButton,NULL);  //ʵ������֮���˳���л�  
    spriteRightButton->setPosition(Point(visibleSize.width*0.4,visibleSize.height * 1 / 7));  
	ccmenuRight->setPosition(Vec2::ZERO);
    this->addChild(ccmenuRight,2); 

	//��-����
    auto labelTitle = Label::createWithTTF("ENEMIES", "Marker Felt.ttf", 24);
    labelTitle->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 6 / 7));
	labelTitle->setColor(Color3B(0,0,0));
    this->addChild(labelTitle, 2);

	//��-ҳ��
	enemyId = 0;
	labelPage = Label::createWithTTF(String::createWithFormat("%d",enemyId + 1)->getCString(), "Marker Felt.ttf", 24);
    // ����label����Ļ�е���ʾλ��
    labelPage->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 1 / 7));
	labelPage->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelPage, 2);

	////////////////////////////////////////////////
	///һ���label-��ʼ
	///////////////////////////////////////////////
	//��������
	labelName = Label::createWithTTF("", "Marker Felt.ttf", 24);
    // ����label����Ļ�е���ʾλ��
    labelName->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.60));
	labelName->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelName, 2);

	//����Ѫֵ
	labelBloodValue = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelBloodValue->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.50));
	labelBloodValue->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelBloodValue, 2);

	//���﹥����
	labelAttackValue = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelAttackValue->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.45));
	labelAttackValue->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelAttackValue, 2);

	//�������������
	labelDefenseValue = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelDefenseValue->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.40));
	labelDefenseValue->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelDefenseValue, 2);

	//����ħ��������
	labelMagicDefenseValue = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelMagicDefenseValue->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.30));
	labelMagicDefenseValue->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelMagicDefenseValue, 2);

	//�����ƶ��ٶ�
	labelMovementSpeed = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelMovementSpeed->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.25));
	labelMovementSpeed->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelMovementSpeed, 2);

	//������������
	labelLifeNumber= Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelLifeNumber->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.20));
	labelLifeNumber->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelLifeNumber, 2);
	
	//�������Բ���˵��
    labelNotice = Label::createWithTTF("*", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelNotice->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.15));
	labelNotice->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelNotice, 2);

	/*****************************
	**��ʾ�������ģ��-��ʼ
	******************************/
	
	//��ȡxml�ĵ�,����ValueVector��
	ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("creep.xml");
	int i = 0;
	for( auto& e : txt_vec){
		auto txt_map = txt_vec.at(i).asValueMap();//����ֵת����Map��ʽ������txt_map��
		int id_int = txt_map.at("id").asInt();//��ȡid
		if(id_int == i){
			//auto label_str = txt_map.at("info").asString();//��ȡinfo��ֵ
			enemyDesc[i]->enemyName = txt_map.at("EnemyName").asString();
			enemyDesc[i]->bloodValue = txt_map.at("BloodValue").asString();
			enemyDesc[i]->attackValue = txt_map.at("AttackValue").asString();
			enemyDesc[i]->defenseValue = txt_map.at("DefenseValue").asString();
			enemyDesc[i]->magicDefenseValue = txt_map.at("MagicDefenseValue").asString();
			enemyDesc[i]->movementSpeed = txt_map.at("MovementSpeed").asString();
			enemyDesc[i]->lifeNumber = txt_map.at("LifeNumber").asString();
			enemyDesc[i]->note = txt_map.at("Note").asString();
		}else if(id_int == 100){
			labelBloodValue->setString(txt_map.at("BloodValue").asString());
			labelAttackValue->setString(txt_map.at("AttackValue").asString());
			labelDefenseValue->setString(txt_map.at("DefenseValue").asString());
			labelMagicDefenseValue->setString(txt_map.at("MagicDefenseValue").asString());
			labelMovementSpeed->setString(txt_map.at("MovementSpeed").asString());
			labelLifeNumber->setString(txt_map.at("LifeNumber").asString());
		}
		i ++; //��һ������	
	}

	/*****************************
	**��ʾ�������ģ��-����
	*****************************/

	//����������ֵ
	//����Ѫֵ1
	labelBloodValue1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelBloodValue1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.50));
	labelBloodValue1->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelBloodValue1, 2);

	//���﹥����
	labelAttackValue1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelAttackValue1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.45));
	labelAttackValue1->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelAttackValue1, 2);

	//�������������
	labelDefenseValue1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelDefenseValue1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.40));
	labelDefenseValue1->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelDefenseValue1, 2);

	//����ħ��������
	labelMagicDefenseValue1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelMagicDefenseValue1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.30));
	labelMagicDefenseValue1->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelMagicDefenseValue1, 2);

	//�����ƶ��ٶ�
	labelMovementSpeed1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelMovementSpeed1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.25));
	labelMovementSpeed1->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelMovementSpeed1, 2);

	//������������
	labelLifeNumber1= Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelLifeNumber1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.20));
	labelLifeNumber1->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelLifeNumber1, 2);

	//////////////////////////////////
	//һ���label-����
	//////////////////////////////////

	bigSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(enemyDesc[0]->enemyDescFileName));
	labelName->setString(enemyDesc[0]->enemyName);
		//�ߴ�����
	labelBloodValue1->setString(enemyDesc[0]->bloodValue);
	labelAttackValue1->setString(enemyDesc[0]->attackValue);
	labelDefenseValue1->setString(enemyDesc[0]->defenseValue);
	labelMagicDefenseValue1->setString(enemyDesc[0]->magicDefenseValue);
	labelMovementSpeed1->setString(enemyDesc[0]->movementSpeed);
	labelLifeNumber1->setString(enemyDesc[0]->lifeNumber);
	labelNotice->setString(enemyDesc[0]->note);

	creepFrame->setPosition(enemyDesc[0]->getPosition());
	creepFrame->setVisible(true);
	return true;
}

//��ҳ
void Enemy::lastPage(Ref* pSender){
	SoundManager::playClickEffect();
	enemyId --;
	if(enemyId == 0){
		spriteLeftButton->setEnabled(false);
	}else{
		spriteLeftButton->setEnabled(true);
		spriteRightButton->setEnabled(true);
	}
	//��ҳ��
	labelPage->setString(String::createWithFormat("%d",enemyId + 1)->getCString());

	ccmenuCreep[enemyId]->setVisible(true);
	ccmenuCreep[enemyId + 1]->setVisible(false);
	creepFrame->setVisible(false);
	return;
}

//�ҷ�ҳ
void Enemy::nextPage(Ref* pSender){
	SoundManager::playClickEffect();
	enemyId ++;
	if(enemyId == 2){
		spriteRightButton->setEnabled(false);
		spriteLeftButton->setEnabled(true);
	}else{
		spriteLeftButton->setEnabled(true);
	}
	//��ҳ��
	labelPage->setString(String::createWithFormat("%d",enemyId + 1)->getCString());

	ccmenuCreep[enemyId]->setVisible(true);
	ccmenuCreep[enemyId - 1]->setVisible(false);

	creepFrame->setVisible(false);
	return;
}
//�������� 
bool Enemy::onTouchBegan(Touch* touch, Event* event){

	auto target = static_cast<EnemyDesc*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->enemyDescPic->getContentSize();
	Rect rect = Rect(0-size.width/2, 0-size.height/2, size.width, size.height);

	if (rect.containsPoint(locationInNode) && target->getParent()->isVisible()){
		SoundManager::playClickEffect();
		bigSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(target->enemyDescFileName));
		labelName->setString(target->enemyName);
		//�ߴ�����
		labelBloodValue1->setString(target->bloodValue);
		labelAttackValue1->setString(target->attackValue);
		labelDefenseValue1->setString(target->defenseValue);
		labelMagicDefenseValue1->setString(target->magicDefenseValue);
		labelMovementSpeed1->setString(target->movementSpeed);
		labelLifeNumber1->setString(target->lifeNumber);
		labelNotice->setString(target->note);

		moveFrame=MoveTo::create(0.1f,target->getPosition());//����ͼ���λ��ʱ�䣬λ��Ŀ���ַ
		creepFrame->runAction(moveFrame);
		creepFrame->setVisible(true);

		return true;
	}
	return false;
}

void Enemy::onTouchEnded(Touch* touch, Event* event){
	return;
}