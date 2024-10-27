#ifndef HELP_SCENE
#define HELP_SCENE
#include "cocos2d.h"
using namespace cocos2d;
class HelpScene:Layer{
public:
	bool init();
	CREATE_FUNC(HelpScene);
	static Scene * createScene();

};
#endif