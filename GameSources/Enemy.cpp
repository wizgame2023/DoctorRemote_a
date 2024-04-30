/*!
@file Character.cpp
@brief ìGÇ»Ç«é¿ëÃ
íSìñÅ@ëÂâÕå¥
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr), m_Hp(10)
	{
	}
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& pos, const Vec3& rot, const Vec3& scale) :
		GameObject(StagePtr), m_pos(pos), m_rot(rot), m_scale(scale)
	{ 
	}
	void Enemy::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_pos);
		ptr->SetRotation(m_rot);
		ptr->SetScale(m_scale);

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
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");

			}
		}
	}

}
//end basecross
