/*!
@file BreakWall.cpp
@brief 壊れる壁
担当　三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BreakWall::BreakWall(const shared_ptr<Stage>& StagePtr, Vec3 Position,  Vec3 Rotate,Vec3 Scale):
		GameObject(StagePtr),
		m_Position(Position),
		m_Rotate(Rotate),
		m_Scale(Scale),
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
		ptrTransform->SetRotation(m_Rotate);//ローテーション（回転）を設定
		ptrTransform->SetScale(m_Scale);//大きさを設定
		//接触のコリジョンを追加
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto ptrcollider = AddComponent<CollisionCapsule>();
		ptrcollider->SetDrawActive(true);


		//描画コンポーネント
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMultiMeshResource(L"Obstacle_Mesh1");
		ptrDraw->SetTextureResource(L"Internal");



		AddTag(L"BreakWall");//BreakWallタグを追加

	};
	void BreakWall::OnUpdate()
	{
		auto ptrStage = GetStage();
		//もし体力がなくなったら削除される
		if (m_Hp <= 0)
		{	
			int damage = -10;//これを壊したときの患者へのダメージ量
			GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetHp(damage);//ダメージを与える
			int piece = 0;//どれくらいピースを手に入るかを決める
			piece = rand() % 3;//ランダムにどのピースが出るのかを決める変数

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
			//もしぶつかったコリジョンがBulletのものだったら
			if (Other->FindTag(L"Bullet"))
			{
				m_Hp -= Attack;//自分のHPが減る
				//GetStage()->RemoveGameObject<BreakWall>(GetThis<BreakWall>());

			}

		}
	}

}
//end namespace basecross