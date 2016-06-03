#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "layer/GameScene.h"
#include "layer/WelcomeScene.h"

USING_NS_CC;

static cocos2d::Size mydesignResolutionSize = cocos2d::Size(960, 640);

float DESIGN_RATIO = 1.5f;
int DESIGN_PAD_WIDTH = 1024;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {

	//将log结果呈现在输出窗口
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("ZIPAI", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

	Size size = Director::getInstance()->getWinSize();

	float ratio = size.width / size.height;

	if (ratio >= DESIGN_RATIO)
	{
		float height = mydesignResolutionSize.height;
		float width = height * ratio;
		glview->setDesignResolutionSize(width, height, ResolutionPolicy::EXACT_FIT);
	}
	else
	{
		//float width = mydesignResolutionSize.width;
		float width = DESIGN_PAD_WIDTH;
		float height = width / ratio;
		glview->setDesignResolutionSize(width, height, ResolutionPolicy::EXACT_FIT);
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	glview->setFrameSize(960, 640);

#endif

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	FileUtils::getInstance()->addSearchPath("res");
	FileUtils::getInstance()->addSearchPath("icon_image");

	//auto scene = HelloWorld::createScene();
	//auto scene = GameScene::createScene();
	auto scene = WelcomeScene::createScene();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
