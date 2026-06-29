/*!
@file JoinManager.cpp
@brief 脱出するシーンの処理等
担当：三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	JoinManager::JoinManager(const shared_ptr<Stage>& stagePtr, Vec3 playerStartPos, Vec3 TagetPos) ://コンストラクタ１
		GameObject(stagePtr),
		m_Time(0.0f),
		m_UpdateFlag(0),
		m_PlayerStartPos(playerStartPos),
		m_TargetPos(TagetPos),
		m_MinRange(Vec3(TagetPos.x - 0.5f, TagetPos.y, TagetPos.z - 0.5f)),
		m_MaxRange(Vec3(TagetPos.x + 0.5f, TagetPos.y, TagetPos.z + 0.5f))
	{

	}

	JoinManager::JoinManager(const shared_ptr<Stage>& stagePtr,Vec3 TagetPos) ://コンストラクタ2
		GameObject(stagePtr),
		m_Time(0.0f),
		m_UpdateFlag(0),
		m_TargetPos(TagetPos),
		m_MinRange(Vec3(TagetPos.x - 0.5f, TagetPos.y, TagetPos.z - 0.5f)),
		m_MaxRange(Vec3(TagetPos.x + 0.5f, TagetPos.y, TagetPos.z + 0.5f))
	{

	}

	JoinManager::~JoinManager()
	{

	}

	void JoinManager::OnCreate()
	{	
		auto stage = GetStage();//ステージ取得
		m_Player = stage->GetSharedGameObject<Player>(L"GamePlayer");//Playerを取得

		m_Sprite = GetStage()->AddGameObject<Sprite>(1280, 800, L"Black", Vec3(0, 0, 0));
		m_Sprite->SetColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));//半透明で出す

		m_stageCollionManager = stage->GetSharedGameObject<StageCollisionManager>(L"StageCollisionManager");//CollisionManagerを取得
		m_stageCollionManager->SetCollisionSwhich(false);//ステージ上のコリジョン判定をなくす

		m_Player = stage->GetSharedGameObject<Player>(L"GamePlayer");//Playerを取得

		
		auto ptrCamera = stage->GetView()->GetTargetCamera();
		m_Camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		auto mainCamera = m_Camera.lock();
		if (mainCamera) 
		{
			mainCamera->SetMove(false);//カメラの操作を無視させる
		}
	}

	void JoinManager::OnUpdate()
	{	
		m_PlayerPos = m_Player.lock()->GetComponent<Transform>()->GetPosition();//Positionを取得
		auto stage = GetStage();


		float speed = 5.0f;//速さ
		float VecX = m_TargetPos.x - m_PlayerPos.x;//目標位置とPlayerとのX座標の距離を測っている
		float VecZ = m_TargetPos.z - m_PlayerPos.z;//目標位置とPlayerとのZ座標の距離を測っている
		float rad = atan2(VecZ, VecX);//角度を求める（ラジアン）


		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();//デルタタイムを取得
		m_PlayerPos.x += (speed * cos(rad)) * delta;//間接的に距離を足している
		m_PlayerPos.z += (speed * sin(rad)) * delta;//間接的に距離を足している
		m_Player.lock()->GetComponent<Transform>()->SetPosition(m_PlayerPos);//Playerに変更したPositionに設定

		if (m_PlayerPos.x <= m_MaxRange.x && m_PlayerPos.x >= m_MinRange.x && m_UpdateFlag == 0)//目標地点に付いたら
		{
			if (m_PlayerPos.z <= m_MaxRange.z && m_PlayerPos.z >= m_MinRange.z)
			{
				dynamic_pointer_cast<MainCamera>(OnGetDrawCamera())->SetMove(true);//カメラを操作できるようになる
				m_stageCollionManager->SetCollisionSwhich(true);//ステージ上のコリジョン判定を復活させる
				auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
				stageManager->SetCountFlag(true);//ステージのカウントを開始する
				stage->RemoveGameObject<Sprite>(m_Sprite);//スプライトを削除
				stage->RemoveGameObject<JoinManager>(GetThis<JoinManager>());//自分自身を削除
			}
		}



	}

}
//end namaspace basecross