/*!
@file Character.cpp
@brief ìGÇ»Ç«é¿ëÃ
íSìñÅ@ëÂâÕå¥
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr), m_Hp(100), m_counter(0)
	{
	}
	void Enemy::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(20.0f, 0.5f, 23.0f);
		ptr->SetRotation(0, 0, 0);
		ptr->SetScale(1, 1, 1);

		AddTag(L"Enemy");

		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionSphere>();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

	}


	void Enemy::OnUpdate()
	{

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
			if (m_Hp <= 0)
			{
				GetStage()->RemoveGameObject<Enemy>(GetThis<Enemy>());
			}
		}
	}

}
//end basecross
