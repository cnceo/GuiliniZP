#include "SoundEffect.h"
#include "SimpleAudioEngine.h"

#define AUDIOENGIN	CocosDenshion::SimpleAudioEngine::getInstance()

Audio* Audio::m_instance = nullptr;

Audio* Audio::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::prepare()
{
	//AUDIOENGIN->preloadBackgroundMusic("");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/GX_N/gx_n_bi.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/GX_N/gx_n_chi.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/GX_N/gx_n_guosao.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/GX_N/gx_n_hu.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/GX_N/gx_n_kaiduo.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/GX_N/gx_n_peng.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/GX_N/gx_n_sao.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/GX_N/gx_n_saochuan.mp3");

	AUDIOENGIN->preloadEffect("music/both_action/boy_action/PT_N/pt_n_bi.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/PT_N/pt_n_chi.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/PT_N/pt_n_guosao.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/PT_N/pt_n_hu.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/PT_N/pt_n_kaiduo.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/PT_N/pt_n_peng.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/PT_N/pt_n_sao.mp3");
	AUDIOENGIN->preloadEffect("music/both_action/boy_action/PT_N/pt_n_saochuan.mp3");

	AUDIOENGIN->preloadEffect("music/girl_action/gx_n_moHu_1.mp3");
	AUDIOENGIN->preloadEffect("music/girl_action/gx_v_moHu.mp3");
	AUDIOENGIN->preloadEffect("music/girl_action/pt_n_mohu.mp3");
	AUDIOENGIN->preloadEffect("music/girl_action/pt_v_mohu.mp3");

	AUDIOENGIN->preloadEffect("music/girl_action/GX_V/gx_v_bi.mp3");
	AUDIOENGIN->preloadEffect("music/girl_action/GX_V/gx_v_chi.mp3");
	AUDIOENGIN->preloadEffect("music/girl_action/GX_V/gx_v_guosao.mp3");
	AUDIOENGIN->preloadEffect("music/girl_action/GX_V/gx_v_hu.mp3");
	AUDIOENGIN->preloadEffect("music/girl_action/GX_V/gx_v_kaiduo.mp3");
	AUDIOENGIN->preloadEffect("music/girl_action/GX_V/gx_v_peng.mp3");
	AUDIOENGIN->preloadEffect("music/girl_action/GX_V/gx_v_sao.mp3");
	AUDIOENGIN->preloadEffect("music/girl_action/GX_V/gx_v_saochuan.mp3");

}