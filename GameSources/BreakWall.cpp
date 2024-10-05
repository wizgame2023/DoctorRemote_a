/*!
@file BreakWall.cpp
@brief 壊れる壁
担当：三瓶
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BreakWall::BreakWall(const shared_ptr<Stage>& StagePtr, Vec3 Position, Vec3 Rotate, Vec3 Scale) :
		GameObject(StagePtr),
		m_Position(Position),
		m_StartPosition(Position),
		m_Rotate(Rotate),
		m_Scale(Scale),
		m_hp(1)
	{

	}
	BreakWall::BreakWall(const shared_ptr<Stage>& StagePtr, Vec3 Position, Vec3 Rotate, Vec3 Scale,float mapSize,float miniMapSize,Vec3 miniMapStratPos) :
		GameObject(StagePtr),
		m_Position(Position),
		m_StartPosition(Position),
		m_Rotate(Rotate),
		m_Scale(Scale),
		m_hp(1),
		m_MapMagnification(miniMapSize/mapSize),
		m_MiniMapStartPos(miniMapStratPos)
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
			Vec3(0.0f, -0.1f, 0.0f)
		);

		m_ptrCollider = AddComponent<CollisionObb>();
		//m_ptrCollider->SetSleepActive(true);
		m_ptrCollider->SetFixed(false);//これでぶつかっても動かないようにする
		//m_ptrCollider->SetAfterCollision(AfterCollision::None);

		m_ptrCollider->SetDrawActive(false);//コリジョンを見えるようにする



		//描画コンポーネント
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"WallBreak");
		ptrDraw->SetMeshToTransformMatrix(spanMat);


		auto miniMapPos = m_Position;//ミニマップの座標を入れる
		miniMapPos.y = miniMapPos.z;//座標を調整する
		miniMapPos.z = 5;
		auto a = 0;
		//ミニマップに自分自身を出現させる
		m_MyMiniMap = GetStage()->AddGameObject<Sprite>(1.5f*m_MapMagnification, 4.5f*m_MapMagnification, L"MiniMapBrearkWall", m_MiniMapStartPos + (miniMapPos * m_MapMagnification), Vec3(0.0f, 0.0f, -m_Rotate.y), 5);

		AddTag(L"BreakWall");//BreakWallタグを追加

	};
	void BreakWall::OnUpdate()
	{
		//m_ptrCollider->SetFixed(false);

		auto ptrStage = GetStage();
		//もし体力がなくなったら削除される
		if (m_hp <= 0)
		{	
			//int damage = -20;//これを壊したときの患者へのダメージ量
			//GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetHp((float)damage);//ダメージを与える
			//int piece = 0;//どれくらいピースを手に入るかを決める
			//piece = rand() % 3;//ランダムにどのピースが出るのかを決める変数

			auto soundSE = App::GetApp()->GetXAudio2Manager();
			soundSE->Start(L"BreakWallSE", 0, 1.5f);

			GetStage()->RemoveGameObject<Sprite>(m_MyMiniMap);
			GetStage()->RemoveGameObject<BreakWall>(GetThis<BreakWall>());
		}

		//デバック用
		//auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		//if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
		//	float a = 1.0f;
		//	m_ptrCollider->SetFixed(false);//これでぶつかっても動かないようにする

		//}
		m_Trans->SetPosition(m_Position);//位置を設定


	};

	

	//コリジョンがぶつかったら
	void BreakWall::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		auto stage = GetStage();
		m_bullet = dynamic_pointer_cast<Bullet>(Other);

		if (!m_bullet.expired())
		{
			int Attack = m_bullet.lock()->GetAttack();
			//もしぶつかったコリジョンがBulletのものだったら
			if (Other->FindTag(L"Bullet"))
			{
				m_Position = m_StartPosition;
				m_hp -= Attack;//自分のHPが減る
				auto PtrEffect = stage->GetSharedGameObject<EffectBreakWall>(L"RedEffect", false);
				auto effectPos = GetComponent<Transform>()->GetPosition();
				effectPos.y = 0.0f;
				PtrEffect->InsertEffect(effectPos);//エフェクトの生成位置を設定する

				//auto numPtr = m_MyMiniMap->GetNumPtr();//自分を表示したスプライトの配列番号を取得
				//stage->GetSharedGameObject<UIManager>(L"UIManager")->EraseUiPtr(numPtr);//配列から自分のポインタを消去


			}

		}		
		if (Other->FindTag(L"Player"))
		{
			m_Position = m_StartPosition;
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