/*!
@file Character.cpp
@brief 敵など実体
担当　大河原
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Hp(10),
		m_posX(1.0f),
		m_enemyflag(false),
		m_meshResName(L"Baikin_Mesh")
	{
	}
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot, const Vec3& scale
	) :
		GameObject(StagePtr),
		m_pos(pos),
		m_rot(rot),
		m_scale(scale),
		m_posX(false),
		m_enemyflag(false),
		m_meshResName(L"Baikin_Mesh"),
		m_Hp(5)
	{ 
	}
	void Enemy::OnCreate()
	{
		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(m_pos);
		m_trans->SetRotation(m_rot);
		m_trans->SetScale(m_scale);

		AddTag(L"Enemy");

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMultiMeshResource(m_meshResName);
		shadowPtr->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMultiMeshResource(m_meshResName);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->AddAnimation(L"Default", 0, 90, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetDrawActive(true);


		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

	}


	void Enemy::OnUpdate()
	{
		float elapsed = App::GetApp()->GetElapsedTime();

		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(elapsed);
		
		m_trans = GetComponent<Transform>();
		m_posCur = m_trans->GetPosition();

		if (m_pos.x + 1.0f < m_posCur.x) {
			m_posX = false;
		}
		else if (m_pos.x - 1.0f > m_posCur.x) {
			m_posX = true;
		}

		if (m_posX) {

			m_posCur.x += 1.0f * elapsed;
		}
		else if (!m_posX) {
			m_posCur.x -= 1.0f * elapsed;
		}
		m_trans->SetPosition(Vec3(m_posCur));
		 
		 
		//auto piece = GetStage()->GetSharedGameObject<Player>(L"GamePlayer");
		//float pieceBar = piece->GetPiece();
		//float maxPieceBar = piece->GetMaxPiece();
	
		//if (pieceBar >= maxPieceBar)
		//{
		//	if (m_counter == 0)
		//	{
		//	  m_Hp = 3;
		//	  ++m_counter;
		//	}
		//}


	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Collision)
	{
		m_bullet = dynamic_pointer_cast<Bullet>(Collision);
		//Collision->GetStage()->SetSharedGameObject(L"Bullet", Bulletptr);
		if (!m_bullet.expired())
		{

			int attack = m_bullet.lock()->GetAttack();

			if (Collision->FindTag(L"Bullet") && m_Hp > 0)
			{
				m_Hp = m_Hp - attack;
			}
		}	
		if (m_Hp <= 0)
		{
			GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetStageFlag(2);//ステージの全体フラグ進行
			GetStage()->RemoveGameObject<Enemy>(GetThis<Enemy>());
			//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToScoreStage");
			m_enemyflag = GetEnemy();

			if (m_enemyflag) {
				GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetEnemyFlag(true);
			}
		}

	}

	void Enemy::SetEnemy(bool enemy) {
		m_enemyflag = enemy;
	}
	bool Enemy::GetEnemy() {
		return m_enemyflag;
	}
}
//end basecross
