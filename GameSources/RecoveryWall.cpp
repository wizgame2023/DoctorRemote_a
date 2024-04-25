/*!
@file RecoveryWall.cpp
@brief 回復する壁
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RecoveryWall::RecoveryWall(const shared_ptr<Stage>& StagePtr, Vec3 Position, Vec3 Rotate, Vec3 Scale) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Rotate(Rotate),
		m_Scale(Scale),
		m_Hp(1)
	{

	}
	RecoveryWall::~RecoveryWall()
	{
	};

	void RecoveryWall::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();//toransformを取得

		ptrTransform->SetPosition(m_Position);//位置を設定
		ptrTransform->SetScale(m_Scale);//大きさを設定
		ptrTransform->SetRotation(m_Rotate);//クトーニアン（回転）を設定
		//接触のコリジョンを追加
		auto ptrcollider = AddComponent<CollisionObb>();
		ptrcollider->SetDrawActive(true);


		//描画コンポーネント
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMultiMeshResource(L"Obstacle_Mesh1");
		//ptrDraw->SetTextureResource(L"Internal");


		AddTag(L"RecoveryWall");//BreakWallタグを追加

	};
	void RecoveryWall::OnUpdate()
	{
		if (m_Hp <= 0)
		{
			int Recovery = 20;
			GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetHp(Recovery);//ダメージを与える
			GetStage()->RemoveGameObject<RecoveryWall>(GetThis<RecoveryWall>());

		}
	};

	//コリジョンがぶつかったら
	void RecoveryWall::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		m_bullet = dynamic_pointer_cast<Bullet>(Other);

		if (!m_bullet.expired())
		{
			int Attack = m_bullet.lock()->GetAttack();
			//もしぶつかったコリジョンがBulletのものだったら
			if (Other->FindTag(L"Bullet"))
			{
				m_Hp -= Attack;
				//GetStage()->RemoveGameObject<BreakWall>(GetThis<BreakWall>());

			}

		}
	}

}
//end namespace basecross