#include "HelloWorldScene.h"
#include "GameScene.h"
#include "HelpScene.h"
#include "AboutScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
	closeItem->setTag(10);
	//新增菜单条目
	auto gameItem=MenuItemFont::create("StartGame",CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
	auto helpItem=MenuItemFont::create("Help",CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    auto aboutItem=MenuItemFont::create("About",CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
	gameItem->setPosition(Point(origin.x + visibleSize.width/2 - closeItem->getContentSize().width/2,200 ));
	helpItem->setPosition(Point(origin.x + visibleSize.width/2 - closeItem->getContentSize().width/2,150 ));
    aboutItem->setPosition(Point(origin.x + visibleSize.width/2 - closeItem->getContentSize().width/2,100 ));
	gameItem->setColor(Color3B::BLACK);
	helpItem->setColor(Color3B::BLACK);
	aboutItem->setColor(Color3B::BLACK);
	gameItem->setTag(11);
	helpItem->setTag(12);
	aboutItem->setTag(13);
    // create menu, it's an autorelease object
	auto menu = Menu::create(closeItem,gameItem,helpItem,aboutItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("menu.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{  MenuItem * nowItem=(MenuItem *)pSender;
//播放音效
SimpleAudioEngine::getInstance()->playEffect("select.wav");
  switch(nowItem->getTag())
  {
  case 10:
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	 MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
     return;
    #endif
    Director::getInstance()->end();
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
	#endif
	break;
  case 11://game
	  Director::getInstance()->replaceScene(GameScene::createScene());
	  break;
  case 12://help
	  
	  Director::getInstance()->replaceScene( TransitionFlipY::create(1,HelpScene::createScene()));
	  break;
  case 13://about
	  Director::getInstance()->replaceScene( TransitionFlipY::create(1,AboutScene::createScene()));
	  break;

}
}