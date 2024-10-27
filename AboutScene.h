#ifndef ABOUT_SCENE
#define ABOUT_SCENE
#include "cocos2d.h"
using namespace cocos2d;
class AboutScene:Layer{
public:
	bool init();
	CREATE_FUNC(AboutScene);
	static Scene * createScene();

};
#endif