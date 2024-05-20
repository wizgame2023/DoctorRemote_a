/*!
@file BigPiece.cpp
@brief 大きい欠片の実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BigPiece::BigPiece(const shared_ptr<Stage>& stagePtr,
		const Vec3& position,
		const Vec3& rotate,
		const Vec3 scale
		) :
		GameObject(stagePtr),
		m_position(position),
		m_rotate(rotate),
		m_scale(scale),
		m_meshResName(L"Kakera_Mesh3")
	{}

	void BigPiece::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rotate);
		ptrTrans->SetPosition(m_position);

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//オブジェクトの描画
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(m_meshResName);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->AddAnimation(L"Default", 0, 90, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");


		//オブジェクトの影の描画
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_meshResName);
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//コライダー
		auto colPtr = AddComponent<CollisionObb>();
		colPtr->SetDrawActive(true);
		colPtr->SetAfterCollision(AfterCollision::None);

		AddTag(L"BigPiece");

	}
	void BigPiece::OnUpdate() {
		float elapsed = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsed);
	}

	void BigPiece::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player")) {
			//自分自身を廃棄する
			GetStage()->RemoveGameObject<BigPiece>(GetThis<BigPiece>());

		}
	}

}
//end namespace basecross