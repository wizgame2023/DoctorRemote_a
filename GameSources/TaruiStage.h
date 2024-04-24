/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class TaruiGameStage : public Stage
	{
		void CreateViewLight();
		void CreateEnemy();
		void CreateWall();

	public:
		TaruiGameStage() :Stage() {}
		virtual ~TaruiGameStage() {}
		virtual void OnCreate()override;
	};

}
//end namespace basecross

