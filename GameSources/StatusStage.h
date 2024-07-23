/*!
@file StatusStage.h
@brief ステータスステージ
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"

namespace basecross {
	class StatusStage :public Stage {

		float m_blinking;
		void CreateViewLight(); //ビューの作成

		shared_ptr<Sprite> m_moji[6];
		

	public:
		StatusStage() :Stage() {}
		virtual ~StatusStage(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
