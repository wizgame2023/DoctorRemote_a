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
		m_enemyDeletFlag(0),
		m_meshResName(L"Kakera_Mesh")

	{}

	void EnemyPiece::OnCreate() {
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
		colPtr->SetAfterCollision(AfterCollision::Auto);

		AddTag(L"EnemyPiece");
	}

	void EnemyPiece::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);
	}

	void EnemyPiece::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		if (other->FindTag(L"Bullet")){
			auto pieceSE = App::GetApp()->GetXAudio2Manager();
			pieceSE->Start(L"PieceDownSE", 0, 0.5f);//SEはじめ
			//自分自身を廃棄する
			stage->RemoveGameObject<EnemyPiece>(GetThis<EnemyPiece>());
			stage->AddGameObject<PieceLittle>(other,player, 0.0f);
			stage->AddGameObject<PieceLittle>(other,player, 72.0f);
			stage->AddGameObject<PieceLittle>(other,player, 72.0f * 2);
			stage->AddGameObject<PieceLittle>(other,player, 72.0f * 3);
			stage->AddGameObject<PieceLittle>(other,player, 72.0f * 4);	
			m_enemyDeletFlag++;
		}
		if (other->FindTag(L"Player")) {
			stageManager->SetHp(-10.0f);
		}
	}
	Vec3 EnemyPiece::GetPos() {
		return m_position;
	}
	Vec3 EnemyPiece::GetRot() {
		return m_rotate;
	}
	int EnemyPiece::GetDeletFlag() {
		return m_enemyDeletFlag;
	}
}
//end basecross
