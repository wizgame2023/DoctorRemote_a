/*!
@file StageManagar.h
@brief ステージ全体の処理等
担当：
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageManager :public GameObject {
	private:
		float m_currentHp;
		float m_maxHp;
		float m_hpSpeed;

	public:
		StageManager(const shared_ptr<Stage>& stagePtr);
		virtual ~StageManager(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		float GetHp();
		float GetHpRatio();
		void SetHp(float hp);

	};
}
//end namespace basecross