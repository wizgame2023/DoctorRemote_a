/*!
@file ScoreStage.h
@brief スコアステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ScoreStage :public Stage
	{
		int m_time;
		int m_timeCount = 0;
		int m_count = 0;
		int m_moveCount = -400;
		float m_countUp = 0.0f;
		int m_stageCount;

		float m_mojiCount = 4.0;
		void CreateViewLight();
	public:
		ScoreStage() :Stage() {}

		virtual ~ScoreStage() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void StageChange();
	};
}
