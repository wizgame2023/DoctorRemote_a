/*!
@file StartStage.h
@brief スタートステージ
担当：ちなみ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StartStage :public Stage {

		void CreateViewLight();

	public:
		StartStage():Stage(){}
		virtual ~StartStage(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void StageChange();
	};
}
//end namespace basecross
