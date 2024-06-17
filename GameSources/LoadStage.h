/*!
@file ClearStage.h
@brief ロードステージ
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "Comment.h"

namespace basecross {
	class LoadStage :public Stage {

		int m_time;
		int m_timeCount = 0;
		int m_count = 0;
		int m_moveCount = -400;
		float m_countUp = 0.0f;
		float m_comX;
		bool m_flag;
		int m_stageCount;

		shared_ptr<Sprite>m_sprite;
		shared_ptr<Comment>m_comment;

		void CreateViewLight();

		

	public:
		LoadStage() :Stage() {}
		virtual ~LoadStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void StageChange();
	};

}
