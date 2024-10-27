#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
using namespace CocosDenshion;
bool GameScene::init(){
	if(!Layer::init())
	{
	 return false;
	}
	//��ӱ�����
	auto spbk=Sprite::create("background4.png");
	spbk->setAnchorPoint(Point::ZERO);
	spbk->setPosition(Point::ZERO);
	this->addChild(spbk);
	spbk->setTag(10);
	auto spbk02=Sprite::create("background4.png");
	spbk02->setAnchorPoint(Point::ZERO);
	spbk02->setPosition(Point::ZERO);
	spbk02->setPositionY(spbk->getPositionY()+680);
	this->addChild(spbk02);
	spbk02->setTag(11);
	//��ӷ�����ʾ
	score=0;
	auto labScore=Label::create("score:0","Marker Felt",20);
	labScore->setPosition(Point(30,440));
	labScore->setColor(Color3B::RED);
	this->addChild(labScore);
	labScore->setTag(120);
	//��ӷɻ�����
	auto spPlane=Sprite::create();
	spPlane->setTag(110);
	spPlane->setPosition(Point(160,240));
	this->addChild(spPlane);
	Vector<SpriteFrame*> allframe;//��������֡
	for(int i=0;i<4;i++)
	{
		SpriteFrame * sf=SpriteFrame::create("player.png",Rect(i*47,0,47,56));
		allframe.pushBack(sf);
	}
	Animation * ani=Animation::createWithSpriteFrames(allframe,0.1);
	spPlane->runAction(RepeatForever::create(Animate::create(ani)));
	//ͨ�������¼� ���Ʒɻ��ƶ�
	EventListenerTouchOneByOne * event=EventListenerTouchOneByOne::create();
	event->setSwallowTouches(true);
	event->onTouchBegan=CC_CALLBACK_2(GameScene::onTouchBegan,this);
	event->onTouchMoved=CC_CALLBACK_2(GameScene::onTouchMoved,this);
	event->onTouchEnded=CC_CALLBACK_2(GameScene::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);
	
	//�ƻ�����
	//��������
	this->schedule(schedule_selector(GameScene::moveBackground),0.01);
	//�����ӵ�����
	this->schedule(schedule_selector(GameScene::newBullet),0.5);
	this->schedule(schedule_selector(GameScene::moveBullet),0.01);
	//����л��ķ���
	this->schedule(schedule_selector(GameScene::newEnemy),0.5);
	this->schedule(schedule_selector(GameScene::moveEnemy),0.01);
	//������ײ������Ϸ�߼�
	this->scheduleUpdate();
	//���ű�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic("game.mp3",true);
	return true;
}
Scene *  GameScene::createScene(){
	auto scene=Scene::create();
	auto layer=GameScene::create();
	scene->addChild(layer);
	return scene;
}
void  GameScene::moveBackground(float t)//��������
{
	auto spbk=this->getChildByTag(10);
	auto spbk02=this->getChildByTag(11);
	spbk->setPositionY(spbk->getPositionY()-1);
	if(spbk->getPositionY()<-680)
	{
		spbk->setPositionY(0);
	}
	spbk02->setPositionY(spbk->getPositionY()+680);
}
bool GameScene::onTouchBegan(Touch *touch, Event *unused_event){
	px=touch->getLocation().x;
	py=touch->getLocation().y;
	return true;
}
void GameScene::onTouchMoved(Touch *touch, Event *unused_event){
	int mx=(touch->getLocation().x-px);
    int my=(touch->getLocation().y-py);
	auto spPlane=this->getChildByTag(110);
	spPlane->runAction(MoveBy::create(0,Point(mx,my)));
	px=touch->getLocation().x;
	py=touch->getLocation().y;
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event){

}
void  GameScene::newBullet(float t){
	auto spPlane=this->getChildByTag(110);
	Sprite * bullet=Sprite::create("bullet3.png");
	bullet->setPosition(spPlane->getPosition());
	this->addChild(bullet);
	this->allBullet.pushBack(bullet);
}
void  GameScene::moveBullet(float t){
	
	//for (auto nowbullet:allBullet)
	for(int i=0;i<allBullet.size();i++)
	{  auto nowbullet=allBullet.at(i);
		nowbullet->setPositionY(nowbullet->getPositionY()+3);
		if(nowbullet->getPositionY()>Director::getInstance()->getWinSize().height)
		{  
			nowbullet->removeFromParent();
			allBullet.eraseObject(nowbullet);
			i--;
		}
	}
}
void  GameScene::newEnemy(float t){
	
	Sprite * enemy=nullptr;
	int num=rand()%10;
	if(num>=3)
	{
	    enemy=Sprite::create("aaa.png");
		enemy->setTag(1000);
	}
	else
	{   enemy=Sprite::create("ccc.png");
	    enemy->setTag(2000);
	}
	enemy->setPosition(Point(rand()%300+10,500));
	this->addChild(enemy);
	this->allEnemy.pushBack(enemy);
}
void  GameScene::moveEnemy(float t){
	
	for(int i=0;i<allEnemy.size();i++)
	{  auto nowenemy=allEnemy.at(i);
		nowenemy->setPositionY(nowenemy->getPositionY()-3);
		if(nowenemy->getPositionY()<0)
		{  
			nowenemy->removeFromParent();
			allEnemy.eraseObject(nowenemy);
			i--;
		}
	}
}
void GameScene::update(float t){
	
	//��ײ���
	auto spPlane=this->getChildByTag(110);
	Rect rp(spPlane->getPositionX(),spPlane->getPositionY(),47,56);
	for(int i=0;i<allEnemy.size();i++)
	{  auto nowenemy=allEnemy.at(i);
	    Rect er(nowenemy->getPositionX(),nowenemy->getPositionY(),40,50);
       //�ͷɻ���ײ���
		if(rp.intersectsRect(er))
		{
			 // //��ըЧ�� 
			   newBomb(spPlane->getPositionX(),spPlane->getPositionY());
		      //�л���ʧ
			   nowenemy->removeFromParent();
			   allEnemy.eraseObject(nowenemy);
			   i--;
			   //��������
			   SimpleAudioEngine::getInstance()->playEffect("explo.wav");
			   //��ת��GAMEOVER
			   //Director::getInstance()->getActionManager()->pauseAllRunningActions();
			   this->pauseSchedulerAndActions();
			   auto spover=Sprite::create("end.png");
			   spover->setPosition(Point::ZERO);
			   spover->setAnchorPoint(Point::ZERO);
			   this->addChild(spover);
			   auto act=Sequence::create(
				   DelayTime::create(2),
				   CallFunc::create(this,callfunc_selector(GameScene::jumpToMenu)),
				   NULL
				   );
			   this->runAction(act);
		}
		//���ӵ���ײ���
	   for(int j=0;j<allBullet.size();j++)
	   { auto nowbullet=allBullet.at(j);
	       Rect br(nowbullet->getPositionX(),nowbullet->getPositionY(),20,20);
		   if(er.intersectsRect(br))
		   {//�ӵ������˵л�
			   Label * labScore=(Label*)this->getChildByTag(120);
			   score+=nowenemy->getTag();
			    //��ըЧ�� 
			    newBomb(nowbullet->getPositionX(),nowbullet->getPositionY());
				//����ϵͳ
				auto ps=ParticleSystemQuad::create("bomb.plist");
				ps->setPosition(Point(nowbullet->getPositionX(),nowbullet->getPositionY()));
				this->addChild(ps);
		      //�ӷ�
			   labScore->setString(String::createWithFormat("score:%d",score)->_string);
			  //�ӵ���ʧ
			   nowbullet->removeFromParent();
			   allBullet.eraseObject(nowbullet);
			  //�л���ʧ
			   nowenemy->removeFromParent();
			   allEnemy.eraseObject(nowenemy);
			   i--;
			   //��������
			   SimpleAudioEngine::getInstance()->playEffect("explo.wav");
			
			   break;
			 
		   }

	   }
	}
}
void GameScene::newBomb(int x,int  y)//��ըЧ��
{
	Vector<SpriteFrame*> allframe;
	for(int i=0;i<7;i++)
	{
		SpriteFrame * sf=SpriteFrame::create("boom.png",Rect(i*44,0,44,47));
		allframe.pushBack(sf);
	}
	Animation * ani=Animation::createWithSpriteFrames(allframe,0.03);
	auto sprite=Sprite::create();
	Action * act=Sequence::create(
		Animate::create(ani),  //����
		CCCallFuncN::create(sprite,callfuncN_selector(GameScene::killMe)), //ɾ���Լ�
		NULL);
	this->addChild(sprite);
	sprite->setPosition(Point(x,y));
	sprite->runAction(act);
	
}
void GameScene::killMe(Node * pSender)//ɾ���Լ�
{
	pSender->removeFromParentAndCleanup(true);
}
void GameScene::jumpToMenu()//��ת�����˵�
{
	
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}