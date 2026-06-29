/*!
@file EffectCgase.h
@brief ゲームステージ
担当　三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EffectChase : public EffectMove
	{
	private:

	public:
		EffectChase(shared_ptr<Stage>& Stageptr, wstring TextureName, float maxTime, int addNumber,float lenght, Vec3 pushPos = Vec3(1.0f, 1.0f, 1.0f), Vec3 Scale = Vec3(1.0f, 1.0f, 1.0f));
		~EffectChase() override;

		void OnUpdate() override;
		//void InsertEffect(const Vec3& Pos) override;

	};

}