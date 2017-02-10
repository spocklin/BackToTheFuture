#ifndef __ICONS_H__
#define __ICONS_H__

#include "cocos2d.h"

USING_NS_CC;
class Icons: public Sprite
{
public :
	//��������״̬��������������������������
	enum IconsStatus{eIconOff,eIconOn,eIconOK};
	//��ʼ������
    virtual bool initNewIcons(std::string picture,std::string off_picture,std::string iconName,
		std::string iconIntroduction,int startNum,Icons::IconsStatus iconSta,int row,int column);


	//�����Զ��徫��ķ���
	static Icons* createNewIcons(std::string picture,std::string off_picture,std::string iconName,
		std::string iconIntroduction,int startNum,Icons::IconsStatus iconSta,int row,int column);
    CREATE_FUNC(Icons);


	//����iconSta�޸ľ���״̬
	void showIcon(Icons::IconsStatus iconSta);
	//�þ�����������Ҫ������
	int priceTag;
	//�ڲ���ʾ��ͼ�ꣻ
	Sprite* icon;
	//������ͼ
	Sprite* iconSelected;
	//�ж��Ƿ�ѡ��
	void iconIsSelect(bool select);
	
	//�ؼ�����
	std::string iconName;
	//�ؼ�����
	std::string iconIntroduction;
	//��������λ��
	int iconRow;
	int	iconColumn;


	IconsStatus getIconState();
	void setMayUpedate();
	void setUpdated();
protected:
	IconsStatus iconSta;
	Sprite* iconOKBack;
	
	std::string picture;
	std::string off_picture;

};

#endif