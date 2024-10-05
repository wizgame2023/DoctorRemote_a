/*!
@file BigPiece.cpp
@brief 大きい欠片の実装
担当：逸見
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
		m_status(0),
		m_hp(12),
		m_littlePieceNum(6),
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
		m_status(0),
		m_hp(12),
		m_littlePieceNum(6),
		m_littlePieceFlag(littlePieceFlag),
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
			m_effectName = L"BigPieceEffectPurple2";
		}
		if (m_var == 2)
		{
			m_meshResName = L"Kakera_Mesh4";
			m_effectName = L"BigPieceEffectPurple2-1";
		}
		if (m_var == 3)
		{
			m_meshResName = L"Kakera_Mesh5";
			m_effectName = L"BigPieceEffectPurple2-2";

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
		colPtr->SetDrawActive(false);
		colPtr->SetAfterCollision(AfterCollision::None);
		colPtr->SetFixed(false);
		
		//ステータス
		auto scene = App::GetApp()->GetScene<Scene>();
		m_status = scene->GetBigPieceUp();

		AddTag(L"BigPiece");

		m_littlePieceNum = App::GetApp()->GetScene<Scene>()->GetBigPieceUp();

	}
	void BigPiece::OnUpdate() {
		auto stage = GetStage();
		float elapsed = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsed);
		m_trans = GetComponent<Transform>();
		m_trans->SetScale(m_scale);

		auto StageFlag = stage->GetSharedGameObject<StageManager>(L"StageManager")->GetStageFlag();
		if (StageFlag >= 3&&GetThis<BigPiece>()->FindTag(L"fieldBigPiece"))//StageFlagが敵を倒していた時の進行度の時
		{
			stage->RemoveGameObject<BigPiece>(GetThis < BigPiece>());//自分を消去する
			//自分自身(BigPiece)がいなくなることを伝える
			GetStage()->GetSharedGameObject<MiniMapBigPiece>(m_myMiniMapName)->SetExistence(false);
		}

	}

	void BigPiece::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");

		if (other->FindTag(L"Bullet")) {
			m_bullet = dynamic_pointer_cast<Bullet>(other);
			if (m_enemyDeletFlag) return;
			if (m_hp > 0) {
				m_hp -= m_bullet.lock()->GetAttack();
			}
			if (m_hp <= 0) {
				//欠片をまき散らす
				if (m_littlePieceFlag) {
					//自分自身(BigPiece)がいなくなることを伝える
					GetStage()->GetSharedGameObject<MiniMapBigPiece>(m_myMiniMapName)->SetExistence(false);
					//欠片の生成
					ScatterDestroy(m_littlePieceNum);

				}
				else {
					ScatterDestroy(0);
				}

			}


			//m_enemyDeletFlag = true;

			//効果音
			auto pieceSE = App::GetApp()->GetXAudio2Manager();
			pieceSE->Start(L"BreakSE", 0, 4.5f);

			auto PtrEffect = GetStage()->GetSharedGameObject<Effect>(L"Effect", false);
			PtrEffect = GetStage()->GetSharedGameObject<EffectMove>(m_effectName, false);
			PtrEffect->InsertEffect(GetComponent<Transform>()->GetPosition() - Vec3(0.0f, 1.0f, 0.0f));


		}
		if (other->FindTag(L"Player")) {
			auto stageManager = GetStage()->GetSharedGameObject<StageManager>(L"StageManager");
			stageManager->SetHp(-20.0f);
		}
		if (other->FindTag(L"Ground")) {
			m_ground = true;
		}
	}

	void BigPiece::ScatterDestroy(int littleNum, bool des) {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		if (littleNum > 0) {
			for (int i = 0; i < littleNum; i++) {
				stage->AddGameObject<PieceLittle>(GetThis<BigPiece>(), player, (360 / littleNum) * i, L"BigPieceLittle");
			}
		}
		if (des) {
			stage->RemoveGameObject<BigPiece>(GetThis < BigPiece>());
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
			auto pos = ptrTrans->GetPosition();
			ptrTrans->SetPosition(Vec3(pos.x, 0.0f, pos.z));

		}

	}


	void BigPiece::MyMiniMapName(wstring Name)
	{
		m_myMiniMapName = Name;
	}

}
//end namespace basecross