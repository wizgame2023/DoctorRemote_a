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
		m_StratPosition(Position),
		m_Scale(Scale),
		m_hp(1)
	{

	}
	RecoveryWall::~RecoveryWall()
	{
	};

	void RecoveryWall::OnCreate()
	{
		m_Transform = GetComponent<Transform>();//toransformを取得

		m_Transform->SetPosition(m_Position);//位置を設定
		m_Transform->SetRotation(m_Rotate);//ローテーション（回転）を設定		
		m_Transform->SetScale(m_Scale);//大きさを設定
		//接触のコリジョンを追加
		auto ptrCollider = AddComponent<CollisionObb>();
		ptrCollider->SetFixed(false);//これでぶつかっても動かないようにする


		//描画コンポーネント
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetTextureResource(L"WallRecovery");
		ptrDraw->SetMeshResource(L"Obstacle_Mesh1");


		AddTag(L"RecoveryWall");//BreakWallタグを追加

	};
	void RecoveryWall::OnUpdate()
	{
		if (m_hp <= 0)
		{
			int Recovery = 25;
			GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetHp((float)Recovery);//回復する
			GetStage()->RemoveGameObject<RecoveryWall>(GetThis<RecoveryWall>());

			auto soundSE = App::GetApp()->GetXAudio2Manager();
			soundSE->Start(L"RecoveryWallSE", 0, 1.5f);

		}
		m_Transform->SetPosition(m_Position);//位置を設定

		auto PtrEffect = GetStage()->GetSharedGameObject<Effect>(L"Effect", false);//なぜfalseがあるか調べる
		PtrEffect->InsertEffect(GetComponent<Transform>()->GetPosition());


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
				m_hp -= Attack;
			}

		}
		if (Other->FindTag(L"Player"))
		{
			m_Position = m_StratPosition;
		}
	}

}
//end namespace basecross