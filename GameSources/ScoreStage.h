/*!
@file ScoreStage.h
@brief スコアステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ScoreStage :public Stage
	{
		int m_time;//ステージクリアした時の残りタイムを格納する変数
		float m_countUp = 0.0f;//スコアステージが生成されてから何秒経ったかを表す変数
		int m_timeCount = 0;//if文に「m_countUp」を何回使ったかを表す変数
		int m_control = 0;//「OnUpdate」の中で１回しか通さないように制御する変数
		int m_stageCount;

		int m_achievementPoint;
		int m_apReceive;

		float m_mojispeed;
		float m_mojispeed1;

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
