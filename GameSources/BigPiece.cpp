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
		const Vec3 scale,
		int var
		) :
		GameObject(stagePtr),
		m_position(position),
		m_rotate(rotate),
		m_scale(scale),
		m_var(var),
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

		if (m_var == 1)
		{
			m_meshResName = L"Kakera_Mesh3";
		}
		if (m_var == 2)
		{
			m_meshResName = L"Kakera_Mesh4";
		}
		if (m_var == 3)
		{
			m_meshResName = L"Kakera_Mesh5";
		}
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
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		if (other->FindTag(L"Bullet")) {
			GetStage()->GetSharedGameObject<MiniMapBigPiece>(m_myMiniMapName)->SetExistence(false);//自分自身(BigPiece)がいなくなることを伝える
			auto pieceSE = App::GetApp()->GetXAudio2Manager();
			pieceSE->Start(L"PieceDownSE", 0, 0.5f);
			//自分自身を廃棄する
			GetStage()->RemoveGameObject<BigPiece>(GetThis<BigPiece>());
			stage->AddGameObject<PieceLittle>(other, player, 0.0f);
			stage->AddGameObject<PieceLittle>(other, player, 45.0f);
			stage->AddGameObject<PieceLittle>(other, player, 45.0f * 2);
			stage->AddGameObject<PieceLittle>(other, player, 45.0f * 3);
			stage->AddGameObject<PieceLittle>(other, player, 45.0f * 4);
			stage->AddGameObject<PieceLittle>(other, player, 45.0f * 5);
			stage->AddGameObject<PieceLittle>(other, player, 45.0f * 6);
			stage->AddGameObject<PieceLittle>(other, player, 45.0f * 7);
			stage->AddGameObject<PieceLittle>(other, player, 45.0f * 8);

		}
		if (other->FindTag(L"Player")) {
			auto stageManager = GetStage()->GetSharedGameObject<StageManager>(L"StageManager");
			stageManager->SetHp(-20.0f);
		}
	}

	void BigPiece::MyMiniMapName(wstring Name)
	{
		m_myMiniMapName = Name;
	}

}
//end namespace basecross