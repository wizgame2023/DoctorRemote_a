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
		const Vec3& scale,
		const bool littlePieceFlag
		) :
		GameObject(StagePtr),
		m_position(position),
		m_rotate(rotate),
		m_scale(scale),
		m_enemyDeletFlag(0),
		m_pieceDeleteFlag(false),
		m_pieceDeleteTime(scale.x * 0.15f),
		m_littlePieceFlag(littlePieceFlag),
		m_meshResName(L"Kakera_Mesh")

	{}

	void EnemyPiece::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rotate);
		ptrTrans->SetPosition(m_position);

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.2f, 0.0f)
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
		auto colPtr = AddComponent<CollisionSphere>();
		colPtr->SetDrawActive(true);
		colPtr->SetAfterCollision(AfterCollision::None);
		colPtr->SetFixed(false);

		//auto grav = AddComponent<Gravity>();


		AddTag(L"EnemyPiece");
	}

	void EnemyPiece::OnUpdate() {
		auto stage = GetStage();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);
		m_trans = GetComponent<Transform>();
		m_trans->SetScale(m_scale);

		//時間差で消すためにFlagで見ている
		if (m_enemyDeletFlag) {
			m_pieceDeleteTime -= elapsedTime;
			m_scale -= 2.0f * elapsedTime * 3.0f;
			if (m_pieceDeleteTime < 0) {
				//自分自身を廃棄する
				stage->RemoveGameObject<EnemyPiece>(GetThis<EnemyPiece>());
				m_enemyDeletFlag = false;
			}

		}
	}

	void EnemyPiece::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		if (other->FindTag(L"Bullet")){
			//欠片をばらまく
			if (m_enemyDeletFlag) return;
			if (m_littlePieceFlag) {
				stage->AddGameObject<PieceLittle>(other,player, 0.0f);
				stage->AddGameObject<PieceLittle>(other,player, 72.0f);
				stage->AddGameObject<PieceLittle>(other,player, 72.0f * 2);
				stage->AddGameObject<PieceLittle>(other,player, 72.0f * 3);
				stage->AddGameObject<PieceLittle>(other,player, 72.0f * 4);	
			}
			m_enemyDeletFlag = true;
			//m_enemyDeletFlag++;
			
			//効果音
			auto pieceSE = App::GetApp()->GetXAudio2Manager();
			pieceSE->Start(L"PieceDownSE", 0, 0.5f);//SEはじめ
		}
		if (other->FindTag(L"Player")) {
			stageManager->SetHp(-10.0f);
		}
		if (other->FindTag(L"Ground")) {
			m_ground = true;
		}
	}

	void EnemyPiece::Event(float deg) {
		auto grav = AddComponent<Gravity>();
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();

		//auto bossTrans = m_boss->GetComponent<Transform>();
		//auto bossPos = bossTrans->GetPosition();

		//pos = bossPos;
		//落ちてくる高さ
		pos.y += 6.0f;
		Quat qt = ptrTrans->GetQuaternion();
		float rad = XMConvertToRadians(deg);

		Vec3 velo(sin(rad), 1.0f, cos(rad));
		velo *= 7.0f;
		m_velocity = velo;
		ptrTrans->SetPosition(pos);

	}
	void EnemyPiece::UpdateEvent() {
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
