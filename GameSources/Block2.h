/*!
@file Block.h
@brief ブロックのオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BlockSecond : public GameObject
	{
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
	public:
		BlockSecond(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot, const Vec3& scale);
		~BlockSecond() {}
		virtual void OnCreate() override;
		//virtual void OnUpdate() override;

	};
}
//end namespace basecross