/*!
@file TutorialManager.cpp
@brief チュートリアルの管理実体
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"

namespace basecross {
	class ToturialManager :public GameObject {
	private:
		float m_blinking;
		float m_blinking2;

		int m_count;

		bool m_textutreCheck;
		bool m_blinkFlag;
		bool m_comFrameFlag;

		shared_ptr<Sprite> m_triDot[10];
		shared_ptr<Sprite> m_bButton;
		shared_ptr<CommentManager> m_com[10];


	public:
		ToturialManager(const shared_ptr<Stage>& stagePtr);
		virtual ~ToturialManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}