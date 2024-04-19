/*!
@file BreakWall.cpp
@brief 壊れる壁
担当　三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BreakWall::BreakWall(const shared_ptr<Stage>& StagePtr, Vec3 Position, Vec3 Scale, Vec3 Rotate):
		GameObject(StagePtr),
		m_Position(Position),
		m_Scale(Scale),
		m_Rotate(Rotate),
		m_Hp(1)
	{

	}
	BreakWall::~BreakWall()
	{
	};

	void BreakWall::OnCreate()
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
		ptrDraw->SetTextureResource(L"Internal");


		AddTag(L"BreakWall");//BreakWallタグを追加

	};
	void BreakWall::OnUpdate()
	{
		if (m_Hp <= 0)
		{
			GetStage()->RemoveGameObject<BreakWall>(GetThis<BreakWall>());

		}
	};

	//コリジョンがぶつかったら
	void BreakWall::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		m_bullet = dynamic_pointer_cast<Bullet>(Other);

		if (!m_bullet.expired())
		{
			int Attack = m_bullet.lock()->GetAttack();
			//もしぶつかったコリジョンがEnemyのものだったら
			if (Other->FindTag(L"Bullet"))
			{
				m_Hp -= Attack;
				//GetStage()->RemoveGameObject<BreakWall>(GetThis<BreakWall>());

			}

		}
	}

}
//end namespace basecross