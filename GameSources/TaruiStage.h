/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class T_GameStage : public Stage
	{
		void CreateViewLight();
		void CreateEnemy();

	public:
		T_GameStage() :Stage() {}
		~T_GameStage() {}
		virtual void OnCreate()override;
	};

}
//end namespace basecross

