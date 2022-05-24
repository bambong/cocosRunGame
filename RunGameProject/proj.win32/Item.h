#pragma once
#include "ContactAbleObject.h"
#include "HelloWorldScene.h"
class Item : ContactAbleObject
{
private :
	HelloWorld* scene;
public :
	Item(HelloWorld* scene);

	virtual void Active();

};

