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
		m_pieceDeleteTime(scale.x * 0.15f),
		m_littlePieceFlag(true),
		m_enemyDeletFlag(false),
		m_meshResName(L"Kakera_Mesh3")
	{}
	BigPiece::BigPiece(const shared_ptr<Stage>& stagePtr,
		const Vec3& position,
		const Vec3& rotate,
		const Vec3 scale,
		const bool littlePieceFlag,
		const int var
	) :
		GameObject(stagePtr),
		m_position(position),
		m_rotate(rotate),
		m_scale(scale),
		m_var(var),
		m_littlePieceFlag(littlePieceFlag),
		m_pieceDeleteTime(scale.x *0.15f),
		m_enemyDeletFlag(false),
		m_meshResName(L"Kakera_Mesh3")
	{}


	void BigPiece::OnCreate() {
		m_trans = GetComponent<Transform>();
		m_trans->SetScale(m_scale);
		m_trans->SetRotation(m_rotate);
		m_trans->SetPosition(m_position);

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.3f, 0.0f)
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
		auto colPtr = AddComponent<CollisionSphere>();
		colPtr->SetDrawActive(true);
		colPtr->SetAfterCollision(AfterCollision::None);
		colPtr->SetFixed(false);

		AddTag(L"BigPiece");

	}
	void BigPiece::OnUpdate() {
		auto stage = GetStage();
		float elapsed = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsed);
		m_trans = GetComponent<Transform>();
		m_trans->SetScale(m_scale);

		//時間差で小さくして消す
		if (m_enemyDeletFlag) {
			m_pieceDeleteTime -= elapsed;
			m_scale -= 2.0f * elapsed * 3.0f;
			if (m_pieceDeleteTime < 0) {
				//自分自身を廃棄する
				stage->RemoveGameObject<BigPiece>(GetThis<BigPiece>());
				m_enemyDeletFlag = false;
			}

		}

		//if (m_trans->GetPosition().y < 0.1f) {
		//	m_ground = true;

		//}

	}

	void BigPiece::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");

		if (other->FindTag(L"Bullet")) {
			if (m_enemyDeletFlag) return;
			//欠片の生成
			if (m_littlePieceFlag) {
				GetStage()->GetSharedGameObject<MiniMapBigPiece>(m_myMiniMapName)->SetExistence(false);//自分自身(BigPiece)がいなくなることを伝える
				stage->AddGameObject<PieceLittle>(other, player, 0.0f);
				stage->AddGameObject<PieceLittle>(other, player, 40.0f);
				stage->AddGameObject<PieceLittle>(other, player, 40.0f * 2);
				stage->AddGameObject<PieceLittle>(other, player, 40.0f * 3);
				stage->AddGameObject<PieceLittle>(other, player, 40.0f * 4);
				stage->AddGameObject<PieceLittle>(other, player, 40.0f * 5);
				stage->AddGameObject<PieceLittle>(other, player, 40.0f * 6);
				stage->AddGameObject<PieceLittle>(other, player, 40.0f * 7);
				stage->AddGameObject<PieceLittle>(other, player, 40.0f * 8);
				//stage->AddGameObject<PieceLittle>(other, player, 45.0f * 9);

			}
			m_enemyDeletFlag = true;

			//効果音
			auto pieceSE = App::GetApp()->GetXAudio2Manager();
			pieceSE->Start(L"PieceDownSE", 0, 0.5f);

		}
		if (other->FindTag(L"Player")) {
			auto stageManager = GetStage()->GetSharedGameObject<StageManager>(L"StageManager");
			stageManager->SetHp(-20.0f);
		}
		if (other->FindTag(L"Ground")) {
			m_ground = true;
		}
	}

	void BigPiece::Event(float deg,float power) {
		auto grav = AddComponent<Gravity>();
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();

		//落ちてくる高さ
		pos.y += 5.0f;
		Quat qt = ptrTrans->GetQuaternion();
		float rad = XMConvertToRadians(deg);

		Vec3 velo(sin(rad), 1.0f, cos(rad));
		velo *= power;
		m_velocity = velo;
		ptrTrans->SetPosition(pos);

	}
	void BigPiece::UpdateEvent() {
		//auto grav = GetComponent<Gravity>();
		auto elapsed = App::GetApp()->GetElapsedTime();
		auto ptrTrans = GetComponent<Transform>();
		if (!m_ground) {
			auto pos = ptrTrans->GetPosition();
			pos += m_velocity * elapsed;
			ptrTrans->SetPosition(pos);
		}
		else if (m_ground) {
			auto grav = GetComponent<Gravity>();
			grav->SetGravityZero();
		}

	}


	void BigPiece::MyMiniMapName(wstring Name)
	{
		m_myMiniMapName = Name;
	}

}
//end namespace basecross