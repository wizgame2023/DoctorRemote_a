/*!
@file GameOverStage.h
@brief ゲームオーバーステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GameOverStage :public Stage {
		void CreateViewLight();

	public:
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void StageChange();


	};
}
//end namespace basecross

