#include "ToastManger.h"
#include "Utils/CommonFunction.h"

static ToastManger* m_Toastmanger = NULL;

ToastManger* ToastManger::getInstance()
{
	if (m_Toastmanger == NULL)
	{
		m_Toastmanger = new ToastManger();
	}
	return m_Toastmanger;
}

ToastManger::ToastManger()
{
	m_scene = NULL;
}

ToastManger::~ToastManger()
{

}

void ToastManger::createToast(std::string str)
{
	Scene * sceneNode = Director::getInstance()->getRunningScene();

	createToast(str, sceneNode);
}

void ToastManger::createToast(std::string str, Node * sceneNode)
{
	Node *toastLayerNode = CommonFunction::getNodeChildByTag(sceneNode, TOAST_LAYER_TAG);
	if (toastLayerNode == NULL)
	{
		m_scene = sceneNode;

		creatToastLayer();
		m_ToastLayer->setTag(TOAST_LAYER_TAG);
		sceneNode->addChild(m_ToastLayer, 1000);
	}

	m_ToastLayer->addLayer(str);
}

void  ToastManger::creatToastLayer()
{
	m_ToastLayer = ToastLayer::create();
}