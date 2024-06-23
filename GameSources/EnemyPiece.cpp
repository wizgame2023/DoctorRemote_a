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
		m_pieceDeletFlag(0),
		m_littlePieceFlag(littlePieceFlag),
		m_hp(6.0f),
		m_breakCount(0.0f),
		m_chainTime(1.0f),
		m_meshResName(L"Kakera_Mesh")

	{}

	void EnemyPiece::OnCreate() {
		auto stage = GetStage();
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


		AddTag(L"EnemyPiece");
	}

	void EnemyPiece::OnUpdate() {
		auto stage = GetStage();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsedTime);
		m_trans = GetComponent<Transform>();
		m_position = m_trans->GetPosition();
		m_trans->SetScale(m_scale);

		auto& pieces = PieceManager::enemyPieces;
		auto& breakPieces = PieceManager::breakPieces;

		//体力が0になっていないかみる
		if (m_hp <= 0) {
			m_breakCount -= elapsedTime;
			if (m_breakCount <= 0&&m_littlePieceFlag) {
				ScatterDestroy(3);
			}
			else if (m_breakCount <= 0 && !m_littlePieceFlag) {
				ScatterDestroy(0);
			}
		}

		//wstringstream wss;//デバック用文字列
		//wss << L"brekPiece[0] :" << PieceManager::breakPieces[0].size() << endl;
		//wss << L"brekPiece[1] :" << PieceManager::breakPieces[1].size() << endl;
		//wss << L"brekPiece[2] :" << PieceManager::breakPieces[2].size() << endl;
		//wss << L"brekPiece :" << PieceManager::breakPieces.size() << endl;
		//wss << L"Piece :" << PieceManager::enemyPieces.size() << endl;
		//wss << L"Count :" << m_breakCount << endl;
		//auto scene = App::GetApp()->GetScene<Scene>();//シーン取得
		//scene->SetDebugString(L"\n" + wss.str());
	}

	void EnemyPiece::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		if (other->FindTag(L"Bullet")){
			m_bullet = dynamic_pointer_cast<Bullet>(other);
			//欠片の体力
			if (m_hp > 0) {
				m_hp -= m_bullet.lock()->GetAttack();
			}
			if (m_hp <= 0) {
				m_pieceDeletFlag ++;
			}
			if (m_pieceDeletFlag == 1) {
				auto bulletLevel = m_bullet.lock()->GetBulletLevel();
				if (m_littlePieceFlag) {
					ScatterDestroy(3);
					ChainEffect(0.0f,(float)bulletLevel);
					PieceManager::PieceDistance(GetThis<EnemyPiece>(),m_bullet.lock());					
				}
				else {
					ScatterDestroy(0);
					ChainEffect(0.0f, (float)bulletLevel);
					PieceManager::PieceDistance(GetThis<EnemyPiece>(), m_bullet.lock());

				}
			}
			//m_pieceDeletFlag = true;
			//m_pieceDeletFlag++;
			
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

	//
	void EnemyPiece::DelDamage(int damage,float count) {
		m_breakCount = count;
		m_hp -= damage;

		if (m_hp < 0) {
			m_hp = 0;
		}
	}
	//小さい欠片を散らばせ、自分自身を消す
	void EnemyPiece::ScatterDestroy(int littleNum,bool des) {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		if (littleNum > 0) {
			for (int i = 0; i < littleNum; i++) {
				stage->AddGameObject<PieceLittle>(GetThis<EnemyPiece>(), player, (360 / littleNum) * i);
			}
		}
		if (des) {
			stage->RemoveGameObject<EnemyPiece>(GetThis<EnemyPiece>());
		}
	}

	//エフェクト
	void EnemyPiece::ChainEffect(float radius,float deleteTime){
		auto stage = GetStage();
		auto effect = m_effect.lock();
		effect = stage->AddGameObject<EffectPiece>();
		effect->SetUnderRadius(radius);
		effect->SetScrollSpeed(0.0f, 3.0f);
		effect->SetDeleteTime(deleteTime);
		auto effectTrans = effect->GetComponent<Transform>();
		effectTrans->SetPosition(m_position);
	}
	//ボスのイベント
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

	//ボスのイベントの更新処理
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
			auto pos=ptrTrans->GetPosition();
			ptrTrans->SetPosition(Vec3(pos.x, 0.0f, pos.z));
			
		}

	}

	Vec3 EnemyPiece::GetPos() {
		return m_position;
	}
	Vec3 EnemyPiece::GetRot() {
		return m_rotate;
	}
	int EnemyPiece::GetDeletFlag() {
		return m_pieceDeletFlag;
	}
	bool EnemyPiece::GetGroundFlag() {
		return m_ground;
	}
	
}

//end basecross
