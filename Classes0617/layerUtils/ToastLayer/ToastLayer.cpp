#include "ToastLayer.h"
#include "Utils/CommonFunction.h"

void   creatNodeFadeToAction(Node * node)
{
	Vector<Node *> m_nodeChildren = node->getChildren();
	for (int i = 0; i < m_nodeChildren.size(); i++)
	{
		m_nodeChildren.at(i)->runAction(FadeOut::create(0.5f));
	}
}

void  Toast::nodeDeleteAction()
{
	this->getChildByName("lable")->runAction(FadeOut::create(0.5f));

	creatNodeFadeToAction(this->getChildByName("scale"));

	FiniteTimeAction *  callfun = CallFunc::create(this, callfunc_selector(Toast::removeThis));
	runAction(Sequence::create(DelayTime::create(0.6), callfun, NULL));
}

void  Toast::removeThis()
{
	this->stopAllActions();
	m_toastLayer->deleteNode(this);
}

Toast* Toast::create(std::string str, ToastLayer * toastLayer)
{
	Toast  * toast = new Toast();

	toast->m_toastLayer = toastLayer;
	toast->m_showString = str;
	toast->OnInit();
	toast->autorelease();
	return toast;
}

void Toast::OnInit()
{
	Layer::init();

	auto m_bg = Scale9Sprite::create("dr_tcd.png", Rect(0, 0, 45, 44));
	m_bg->setPosition(CommonFunction::getVisibleAchor(0.5, 0.2, Vec2(0, 75)));
	m_bg->setContentSize(Size(200, 60));
	m_bg->setName("scale");
	this->addChild(m_bg, 10);

	Label * m_label = Label::createWithSystemFont(m_showString, "Microsoft Yahei", 18, Size(200, 30),
		TextHAlignment::CENTER, TextVAlignment::CENTER
		);
	m_label->setColor(Color3B(36, 247, 255));
	m_label->setName("lable");
	m_label->setPosition(CommonFunction::getVisibleAchor(0.5, 0.2, Vec2(0, 75)));
	this->addChild(m_label, 100);

	FiniteTimeAction *  callfun = CallFunc::create(this, callfunc_selector(Toast::nodeDeleteAction));
	this->runAction(Sequence::create(DelayTime::create(1), callfun, NULL));
}

ToastLayer::ToastLayer()
{

}

ToastLayer::~ToastLayer()
{
	m_node.clear();
}

ToastLayer* ToastLayer::create()
{
	ToastLayer  * toastLayer = new ToastLayer();
	toastLayer->OnInit();
	toastLayer->autorelease();
	return toastLayer;
}

void ToastLayer::OnInit()//初始化
{
	Layer::init();
}

void  ToastLayer::moveNode()//移动节点
{
	for (int i = 0; i < m_node.size(); i++)
	{
		m_node.at(i)->setPositionY(m_node.at(i)->getPositionY() + MOVE_LENGTH);
	}

	if (m_node.size() > 3)
	{
		for (int i = 0; i < m_node.size() - 2; i++)
		{
			m_node.at(i)->stopAllActions();
			deleteNode(m_node.at(i));
		}
	}
}

void  ToastLayer::addLayer(std::string str)
{
	//层移动
	if (m_node.size() > 0)
	{
		moveNode();
	}

	Toast* ToastL = Toast::create(str, this);
	this->addChild((Node *)ToastL);
	m_node.push_back((Node *)ToastL);//添加至容器
}

void ToastLayer::deleteNode(Node * node)//删除节点
{
	if (node == NULL)return;

	std::vector<Node*>::iterator it = m_node.begin();
	while (it != m_node.end())
	{
		if (*it == node)
		{
			this->removeChild(*it);
			m_node.erase(it);
			break;
		}
		it++;
	}
}