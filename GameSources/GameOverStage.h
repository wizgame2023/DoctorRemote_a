/*!
@file GameOverStage.h
@brief ゲームオーバーステージ
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameOverStage :public Stage {
		int m_count;
		float m_buttonTime = 3.0f;
		bool m_buttonFlag = false;
		bool m_buttonSEFlag = false;
		void CreateViewLight();


	public:
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		shared_ptr<SoundItem> m_BGM;
		
		void BaseBGM();
		void StageChange();
	};
}
//end namespace basecross

