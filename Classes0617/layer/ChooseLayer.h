#pragma once

#include "cocos2d.h"
#include "ui/UIButton.h"

using namespace cocos2d;
using namespace ui;

/*
菜单选择层
*/

class ChooseLayer :public Layer
{
public:

	ChooseLayer();
	~ChooseLayer();

	virtual bool init();
	CREATE_FUNC(ChooseLayer);
	virtual void onEnter();

public:
	void setBtnEnable(int index);

private:

	void initData();
	void initUI();

private:
	void chiBtnCbk(Ref* psender);
	void pengBtnCbk(Ref* psender);
	void huBtnCbk(Ref* psender);
	void closeBtnCbk(Ref* psender);

	void close();

private:
	Button* m_chi_btn;
	Button* m_peng_btn;
	Button* m_hu_btn;
	Button* m_close_btn;
};

