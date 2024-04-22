/*!
@file RecoveryWall.cpp
@brief 回復する壁
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RecoveryWall::RecoveryWall(const shared_ptr<Stage>& StagePtr, Vec3 Position, Vec3 Scale, Vec3 Rotate) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Scale(Scale),
		m_Rotate(Rotate),
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
		ptrTransform->SetQuaternion(Quat());//クトーニアン（回転）を設定
		//接触のコリジョンを追加
		auto ptrcollider = AddComponent<CollisionObb>();


		//描画コンポーネント
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"Internal");


		AddTag(L"RecoveryWall");//BreakWallタグを追加

	};
	void RecoveryWall::OnUpdate()
	{
		if (m_Hp <= 0)
		{
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
				float recovery = 0.0f;
				recovery = 1.0f;//体力を回復させる
				//GetStage()->RemoveGameObject<BreakWall>(GetThis<BreakWall>());

			}

		}
	}

}
//end namespace basecross