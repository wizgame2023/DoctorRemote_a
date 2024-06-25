/*!
@file TitleStage.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleStage :public Stage
	{
		float m_blinking = 0;
		void CreateViewLight();
	public:
		TitleStage() :Stage(){}
			virtual ~TitleStage() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void StageChange();
	};
}