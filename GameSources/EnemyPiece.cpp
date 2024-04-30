/*!
@file EnemyPiece.cpp
@brief 敵の欠片実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	EnemyPiece::EnemyPiece(const shared_ptr<Stage>& StagePtr,
		const Vec3& position,
		const Vec3& rotate,
		const Vec3& scale
		) :
		GameObject(StagePtr),
		m_position(position),
		m_rotate(rotate),
		m_scale(scale),
		m_meshResName(L"DEFAULT_CUBE")

	{}
	EnemyPiece::~EnemyPiece() {};

	void EnemyPiece::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rotate);
		ptrTrans->SetPosition(m_position);

		//オブジェクトの描画
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(m_meshResName);
		ptrDraw->SetOwnShadowActive(true);
		//ptrDraw->SetTextureResource(L"");
		
		//オブジェクトの影の描画
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(m_meshResName);

		//コライダー
		auto colPtr = AddComponent<CollisionObb>();
		colPtr->SetDrawActive(true);
		colPtr->SetAfterCollision(AfterCollision::None);

		AddTag(L"EnemyPiece");
	}

	void EnemyPiece::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player")){
			//自分自身を廃棄する
			GetStage()->RemoveGameObject<EnemyPiece>(GetThis<EnemyPiece>());

		}
	}
	Vec3 EnemyPiece::GetPos() {
		return m_position;
	}
	Vec3 EnemyPiece::GetRot() {
		return m_rotate;
	}
}
//end basecross
