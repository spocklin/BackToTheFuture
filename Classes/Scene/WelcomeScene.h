#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(WelcomeScene);
	//���ɱ���ͼ
	void initBackGround();
	//����Logoͼ
	void initLogo();
	//����start��ť
	void initButton_start();
	//����&����Logo����
	void initLogoAnimation();
	//����&����start��������
	void initButton_startAnimation();
	//���ɼ�¼��menu
	void initMenu_save();
	//�˵��رհ�������
	void savemenuCloseCallback(cocos2d::Ref* pSender);
	//save_menu����
	void setSaveMenuInVisible();
	void setSaveMenuVisible();
	//����3����¼�浵
	//��Ա����
	void init_creditBtn();
	void initSoundButton();
	void init_creditBtn_startAnimation();
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
private:
	Size visibleSize;
	//��Ϸlogoͼλ��
	Point point_Logo;
	//logo
	Sprite *sprite_Logo;
	//��sprite�Զ���start����
	Sprite *button_Start;
	//credit
	Sprite *button_credit;
	//��¼menu
	Sprite *menu_Save;
	//menu_Save��ʼλ��
	Point point_Menu_Save;
	//menu�Ĺرհ���
	MenuItemSprite *button_Menu_Save_Close;
	//menu�Ĺرհ���λ��
	Point point_Button_Menu_Save_Close;
	void onEnterTransitionDidFinish();
};

#endif