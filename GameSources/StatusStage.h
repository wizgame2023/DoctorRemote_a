/*!
@file StatusStage.h
@brief ステータスステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StatusStage :public Stage {

		void CreateViewLight(); //ビューの作成


	public:
		StatusStage() :Stage() {}
		virtual ~StatusStage(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
