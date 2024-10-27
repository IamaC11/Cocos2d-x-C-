#ifndef GAME_SCENE
#define GAME_SCENE
#include "cocos2d.h"
using namespace cocos2d;
class GameScene:Layer{
public:
	bool init();
	CREATE_FUNC(GameScene);
	static Scene * createScene();
	void moveBackground(float t);//滚动背景
	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 
    int px,py;//飞机的坐标
	Vector<Sprite *> allBullet;//所有子弹
	void newBullet(float t);
	void moveBullet(float t);
	Vector<Sprite *> allEnemy;//所有敌机
	void newEnemy(float t);
	void moveEnemy(float t);
	void update(float t);
	int score;//分数
	void newBomb(int x,int  y);//爆炸效果
	void killMe(Node * pSender);//删除自己
	void jumpToMenu();//跳转到主菜单
};
#endif