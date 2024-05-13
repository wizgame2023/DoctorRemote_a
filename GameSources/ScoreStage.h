/*!
@file ScoreStage.h
@brief スコアステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ScoreStage :public Stage
	{
		void CreateViewLight();
	public:
		ScoreStage() :Stage() {}
		virtual ~ScoreStage() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void StageChange();
	};
}
