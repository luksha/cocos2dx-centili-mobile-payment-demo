#include "HelloWorldScene.h"
#include "/platform/android/jni/JniHelper.h"


USING_NS_CC;

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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	 auto buyButton = MenuItemImage::create(
                                           "buy-normal.png",
                                           "buy-selected.png",
                                           CC_CALLBACK_1(HelloWorld::menuPayButton, this));
    
	buyButton->setPosition(Vec2(origin.x + visibleSize.width/2 ,
								origin.y + visibleSize.height*0.20));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, buyButton, NULL);
	//auto menuButton = Menu::create(payButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Centili mobile payment demo for cocos2dx", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

void HelloWorld::menuPayButton(Ref* pSender){

	#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
		MessageBox("This is payment implementation for Android","Alert");
		return;
	#endif

	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",//class
		"centiliPayment",//method
		"(Ljava/lang/String;)V")) {
 
			 const char* apikey = "c9534ea982c37bb5da3956283ea50032";
 
			 jstring stringArg1 = t.env->NewStringUTF(apikey);
			 t.env->CallStaticVoidMethod(t.classID,
										 t.methodID,
										 stringArg1
			);

     t.env->DeleteLocalRef(t.classID);
	 t.env->DeleteLocalRef(stringArg1);
	}
	
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
	#endif

    Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif

}




