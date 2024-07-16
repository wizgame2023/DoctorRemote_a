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
		virtual void OnDestroy() override;
		void ResetButton();

		shared_ptr<SoundItem> m_BGM;

		void BaseBGM();
	};
}