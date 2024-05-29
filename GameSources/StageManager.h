/*!
@file StageManagar.h
@brief ステージ全体の処理等
担当：逸見
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

		int m_ligthStatus;
		bool m_start;

		shared_ptr<Sprite> m_ligth;
		shared_ptr<Sprite> m_startSprite;
		shared_ptr<UITime> m_num;

	public:
		StageManager(const shared_ptr<Stage>& stagePtr);
		virtual ~StageManager(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		float GetHp();
		float GetHpRatio();
		void SetHp(float hp);
		bool StartFlag();
	};
}
//end namespace basecross