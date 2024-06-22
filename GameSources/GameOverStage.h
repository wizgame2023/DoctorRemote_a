/*!
@file GameOverStage.h
@brief ゲームオーバーステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameOverStage :public Stage {
		void CreateViewLight();
		int m_count;

	public:
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

		void StageChange();
	};
}
//end namespace basecross

