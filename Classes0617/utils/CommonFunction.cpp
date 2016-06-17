#include "CommonFunction.h"

Vec2 CommonFunction::getVisibleAchor(Anchor anchor, Vec2 deltaPos)
{
	return getVisibleAchor(anchor, NULL, deltaPos);
}

Vec2 CommonFunction::getVisibleAchor(Anchor anchor, Node * node, Vec2 deltaPos)
{
	Size winSize;
	if (node == NULL)
		winSize = Director::getInstance()->getVisibleSize();
	else
		winSize = node->getContentSize();

	Point origPos = Director::getInstance()->getVisibleOrigin();

	if (anchor == Anchor::LeftButtom)
	{
		return Vec2(0 + deltaPos.x + origPos.x, 0 + deltaPos.y + origPos.y);
	}
	else if (anchor == Anchor::LeftMid)
	{
		return Vec2(0 + deltaPos.x + origPos.x, winSize.height / 2 + deltaPos.y + origPos.y);
	}
	else if (anchor == Anchor::LeftTop)
	{
		return Vec2(0 + deltaPos.x + origPos.x, winSize.height + deltaPos.y + origPos.y);
	}
	else if (anchor == Anchor::MidButtom)
	{
		return Vec2(winSize.width / 2 + deltaPos.x + origPos.x, 0 + deltaPos.y + origPos.y);
	}
	else if (anchor == Anchor::Center)
	{
		return Vec2(winSize.width / 2 + deltaPos.x + origPos.x, winSize.height / 2 + deltaPos.y + origPos.y);
	}
	else if (anchor == Anchor::MidTop)
	{
		return Vec2(winSize.width / 2 + deltaPos.x + origPos.x, winSize.height + deltaPos.y + origPos.y);
	}
	else if (anchor == Anchor::RightButtom)
	{
		return Vec2(winSize.width + deltaPos.x + origPos.x, 0 + deltaPos.y + origPos.y);
	}
	else if (anchor == Anchor::RightMid)
	{
		return Vec2(winSize.width + deltaPos.x + origPos.x, winSize.height / 2 + deltaPos.y + origPos.y);
	}
	else if (anchor == Anchor::RightTop)
	{
		return Vec2(winSize.width + deltaPos.x + origPos.x, winSize.height + deltaPos.y + origPos.y);
	}
	return Vec2(0, 0);
}

Vec2 CommonFunction::getVisibleAchor(float pointx, float pointy, Vec2 deltaPos)
{
	Size winSize = Director::getInstance()->getVisibleSize();
	Point origPos = Director::getInstance()->getVisibleOrigin();

	return Vec2(winSize.width * pointx + deltaPos.x + origPos.x, winSize.height*pointy + deltaPos.y + origPos.y);
}

Vec2 CommonFunction::getVisibleAchor(float pointx, float pointy, Node * node, Vec2 deltaPos)
{
	return Vec2(node->getContentSize().width * pointx + deltaPos.x, node->getContentSize().height* pointy + deltaPos.y);
}


/*


std::string CommonFunction::getLableText(std::string &str, Color3B &fontColor, int &fontSize)
{
	std::string textStr;
	int t1 = str.find("[");
	int t2 = str.find("]");

	if (t1 < 0 || t2 < 0)//只有一条数据
	{
		textStr = str;
		str = "";
		fontColor = Color3B(255, 255, 255);
		fontSize = 16;
		return textStr;
	}
	else if (t1 > 0)//非标准没有配字体颜色
	{
		fontColor = Color3B(255, 255, 255);
		fontSize = 16;
		textStr = getRemaining(str);//文本数据
		return textStr;
	}
	else if (t1 == 0)//标准配置 字体 颜色
	{
		std::string strColorSize = str.substr(t1, t2 + 1);//字体颜色大小

		getStrColor(strColorSize, fontColor);
		getStrSize(strColorSize, fontSize);

		str = str.substr(t2 + 1, str.size() - t2 + 1);//除掉颜色后剩余数据

		textStr = getRemaining(str);//文本数据
		return  textStr;
	}
}
*/

/*
std::string  CommonFunction::getRemaining(std::string &str)
{
	std::string textStr;
	int nextT1 = str.find("[");
	if (nextT1 > 0)
	{
		textStr = str.substr(0, nextT1);//文本
		str = str.substr(nextT1, str.size() - nextT1);//剩余
	}
	else
	{
		textStr = str;
		str = "";
	}
	return textStr;
}

*/

/*
Widget * CommonFunction::createWidgetButton(Node* childNode, float touchSizeScale)
{
	Widget * widget = Widget::create();
	widget->setContentSize(childNode->getContentSize()*touchSizeScale);
	widget->setAnchorPoint(Vec2(0.5, 0.5));
	widget->setTouchEnabled(true);

	childNode->setAnchorPoint(Vec2(0.5, 0.5));
	childNode->setPosition(CommonFunction::getVisibleAchor(0.5, 0.5, widget, Vec2::ZERO));
	widget->addChild(childNode);

	return widget;
}
*/
/*
RichElementText*CommonFunction:: creatReText(int tag, const Color3B& color, GLubyte opacity, std::string text,
	const std::string& fontName, float fontSize)
{
	RichElementText* re = RichElementText::create(tag, color, opacity, text, fontName, fontSize);
	return   re;
}

*/


/*
cocos2d::ui::RichText * CommonFunction::getRichtext(std::string textStr, float richWight, float richHight, bool readColor)
{
	RichText* _richText = RichText::create();
	_richText->ignoreContentAdaptWithSize(false);
	_richText->setSize(Size(richWight, richHight));

	RichElementText*  re = NULL;
	int i = 100;
	Color3B fontcolor;
	int fontsize;
	while (1)
	{
		if (textStr.size() > 0)
		{
			std::string text = CommonFunction::getLableText(textStr, fontcolor, fontsize);
			if (readColor == false)
			{
				fontcolor = Color3B(0, 0, 0);
			}

			re = creatReText(i, fontcolor, 255, text, "Microsoft Yahei", fontsize);
			_richText->pushBackElement(re);
		}
		else
		{
			break;
		}
		i++;
	}

	return _richText;
}
*/




CCActionInterval * CommonFunction::setScaleto(float time, float scalNum, EaseElasticOutType type)
{
	CCActionInterval * elasticin = NULL;
	switch (type)
	{
	case Out:
		elasticin = CCEaseElasticOut::create(CCScaleTo::create(time, scalNum));
		break;
	case in:
		elasticin = CCScaleTo::create(time, scalNum);
		break;
	default:
		break;
	}

	return elasticin;
}

//获取文本颜色
Color3B CommonFunction::getColor(std::string clorStr)
{
	std::string r, g, b;
	for (int i = 0; i < clorStr.size(); i++)
	{
		if (i < 2)
		{
			r += clorStr[i];
		}
		else if (i >1 && i <4)
		{
			g += clorStr[i];
		}
		else if (i>3 && i < 6)
		{
			b += clorStr[i];
		}
	}
	return Color3B(CommonFunction::htoi(r), CommonFunction::htoi(g), CommonFunction::htoi(b));
}


void CommonFunction::stopAction(Node* node, Vec2 vec)//暂停指定对象动作
{
	CCDirector::sharedDirector()->getActionManager()->removeAllActionsFromTarget(node);
	node->setPosition(vec);
}

void CommonFunction::nodeVisible(Node* node, bool isVisibel)
{
	node->setVisible(isVisibel);

	Vector<Node *> m_nodeChildren = node->getChildren();
	for (int i = 0; i < m_nodeChildren.size(); i++)
	{
		m_nodeChildren.at(i)->setVisible(isVisibel);
		nodeFadeOut(m_nodeChildren.at(i), isVisibel);
	}
}

void CommonFunction::setNodeOpacity(Node * node, float opacity)
{
	node->setOpacity(opacity);

	Vector<Node *> m_nodeChildren = node->getChildren();
	for (int i = 0; i < m_nodeChildren.size(); i++)
	{
		m_nodeChildren.at(i)->setOpacity(opacity);
		setNodeOpacity(m_nodeChildren.at(i));
	}
}

void CommonFunction::nodeVisit(Node * node)
{
	node->visit();

	Vector<Node *> m_nodeChildren = node->getChildren();
	for (int i = 0; i < m_nodeChildren.size(); i++)
	{
		m_nodeChildren.at(i)->visit();
		nodeVisit(m_nodeChildren.at(i));
	}
}

Node* CommonFunction::getNodeChildByTag(Node * node, int childTag)
{
	Node * m_node = NULL;

	m_node = node->getChildByTag(childTag);
	if (m_node == NULL)
	{
		Vector<Node *> m_nodeChildren = node->getChildren();
		for (int i = 0; i < m_nodeChildren.size(); i++)
		{
			Node* subNode = getNodeChildByTag(m_nodeChildren.at(i), childTag);
			if (subNode != NULL)
			{
				return subNode;
			}
		}
	}
	else
	{
		return m_node;
	}
	return NULL;
}

//精灵变灰
Sprite* CommonFunction::MakeSpiteGray(std::string imageName)
{
	Sprite* sprite_chess;

	CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName);
	if (spriteFrame)
	{
		sprite_chess = Sprite::createWithSpriteFrameName(imageName);
	}
	else
	{
		sprite_chess = Sprite::create(imageName);
	}

	sprite_chess->setPosition(sprite_chess->getContentSize().width / 2, sprite_chess->getContentSize().height / 2);

	RenderTexture *render = RenderTexture::create(sprite_chess->getContentSize().width, sprite_chess->getContentSize().height, Texture2D::PixelFormat::RGBA8888);
	render->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
	sprite_chess->visit();
	render->end();
	Director::getInstance()->getRenderer()->render();

	Image *finalImage = render->newImage();

	unsigned char *pData = finalImage->getData();

	int iIndex = 0;

	for (int i = 0; i < finalImage->getHeight(); i++)
	{
		for (int j = 0; j < finalImage->getWidth(); j++)
		{
			// gray
			int iBPos = iIndex;

			unsigned int iB = pData[iIndex];

			iIndex++;

			unsigned int iG = pData[iIndex];

			iIndex++;

			unsigned int iR = pData[iIndex];

			iIndex++;
			iIndex++;

			unsigned int iGray = 0.3 * iR + 0.6 * iG + 0.1 * iB;

			pData[iBPos] = pData[iBPos + 1] = pData[iBPos + 2] = (unsigned char)iGray;
		}

	}

	Texture2D *texture = new Texture2D;
	texture->initWithImage(finalImage);

	auto pSprite = Sprite::createWithTexture(texture);

	delete finalImage;

	texture->release();

	return pSprite;

}



std::string CommonFunction::decodeDataBasePSW()
{
	return "######";
}

std::string& CommonFunction::replace_all(std::string& str, const std::string& old_value, const std::string& new_value)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())   {
		if ((pos = str.find(old_value, pos)) != std::string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}

CCActionInterval * CommonFunction::GetShakeAction(ShakeMode mode)
{
	CCActionInterval* action;
	if (mode == Intensity)
	{
		action = CCSequence::create(
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-14, 10)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(12, -10)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-18, -22)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(7, 11)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-22, 3)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(1, -11)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(5, 12)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-9, 2)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-5, 15)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-4, 5)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, 0)),
			NULL
			);
	}
	else if (mode == Moderation)
	{
		action = CCSequence::create(
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, 0)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-3, 3)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(1, -4)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(4, 7)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-3, -2)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, 4)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(3, -4)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-1, 2)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, -1)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-2, 2)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, -3)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, 2)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-3, -2)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, 0)),
			NULL
			);
	}
	else if (mode == Slight)
	{
		action = CCSequence::create(
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, 0)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-2, 1)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(1, -1)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-3, 6)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-1, -1)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(1, 1)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(2, -2)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, 2)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, 0)),
			NULL
			);
	}
	else if (mode == SlightNormal)
	{
		action = CCSequence::create(
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-2, 1)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(1, -1)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(-3, 6)),
			CCMoveTo::create(WM_TIME_NUMBER, Vec2(0, 0)),
			NULL
			);
	}
	action->setTag(1000);
	return action;
}



void CommonFunction::runShakeAction(Node* runNode, ShakeMode mode)
{
	if (runNode->getActionByTag(1000) == nullptr)
	{
		runNode->runAction(GetShakeAction(mode));
	}
}

void CommonFunction::stopAllAction(Node *node)
{
	node->stopAllActions();

	Vector<Node *> m_nodeChildren = node->getChildren();
	for (int i = 0; i < m_nodeChildren.size(); i++)
	{
		m_nodeChildren.at(i)->stopAllActions();
		stopAllAction(m_nodeChildren.at(i));
	}
}

void CommonFunction::nodeFadeOut(Node * node, float time)
{
	node->runAction(CCFadeOut::create(time));

	Vector<Node *> m_nodeChildren = node->getChildren();
	for (int i = 0; i < m_nodeChildren.size(); i++)
	{
		m_nodeChildren.at(i)->runAction(CCFadeOut::create(time));
		nodeFadeOut(m_nodeChildren.at(i), time);
	}
}

void CommonFunction::nodeFadeIn(Node * node, float time)
{
	node->setOpacity(0);
	node->runAction(CCSequence::create(CCFadeIn::create(time), NULL));

	Vector<Node *> m_nodeChildren = node->getChildren();
	for (int i = 0; i < m_nodeChildren.size(); i++)
	{
		m_nodeChildren.at(i)->setOpacity(0);
		m_nodeChildren.at(i)->runAction(CCSequence::create(CCFadeIn::create(time), NULL));
		nodeFadeIn(m_nodeChildren.at(i), time);
	}
}


cocostudio::CCArmature * CommonFunction::loadArmature(std::string imagePath, std::string plistPath, std::string configFilePath, std::string armatureName)//加载动画
{
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, "Config/" + plistPath, "Config/" + configFilePath);
	CCArmature * m_armature = CCArmature::create(armatureName);
	m_armature->setCascadeOpacityEnabled(true);
	m_armature->setVersion(1);
	m_armature->getAnimation()->playByIndex(0);
	return m_armature;
}

cocostudio::CCArmature * CommonFunction::loadArmatures(std::string imagePath, std::string plistPath, std::string configFilePath, std::string armatureName)//加载动画
{
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, "Config/" + plistPath, "Config/" + configFilePath);
	CCArmature * m_armature = CCArmature::create(armatureName);
	m_armature->setCascadeOpacityEnabled(true);
	m_armature->setVersion(1);
	return m_armature;
}

Animate* CommonFunction::getCCAnimate(std::string imageName, float &actionTime, float intervalTime)
{
	Size size;
	return getCCAnimate(imageName, size, actionTime, intervalTime);
}

Animate* CommonFunction::getCCAnimate(std::string imageName, float intervalTime)
{
	float actionTime = 0;
	return getCCAnimate(imageName, actionTime, intervalTime);
}

Animate* CommonFunction::getCCAnimate(std::string imageName, Size &spriteSize, float intervalTime)
{
	float actionTime = 0;
	return getCCAnimate(imageName, spriteSize, actionTime, intervalTime);
}
Animate* CommonFunction::getCCAnimate(std::string imageName, Size &spriteSize, float &actionTime, float intervalTime)
{
	Vector<SpriteFrame*> animFrames;
	SpriteFrame *spriteFrame;
	char path[50];

	int index = 1;
	while (1)
	{
		sprintf(path, "%s%d.png", imageName.c_str(), index);
		spriteFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path);
		if (spriteFrame == NULL)
			break;

		spriteSize = spriteFrame->getOriginalSize();
		actionTime += intervalTime;
		animFrames.pushBack(spriteFrame);
		index++;
	}

	if (animFrames.size() > 0)
	{
		Animation *animation = Animation::createWithSpriteFrames(animFrames, intervalTime);
		Animate *termpAnimate = Animate::create(animation);

		animFrames.clear();
		return termpAnimate;
	}

	return NULL;
}


std::string CommonFunction::getString(int number)//获取字符串
{
	char buf[20];
	sprintf(buf, "%d", number);
	std::string  str(buf);
	return str;
}

std::string CommonFunction::getString(float number)//获取字符串
{
	char buf[20];
	sprintf(buf, "%.1f", number);
	std::string  str(buf);
	return str;
}
void  getStrColor(std::string &str, Color3B &fontColor)
{
	int t1 = str.find("=");

	std::string color = str.substr(t1 + 1, 6);

	fontColor = CommonFunction::getColor(color);

	str = str.substr(t1 + 1 + 6, str.size() - (6));
}

void  getStrSize(std::string &str, int &fontSize)
{
	int t1 = str.find("=");

	std::string size = str.substr(t1 + 1, 2);

	fontSize = atoi(size.c_str());
}

std::string  getRemaining(std::string &str)
{
	std::string textStr;
	int nextT1 = str.find("[");
	if (nextT1 > 0)
	{
		textStr = str.substr(0, nextT1);//文本
		str = str.substr(nextT1, str.size() - nextT1);//剩余
	}
	else
	{
		textStr = str;
		str = "";
	}
	return textStr;
}

std::string CommonFunction::getLableText(std::string &str, Color3B &fontColor, int &fontSize)
{
	std::string textStr;
	int t1 = str.find("[");
	int t2 = str.find("]");

	if (t1 < 0 || t2 < 0)//只有一条数据
	{
		textStr = str;
		str = "";
		fontColor = Color3B(255, 255, 255);
		fontSize = 16;
		return textStr;
	}
	else if (t1 > 0)//非标准没有配字体颜色
	{
		fontColor = Color3B(255, 255, 255);
		fontSize = 16;
		textStr = getRemaining(str);//文本数据
		return textStr;
	}
	else if (t1 == 0)//标准配置 字体 颜色
	{
		std::string strColorSize = str.substr(t1, t2 + 1);//字体颜色大小

		getStrColor(strColorSize, fontColor);
		getStrSize(strColorSize, fontSize);

		str = str.substr(t2 + 1, str.size() - t2 + 1);//除掉颜色后剩余数据

		textStr = getRemaining(str);//文本数据
		return  textStr;
	}
}

std::string CommonFunction::getImageName(int iconID)//获取图片名
{
	char  namebuf[20];
	sprintf(namebuf, "%d.png", iconID);
	std::string nameStr = namebuf;
	return nameStr;
}
/*
float CommonFunction::getWinRate()
{
	Size winSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	float rateWidth = winSize.width / WINDOWS_STANDARD_WIDTH;
	float rateHeight = winSize.height / WINDOWS_STANDARD_HEIGHT;
	float rate = 1;
	if (rateHeight > rateWidth)
	{
		rate = rateHeight / rateWidth;
	}
	if (rateWidth > rateHeight)
	{
		rate = 1;
	}

	return rate;
}
*/
int CommonFunction::htoi(std::string  s)
{
	int n = 0;
	for (int i = 0; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'); i++)
	{
		if (s[i] > '9')
		{
			n = 16 * n + (10 + s[i] - 'a');
		}
		else
		{
			n = 16 * n + (s[i] - '0');
		}
	}

	return n;
}

void CommonFunction::WStrToUTF8(std::string& dest, const std::wstring& src)
{
	dest.clear();
	for (size_t i = 0; i < src.size(); i++)
	{
		wchar_t w = src[i];
		if (w <= 0x7f)
			dest.push_back((char)w);
		else if (w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
		{
			dest.push_back(0xf0 | ((w >> 18) & 0x07));
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
}





std::string CommonFunction::WStrToUTF8(const std::wstring& str)
{
	std::string result;
	WStrToUTF8(result, str);
	return result;
}


/*
1.先加载 plist png 图片到缓存池
2.用这个方法创建Animation对象
3.创建animate
4.精灵运行此动画


例子：

SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
frameCache->addSpriteFramesWithFile("huang.plist", "huang.png");
auto sp = Sprite::create("10003.png");
sp->setPosition(visibleSize/2);
addChild(sp);

//auto animation = AnimationUtil::createWithSingleFrameName("1000",0.1f,-1);
//sp->runAction(Animate::create(animation));

auto animation1 = AnimationUtil::createWithFrameNameAndNum("1000",7,0.1f,-1);
sp->runAction(Animate::create(animation1));


*/

/*

不用指定有多少张图片，直接传入图片名字就是了

name:图片名字
delay: 每帧的延迟(0.1)
iLoops:循环 （-1循环,0不循环,1一次）
*/
Animation* CommonFunction::createWithSingleFrameName(const char* name, float delay, int iLoops){
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = nullptr;
	int index = 1;
	do
	{
		/*不断获取SpriteFrame对象直到获取的值为空*/
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name, index++));
		if (frame == nullptr)
		{
			break;
		}
		frameVec.pushBack(frame);
	} while (true);

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);	//0.1f
	return animation;
}

/*
需要传入图片的数量

name:图片名字
iNum:图片帧数量
delay:每帧的延迟(0.1)
iLoops:循环 （-1循环,0不循环,1一次）
*/
Animation* CommonFunction::createWithFrameNameAndNum(const char* name, int iNum, float delay, int iLoops){
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = nullptr;
	int index = 1;
	for (int i = 1; i <= iNum; i++)
	{
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name, i));
		if (frame == nullptr)
		{
			break;
		}
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);	//0.1f
	return animation;

}
//获取时间函数
int CommonFunction::getCurDay()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	time_t lt = time(0);
	tm* t = localtime(&lt);
	// 1年370天
	CCLOG("year = %d ,mon = %d ,year-day = %d ,second=%d", t->tm_year, t->tm_mon, t->tm_yday, lt);
	int day = t->tm_yday + 370 * t->tm_year; 
			//一年当中的第几天（第129天），从1900开始的第几年（116+1900 =2016）

	CCLOG("getCurDay:: %d", day);
	return day;
}

int CommonFunction::getCurDay(long long timeLong)
{
	time_t _time = timeLong;
	tm* t = localtime(&_time);
	// 1年370天
	CCLOG("year = %d,mon = %d ,year-day = %d ,second=%lld", t->tm_year, t->tm_mon, t->tm_yday, timeLong);
	int day = t->tm_yday + 370 * t->tm_year;
	CCLOG("server : getCurDay:: %d", day);
	return day;
}





