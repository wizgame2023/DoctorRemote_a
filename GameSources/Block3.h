/*!
@file Block.h
@brief ブロックのオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Block3 : public GameObject
	{
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;
	public:
		Block3(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot, const Vec3& scale);
		~Block3() {}
		virtual void OnCreate() override;

	};

}
