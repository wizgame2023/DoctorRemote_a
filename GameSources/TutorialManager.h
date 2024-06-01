/*!
@file TutorialManager.cpp
@brief チュートリアルの管理実体
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "StageManager.h"

namespace basecross {
	class TutorialManager :public GameObject {
	private:
		float m_blinking;
		float m_blinking2;

		int m_count;

		bool m_textutreCheck;
		bool m_blinkFlag;
		bool m_comFrameFlag;
		bool m_startFlag;

		shared_ptr<Sprite> m_triDot[10];
		shared_ptr<Sprite> m_bButton;
		shared_ptr<CommentManager> m_com[10];
		shared_ptr<StageManager> m_stageManager;


	public:
		TutorialManager(const shared_ptr<Stage>& stagePtr);
		virtual ~TutorialManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void Comment(int moji, wstring mesh,bool delet,bool delet2);
		void UIComment(int moji, wstring mesh, Vec3 triPos, float deg,bool delet,bool delte2);
	};
}