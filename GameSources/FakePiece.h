/*!
@file GameStage.h
@brief ゲームステージ
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class FakePiece :public GameObject {

	private:
		Vec3 m_scale;
		Quat m_qt;
		Vec3 m_position;
		wstring m_meshResName;

	public:
		FakePiece(const shared_ptr<Stage>& StagePtr,
			const Vec3& scale,
			const Quat& qt,
			const Vec3& position);
		virtual ~FakePiece(){}

		virtual void OnCreate() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
//end namespace basecross