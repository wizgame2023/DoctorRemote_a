/*!
@file EscapeManager.cpp
@brief 脱出するシーンの処理等
担当：三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EscapeManager::EscapeManager(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_Time(0.0f)
	{

	}

	EscapeManager::~EscapeManager()
	{

	}

	void EscapeManager::OnCreate()
	{	
		auto stage = GetStage();//ステージ取得
		m_Player = stage->GetSharedGameObject<Player>(L"GamePlayer");//Playerを取得

		m_Sprite = GetStage()->AddGameObject<Sprite>(1280, 800, L"Black", Vec3(0, 0, 0));
		m_Sprite->SetColor(Col4(0.0f, 0.0f, 0.0f, 0.0f));
		m_SpriteCol = m_Sprite->GetColor();

		//m_SpriteCol = Col4(1.0f, 1.0f, 1.0f, 0.0f);


		m_UpdateFlag = 0;
	}

	void EscapeManager::Start()//開始
	{
		auto stage = GetStage();//ステージ取得

		m_Camera = ObjectFactory::Create<Camera>();
		m_Camera->SetEye(Vec3(-10.0f, 15.0f, -15.0f));
		m_Camera->SetAt(Vec3(-10.0f, 0.0f, 0.0f));


		auto View = stage->CreateView<SingleView>();
		View->SetCamera(m_Camera);
		stage->SetView(View);//ステージのビューを設定

		//m_Player = stage->GetSharedGameObject<Player>(L"GamePlayer");//Playerを取得	
		//m_PlayerPos = m_Player.lock()->GetComponent<Transform>()->GetPosition();//Positionを取得

		m_Player.lock()->GetComponent<Transform>()->SetPosition(-10.0f, 2.0f, 0.0f);
		m_Player.lock()->GetComponent<Transform>()->SetRotation(0.0f, 0.0f, 0.0f);

		AABB CollisionActiveArea(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		stage->GetCollisionManager()->SetRootAABB(CollisionActiveArea);

		m_Sprite = GetStage()->AddGameObject<Sprite>(1280, 800, L"Black", Vec3(0, 0, 0));
		m_Sprite->SetColor(Col4(0.0f, 0.0f, 0.0f, 0.0f));

	}

	void EscapeManager::OnUpdate()
	{	
		m_PlayerPos = m_Player.lock()->GetComponent<Transform>()->GetPosition();//Positionを取得

		Vec3 minRange = Vec3(0.0f, 0.0f, 0.0f);//最小の範囲
		Vec3 maxRange = Vec3(10.0f, 0.0f, 10.0f);//最大の範囲
		if (m_PlayerPos.x <= maxRange.x && m_PlayerPos.x >= minRange.x)
		{
			int test = 0;
			if (m_PlayerPos.z <= maxRange.x && m_PlayerPos.z >= minRange.z)
			{
				Start();
				m_UpdateFlag = 1;//脱出する動作にフラグを変更
			}
		}
	
		if (m_UpdateFlag == 1)
		{
			Vec3 speed = Vec3(0.0f, 0.0f, 0.1f);
			auto& app = App::GetApp();
			float delta = app->GetElapsedTime();//デルタタイムを取得
			m_Time += delta;
			m_PlayerPos = m_Player.lock()->GetComponent<Transform>()->GetPosition();
			m_PlayerPos += speed;	

			m_Player.lock()->GetComponent<Transform>()->SetPosition(m_PlayerPos);
			if (m_Time >= 1.0f)
			{		
				m_SpriteCol.w += 0.2f * delta;
				m_Sprite->SetColor(m_SpriteCol);
				if (m_SpriteCol.w > 1.0f)
				{
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToScoreStage");
				}
			}
		}
	}

}