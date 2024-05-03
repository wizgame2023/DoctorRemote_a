/*!
@file BigPiece.cpp
@brief ‘å‚«‚¢Œ‡•Ğ‚ÌÀ‘•
’S“–FˆíŒ©
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BigPiece :public GameObject {
	private:
		Vec3 m_scale;
		Vec3 m_rotate;
		Vec3 m_position;
		wstring m_meshResName;

	public:
		BigPiece(const shared_ptr<Stage>& stagePtr,
			const Vec3& position,
			const Vec3& rotate,
			const Vec3 scale
		);
		virtual ~BigPiece() {}

		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

	};
}
//end namespace basecaross