/*!
@file ClearStage.h
@brief クリアステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class LoadStage :public Stage {

		void CreateViewLight();

	public:
		LoadStage() :Stage() {}
		virtual ~LoadStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void StageChange();
	};

}
