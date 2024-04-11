/*!
@file Character.cpp
@brief ìGÇ»Ç«é¿ëÃ
íSìñÅ@ëÂâÕå¥
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),m_Hp(3)
	{
	}
	void Enemy::OnCreate()
	{
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(0, 0, 0);
		ptr->SetRotation(0, 0, 0);
		ptr->SetScale(1, 1, 1);

		AddTag(L"Enemy");

		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		auto ptrColl = AddComponent<CollisionSphere>();

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);
	}


	void Enemy::OnUpdate()
	{

	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& Collision)
	{
		//Collision->GetStage()->SetSharedGameObject(L"Bullet", Bulletptr);
		int attack = m_bullet.lock()->GetAttack();

		if (Collision->FindTag(L"Bullet") && m_Hp > 0)
		{
			m_Hp = m_Hp - attack;
		}
		if (m_Hp <= 0)
		{
			DestroyGameObject();
		}
	}

}
//end basecross
