#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class TestLayer :public Layer
{
public:
	static Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(TestLayer);
};
