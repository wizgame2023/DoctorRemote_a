/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	FakePiece::FakePiece(const shared_ptr<Stage>& StagePtr,
		const Vec3& scale,
		const Quat& qt,
		const Vec3& position
	):
		GameObject(StagePtr),
		m_scale(scale),
		m_qt(qt),
		m_position(position),
		m_meshResName(L"DEFAULT_CUBE")
	{}

	void FakePiece::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetQuaternion(m_qt);
		ptrTrans->SetPosition(m_position);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(m_meshResName);
		ptrDraw->SetOwnShadowActive(true);

		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_meshResName);

		auto ptrCol = AddComponent<CollisionObb>();
		ptrCol->SetDrawActive(true);
		ptrCol->SetAfterCollision(AfterCollision::None);

		AddTag(L"FakePiece");

	}

	void FakePiece::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player")) {

		}
	}

}
//end basecross
