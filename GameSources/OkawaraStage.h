/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class O_GameStage :public Stage
	{
		void CreateViewLight();
		void CreateEnemy();

	public:
		O_GameStage() :Stage(){}
		~O_GameStage() {}
		virtual void OnCreate()override;

	};
}
//end namespace basecross

