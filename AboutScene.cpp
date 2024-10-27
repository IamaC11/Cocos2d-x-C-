#include "AboutScene.h"
#include "HelloWorldScene.h"
bool AboutScene::init(){
	if(!Layer::init())
	{
	 return false;
	}
	auto spbk=Sprite::create("about.png");
	spbk->setPosition(Point::ZERO);
	spbk->setAnchorPoint(Point::ZERO);
	this->addChild(spbk);
	EventListenerTouchOneByOne * touch=EventListenerTouchOneByOne::create();
	touch->onTouchBegan=[](Touch * touch,Event * event){
	return true;
	};
	touch->onTouchMoved=[](Touch * touch,Event * event){
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch,this);
	return true;
}
Scene *  AboutScene::createScene(){
	auto scene=Scene::create();
	auto layer=AboutScene::create();
	scene->addChild(layer);
	return scene;
}