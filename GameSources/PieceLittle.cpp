/*!
@file PieceLittle.cpp
@brief 欠片を壊したらでてくるオブジェクト
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	PieceLittle::PieceLittle(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_position(Vec3(0.0f,0.5,0.0f)),
		m_rotete(Vec3(0.0f)),
		m_scale(Vec3(0.5f)),
		m_meshResName(L"DEFAULT_SPHERE")
	{}

	void PieceLittle::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(m_position);
		ptrTrans->SetRotation(m_rotete);
		ptrTrans->SetScale(m_scale);

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(m_meshResName);

		//オブジェクトの影の描画
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_meshResName);
		ptrDraw->SetOwnShadowActive(true);

		//コライダー
		auto colPtr = AddComponent<CollisionSphere>();
		colPtr->SetDrawActive(false);
		colPtr->SetAfterCollision(AfterCollision::None);

		AddTag(L"PieceLittle");

	}

	void PieceLittle::OnUpdate() {

	}

	void PieceLittle::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player")) {
			GetStage()->RemoveGameObject<PieceLittle>(GetThis<PieceLittle>());
		}

	}

}
//end namespace basecross