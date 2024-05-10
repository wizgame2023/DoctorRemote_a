/*!
@file EffectBreakWall.h
@brief ゲームステージ
担当　三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EffectBreakWall : public Effect
	{
	private:
	public:
		EffectBreakWall(shared_ptr<Stage>& Stageptr, wstring TextureName, float maxTime, int addNumber, Vec3 pushPos = Vec3(1.0f, 1.0f, 1.0f), Vec3 Scale = Vec3(1.0f, 1.0f, 1.0f));
		~EffectBreakWall() override;

		//virtual void InsertEffect(const Vec3& Pos) override;

	};
}