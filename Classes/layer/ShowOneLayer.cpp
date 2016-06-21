#include "ShowOneLayer.h"
#include "GameLayer.h"
#include "ShowCard.h"
#include "utils/CommonFunction.h"

ShowOneLayer::ShowOneLayer()
{

}

ShowOneLayer::~ShowOneLayer()
{

}

ShowOneLayer* ShowOneLayer::create(GameLayer* _layer)
{
	ShowOneLayer* ret = new ShowOneLayer();
	if (ret && ret->init(_layer))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool ShowOneLayer::init(GameLayer* _layer)
{
	if (!Layer::init())
	{
		return false;
	}

	m_GameLayer = _layer;

	initData();

	initUI();

	return true;
}

void ShowOneLayer::initData()
{

}

void ShowOneLayer::initUI()
{

}

void ShowOneLayer::showPengCard()
{
	if (m_tmpPengCardVec.size()>0)
	{
		for (auto &_card : m_tmpPengCardVec)
		{
			if (_card->getParent())
			{
				_card->removeFromParent();
			}
		}
		m_tmpPengCardVec.clear();
	}

	std::vector<int > _pengList[2];
	_pengList[0] = m_GameLayer->t_Player[1].m_PengCardVec[0];
	_pengList[1] = m_GameLayer->t_Player[1].m_PengCardVec[1];

	if (_pengList[0].size()>0)
	{
		for (int i = 0; i < _pengList[0].size(); i++)
		{
			auto _card = ShowCard::create(0, _pengList[0][i]);
			if (_card)
			{
				addChild(_card);
				m_tmpPengCardVec.pushBack(_card);
			}
		}
	}

	if (_pengList[1].size()>0)
	{
		for (int i = 0; i < _pengList[1].size(); i++)
		{
			auto _card = ShowCard::create(1, _pengList[1][i]);
			if (_card)
			{
				addChild(_card);
				m_tmpPengCardVec.pushBack(_card);
			}
		}
	}

	if (m_tmpPengCardVec.size()>0)
	{
		for (int i = 0; i < m_tmpPengCardVec.size(); i++)
		{
			int _height = m_tmpPengCardVec.at(i)->getContentSize().height;
			m_tmpPengCardVec.at(i)->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2((i / 3)*(_height - 8) + 50, i % 3 * (_height - 70) - 60)));
		}
	}
	refrishCardPos();
}

void ShowOneLayer::showKaiduoCard()
{

}

void ShowOneLayer::showSaochuanCard()
{

}

void ShowOneLayer::showSaoCard()
{

}

void ShowOneLayer::showChiCard()
{

}

void ShowOneLayer::refrishCardPos()
{
	if (!m_ThreeCardVec.empty())
	{
		m_ThreeCardVec.clear();
	}

	if (!m_FourCardVec.empty())
	{
		m_FourCardVec.clear();
	}

	m_ThreeCardVec.pushBack(m_tmpPengCardVec);
	m_ThreeCardVec.pushBack(m_tmpSaoCardVec);
	m_ThreeCardVec.pushBack(m_tmpChiCardVec);

	m_FourCardVec.pushBack(m_tmpKaiDuoCardVec);
	m_FourCardVec.pushBack(m_tmpSaoChuanCardVec);

	if (!m_ThreeCardVec.empty())
	{
		for (int i = 0; i < m_ThreeCardVec.size(); i++)
		{
			auto _card = m_ThreeCardVec.at(i);
			auto _height = _card->getContentSize().height;
			_card->setPosition(CommonFunction::getVisibleAchor(Anchor::Center, Vec2((i / 3)*(_height - 8) + 450, i % 3 * (_height - 70)+ 170)));
		}

		if (!m_ThreeCardVec.empty())
		{
			for (int i = 0; i < m_FourCardVec.size(); i++)
			{
				auto _card = m_FourCardVec.at(i);
				auto _height = _card->getContentSize().height;
				_card->setPosition(CommonFunction::getVisibleAchor(Anchor::RightMid, Vec2((i / 4)*(_height - 8) + m_ThreeCardVec.back()->getPosition().x + _height, i % 4 * (_height - 70) - 30)));
			}
		}
	}
}