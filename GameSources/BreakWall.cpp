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
		m_StartPosition(Position),
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
		m_Trans = GetComponent<Transform>();//toransformを取得

		m_Trans->SetPosition(m_Position);//位置を設定	
		m_Trans->SetRotation(m_Rotate);//ローテーション（回転）を設定
		m_Trans->SetScale(m_Scale);//大きさを設定
		//接触のコリジョンを追加
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		m_ptrCollider = AddComponent<CollisionObb>();
		m_ptrCollider->SetFixed(false);//これでぶつかっても動かないようにする
		//m_ptrCollider->SetAfterCollision(AfterCollision::None);

		//m_ptrCollider->SetDrawActive(true);//コリジョンを見えるようにする



		//描画コンポーネント
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"WallBreak");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		AddTag(L"BreakWall");//BreakWallタグを追加

	};
	void BreakWall::OnUpdate()
	{
		//m_ptrCollider->SetFixed(false);

		auto ptrStage = GetStage();
		//もし体力がなくなったら削除される
		if (m_Hp <= 0)
		{	
			int damage = -20;//これを壊したときの患者へのダメージ量
			GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetHp((float)damage);//ダメージを与える
			int piece = 0;//どれくらいピースを手に入るかを決める
			piece = rand() % 3;//ランダムにどのピースが出るのかを決める変数

			auto soundSE = App::GetApp()->GetXAudio2Manager();
			soundSE->Start(L"BreakWallSE", 0, 0.5f);


			GetStage()->RemoveGameObject<BreakWall>(GetThis<BreakWall>());
		}

		//デバック用
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
			float a = 1.0f;
			m_ptrCollider->SetFixed(false);//これでぶつかっても動かないようにする

		}
		m_Trans->SetPosition(m_Position);//位置を設定


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
				m_Position = m_StartPosition;
				m_Hp -= Attack;//自分のHPが減る
				//GetStage()->RemoveGameObject<BreakWall>(GetThis<BreakWall>());

				auto PtrEffect = GetStage()->GetSharedGameObject<EffectBreakWall>(L"RedEffect", false);
				PtrEffect->InsertEffect(GetComponent<Transform>()->GetPosition());

			}

		}		
		if (Other->FindTag(L"Player"))
		{
			m_Position = m_StartPosition;
			//m_ptrCollider->SetFixed(true);//これでぶつかっても動かないようにする
		}
	}

	//void BreakWall::OnCollisionExit(shared_ptr<GameObject>& Other)
	//{
	//	if (Other->FindTag(L"Player"))
	//	{
	//		//m_Position = m_StartPosition;
	//		m_ptrCollider->SetFixed(false);//これでぶつかっても動かないようにする
	//	}

	//}

}
//end namespace basecross