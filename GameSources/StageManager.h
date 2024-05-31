/*!
@file StageManagar.h
@brief ã‚¹ãƒ†ãƒ¼ã‚¸å…¨ä½“ã®å‡¦ç†ç­‰
æ‹…å½“ï¼šé€¸è¦‹
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "UITime.h"

namespace basecross {
	class StageManager :public GameObject {
	private:
		float m_currentHp;
		float m_maxHp;
		float m_hpSpeed;
		float m_count;
		float m_countStart;
		float m_comX;

		int m_ligthStatus;
		int m_stageFlag;//ƒXƒe[ƒW‘S‘Ì‚Ìƒtƒ‰ƒO
		bool m_start;

		bool m_cfFlag;
		bool m_comFlag;
		bool m_countFlag;


		shared_ptr<Sprite> m_ligth;
		shared_ptr<Sprite> m_startSprite;
		shared_ptr<UITime> m_num;
		shared_ptr<Sprite> m_comFrame;
		shared_ptr<Transform> m_comTrans;

	public:
		StageManager(const shared_ptr<Stage>& stagePtr);
		virtual ~StageManager(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		float GetHp();
		float GetHpRatio();
		void SetHp(float hp);
		void SetCountFlag(bool OnOff);
		void SetStageFlag(int Flag);
		int GetStageFlag();
		bool StartFlag();
	};
}
//end namespace basecross