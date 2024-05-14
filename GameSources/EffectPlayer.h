/*!
@file EffectBullet.h
@brief 弾の当たった時のエフェクト
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EffectPlayer : public Effect
	{
	private:
		float m_length;

	public:
		EffectPlayer(shared_ptr<Stage>& Stageptr, wstring TextureName, float maxTime, int addNumber,float lenght, Vec3 pushPos = Vec3(1.0f, 1.0f, 1.0f), Vec3 Scale = Vec3(1.0f, 1.0f, 1.0f));
		~EffectPlayer() override;

		virtual void InsertEffect(const Vec3& Pos) override;

	};

}