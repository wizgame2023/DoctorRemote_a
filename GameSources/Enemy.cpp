/*!
@file Character.cpp
@brief 敵など実体
担当　逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_hp(10),
		m_posXFlag(1.0f),
		m_enemyflag(false),
		m_meshResName(L"Baikin_Mesh")
	{}
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, 
		const Vec3& pos, 
		const Vec3& rot, 
		const Vec3& scale
	) :
		GameObject(StagePtr),
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_originPos(pos),
		m_maxScale(scale),
		m_width(3.0f),
		m_widthSpeed(2.0f),
		m_hegiht(2.0f),
		m_hegihtSpeed(1.0f),
		m_scaleReduct(0.4f),//どれくらい小さくするか
		m_posYRedect(0.15f),//敵が小さくなる時に下げる高さ
		m_pieceTime(0.1f),
		m_bigPieceTime(0.5f),
		m_bigPieceTime2(0.2f),
		m_pieceCount(0),
		m_bigPieceCount(0),
		m_bigPieceCount2(0),
		m_posXFlag(false),
		m_posYFlag(false),
		m_enemyflag(false),
		m_pieceFlag(false),
		m_bigPieceFlag(false),
		m_bigPieceFlag2(false),
		m_event(false),
		m_event2(false),
		m_meshResName(L"Boss_Mesh"),
		m_hp(60),
		m_maxHp(60)
	{}

	void Enemy::OnCreate()
	{
		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(m_pos);
		m_trans->SetRotation(m_rot);
		m_trans->SetScale(m_scale);

		auto stage = GetStage();
		AddTag(L"Enemy");

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.2f, 0.2f, 0.2f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.3f, 0.0f)
		);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(m_meshResName);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->AddAnimation(L"Default", 0, 90, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");



		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(m_meshResName);
		shadowPtr->SetMeshToTransformMatrix(spanMat);

		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(false);
		//ptrColl->SetDrawActive(true);//コリジョンを見えるようにする


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

	}


	void Enemy::OnUpdate()
	{
		float elapsed = App::GetApp()->GetElapsedTime();
		auto stage = GetStage();
		//auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		//ptrDraw->UpdateAnimation(elapsed);

		//アニメーションの更新
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsed);

		
		m_trans = GetComponent<Transform>();
		m_posCur = m_trans->GetPosition();
		m_trans->SetScale(m_scale);
		m_player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		auto playerTrans = m_player->GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();
		auto eventPos = playerPos - m_posCur;
		auto eventLenght = sqrt(eventPos.x * eventPos.x + eventPos.z * eventPos.z);

		//左右の動き
		if (m_pos.x + m_width < m_posCur.x) {
			m_posXFlag = false;
		}
		else if (m_pos.x - m_width > m_posCur.x) {
			m_posXFlag = true;
		}

		if (m_posXFlag) {

			m_posCur.x += m_widthSpeed * elapsed;
		}
		else if (!m_posXFlag) {
			m_posCur.x -= m_widthSpeed * elapsed;
		}

		//縦の動き
		if (m_pos.y + m_hegiht < m_posCur.y) {
			m_posYFlag = false;
		}
		if (m_pos.y > m_posCur.y) {
			m_posYFlag = true;
		}
		if (m_posYFlag) {
			m_posCur.y += m_hegihtSpeed * elapsed;
		}
		else if (!m_posYFlag) {
			m_posCur.y -= m_hegihtSpeed * elapsed;
		}
		m_trans->SetPosition(Vec3(m_posCur));
		 
		//まき散らすウイルスの更新
		if (eventLenght < 30.0f && stage->GetSharedGameObject<StageManager>(L"StageManager")->GetStageFlag() == 2) {
			m_event = true;
		}
		if (m_event) {
			if (m_pieceCount < 10) {
				m_pieceTime -= elapsed;
				if (m_pieceTime < 0.0f) {
					m_enemyPiece[m_pieceCount] = stage->AddGameObject<EnemyPiece>(m_pos, m_rot, Vec3(2.0f), false);
					m_enemyPiece[m_pieceCount]->Event(360 / 10 * m_pieceCount);
					m_pieceFlag = true;
					m_pieceCount++;
					m_pieceTime = 0.1f;
				}
			}
			if (m_bigPieceCount < 6&&m_pieceCount==10) {
				m_bigPieceTime -= elapsed;
				if (m_bigPieceTime < 0.0f) {
					m_bigEnemyPiece[m_bigPieceCount] = stage->AddGameObject<BigPiece>(m_pos, m_rot, Vec3(2.0f),false);
					m_bigEnemyPiece[m_bigPieceCount]->Event(360 / 6 * m_bigPieceCount);
					m_bigPieceFlag = true;
					m_bigPieceCount++;
					m_bigPieceTime = 0.5f;
				}
			}
			else {
				m_event = false;
			}
			

		}
		if (m_hp < 20) {
			m_event2 = true;
		}
		if (m_event2) {
			if (m_bigPieceCount2 < 8) {
				m_bigPieceTime2 -= elapsed;
				if (m_bigPieceTime2 < 0) {
					m_bigEnemyPiece2[m_bigPieceCount2] = stage->AddGameObject<BigPiece>(m_pos, m_rot, Vec3(1.5f), false);
					m_bigEnemyPiece2[m_bigPieceCount2]->Event(360 / 8 * m_bigPieceCount2,3.0f);
					m_bigPieceFlag2 = true;
					m_bigPieceCount2++;
					m_bigPieceTime2 = 0.2f;
				}

			}
			else {
				m_event2 = false;
			}
		}

		if (m_pieceFlag) {
			for (int i = 0; i < m_pieceCount; i++) {
				m_enemyPiece[i]->UpdateEvent();
				if (m_enemyPiece[i]->GetGroundFlag()) {
					PieceManager::enemyPieces.push_back(m_enemyPiece[i]);
				}
			}
			
		}
		if (m_bigPieceFlag) {
			for (int i = 0; i < m_bigPieceCount; i++) {
				m_bigEnemyPiece[i]->UpdateEvent();
			}
		}
		if (m_bigPieceFlag2) {
			for (int i = 0; i < m_bigPieceCount2; i++) {
				m_bigEnemyPiece2[i]->UpdateEvent();
			}
		}

		if (m_maxHp * 0.80 > m_hp) {
			
			m_scale = m_maxScale - m_scaleReduct;
			m_pos.y = m_originPos.y-m_posYRedect;
		}
		if (m_maxHp * 0.60 > m_hp) {
			m_scale = m_maxScale - m_scaleReduct * 2;
			m_pos.y = m_originPos.y - m_posYRedect * 2;
		}
		if (m_maxHp * 0.40 > m_hp) {
			m_scale = m_maxScale - m_scaleReduct * 3;
			m_pos.y = m_originPos.y - m_posYRedect * 3;

		}
		if (m_maxHp * 0.30 > m_hp) {
			m_scale = m_maxScale - m_scaleReduct * 4;
			m_pos.y = m_originPos.y - m_posYRedect * 4;
		}
		if (m_maxHp * 0.20 > m_hp) {
			m_scale = m_maxScale - m_scaleReduct * 5;
			m_pos.y = m_originPos.y - m_posYRedect * 5;
		}
		

	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Collision)
	{
		m_bullet = dynamic_pointer_cast<Bullet>(Collision);
		auto stage = GetStage();
		//Collision->GetStage()->SetSharedGameObject(L"Bullet", Bulletptr);
		if (!m_bullet.expired())
		{

			int attack = m_bullet.lock()->GetAttack();

			if (Collision->FindTag(L"Bullet") && m_hp >= 0)
			{
				m_hp -=attack;
				//m_scale -= m_scaleReduct;
				//m_pos.y -= m_posYRedect;

			}
		}	
		if (m_hp <= 0)
		{
			GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetCareerFlag(3);//ステージの全体フラグ進行
			GetStage()->RemoveGameObject<Enemy>(GetThis<Enemy>());
			//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToScoreStage");
			m_enemyflag = GetEnemy();

			if (m_enemyflag) {
				GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetEnemyFlag(true);
			}
			int a = 0;
		}
		if (Collision->FindTag(L"Player")) {
			GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetHp(-10.0f);
		}


	}

	void Enemy::EventMove() {

	}

	void Enemy::SetEnemy(bool enemy) {
		m_enemyflag = enemy;
	}
	bool Enemy::GetEnemy() {
		return m_enemyflag;
	}
}
//end basecross
