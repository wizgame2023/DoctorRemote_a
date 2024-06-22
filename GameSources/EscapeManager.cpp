/*!
@file EscapeManager.cpp
@brief 脱出するシーンの処理等
担当：三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EscapeManager::EscapeManager(const shared_ptr<Stage>& stagePtr,Vec3 cameraEye,Vec3 cameraAt,Vec3 minRange,Vec3 maxRange,Vec3 playerStartPos,Vec3 TagetPos):
		GameObject(stagePtr),
		m_Time(0.0f),
		m_UpdateFlag(0),
		m_CameraEye(cameraEye),
		m_CameraAt(cameraAt),
		m_MinRange(minRange),
		m_MaxRange(maxRange),
		m_PlayerStartPos(playerStartPos),
		m_TargetPos(TagetPos)
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

	}

	void EscapeManager::Start()//開始
	{
		auto stage = GetStage();//ステージ取得
		GetStage()->GetSharedGameObject<UIManager>(L"UIManager")->AllClear();//透明から戻す	

		stage->GetSharedGameObject<StageManager>(L"StageManager")->SetStartFlag(false);//Playerの操作を効かなくさせる

		m_Camera = ObjectFactory::Create<Camera>();//カメラの生成
		m_Camera->SetEye(m_CameraEye);
		m_Camera->SetAt(m_CameraAt);


		auto View = stage->CreateView<SingleView>();//新たなビューの生成
		View->SetCamera(m_Camera);
		stage->SetView(View);//ステージのビューを設定

		//m_Player = stage->GetSharedGameObject<Player>(L"GamePlayer");//Playerを取得
		Vec3 test = m_PlayerStartPos;

		m_Player.lock()->GetComponent<Transform>()->SetPosition(m_PlayerStartPos);
		m_Player.lock()->GetComponent<Transform>()->SetRotation(0.0f, 0.0f, 0.0f);
		m_Player.lock()->GetComponent<Transform>()->SetScale(1.0f, 1.0f, 1.0f);
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI, 0.0f),
			Vec3(0.0f, -0.5f, -0.05f)
		);

		m_Player.lock()->GetComponent<PNTBoneModelDraw>()->SetMeshToTransformMatrix(spanMat);
		m_PlayerPos = m_Player.lock()->GetComponent<Transform>()->GetPosition();//PlayerのPositionを取得

		auto stageManager = stage->GetSharedGameObject<StageCollisionManager>(L"StageCollisionManager");//コリジョンマネージャー取得
		stageManager->SetCollisionSwhich(false);//当たり判定を消す
		//AABB CollisionActiveArea(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		//stage->GetCollisionManager()->SetRootAABB(CollisionActiveArea);

		m_Sprite = GetStage()->AddGameObject<Sprite>(1280, 800, L"Black", Vec3(0, 0, 0));
		m_Sprite->SetColor(Col4(0.0f, 0.0f, 0.0f, 0.0f));

	}

	void EscapeManager::OnUpdate()
	{	
		m_PlayerPos = m_Player.lock()->GetComponent<Transform>()->GetPosition();//Positionを取得

		//この範囲にいたら脱出シーンが起きる
		if (m_PlayerPos.x <= m_MaxRange.x && m_PlayerPos.x >= m_MinRange.x && m_UpdateFlag == 0)
		{
			if (m_PlayerPos.z <= m_MaxRange.z && m_PlayerPos.z >= m_MinRange.z)
			{
				Start();
				m_UpdateFlag = 1;//脱出する動作にフラグを変更
			}
		}
	
		if (m_UpdateFlag == 1)
		{
			GetStage()->GetSharedGameObject<TimeManager>(L"TimeManager")->SetTimeFlag(false);//制限時間のカウントを終わらせる
			
			//wstringstream wss;//デバック用文字列
			//wss << L"エスケープマネージャー：" << endl;


			float speed = 5.0f;//速さ
			float VecX = m_TargetPos.x - m_PlayerPos.x;//目標位置とPlayerとのX座標の距離を測っている
			float VecZ = m_TargetPos.z - m_PlayerPos.z;//目標位置とPlayerとのZ座標の距離を測っている
			float rad = atan2(VecZ, VecX);//角度を求める（ラジアン）
			float playerrad = rad + XMConvertToRadians(180.0f);//Playerの向いている方向
			
			m_Player.lock()->GetComponent<Transform>()->SetRotation(0.0f, playerrad - DifferenceRad(playerrad), 0.0f);//進む方向に向く

			//float degConvert = 180.0f / XM_PI;//radからdegに変換するための変数
			//float deg = (rad * degConvert);//ラジアンをディグリーに変換

			//wss << "90.0f:" << XMConvertToDegrees(DifferenceRad(playerrad)) << endl << "VecZ:" << VecZ << endl;//デバック文字列
			//wss << m_UpdateFlag<<endl;
			auto& app = App::GetApp();
			float delta = app->GetElapsedTime();//デルタタイムを取得
			m_Time += delta;//時間経過
			m_PlayerPos.x += (speed * cos(rad)) * delta;//間接的に距離を足している
			m_PlayerPos.z += (speed * sin(rad)) * delta;//間接的に距離を足している
			//auto PlayerRot = m_Player.lock()->GetComponent<Transform>()->GetRotation();
			//wss << "RosX:" << PlayerRot.x << endl << "RosY:" << PlayerRot.y << endl << "RotZ" << PlayerRot.z << endl;//デバック文字列


			m_Player.lock()->GetComponent<Transform>()->SetPosition(m_PlayerPos);
			if (m_Time >= 1.0f)
			{		
				m_SpriteCol.w += 0.2f * delta;//だんだんと画面が暗くなる
				m_Sprite->SetColor(m_SpriteCol);
				if (m_SpriteCol.w > 1.0f)
				{
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToScoreStage");
				}
			}
			//デバック用文字列を生成
			//auto scene = app->GetScene<Scene>();
			//scene->SetDebugString(L"a\n" + wss.str());

		}
	}

	float EscapeManager::DifferenceRad(float rad)
	{
		float difference = 0.0f;//実際の方向とオブジェクトが向いている方向の差
		float deg = XMConvertToDegrees(rad);//ラジアンをディグリーに

		if (deg >= 180.0f)//degが１８０度よりも高かったら
		{
			while (deg > 180.0f)//180以下になるまで
			{
				deg -= 180.0f;//１８０度引く
			}
		}

		bool Flag = false;
		int count = 0;//何回90で割ったか数える
		if (deg >= 90.0f)//90度より大きかったら
		{
			count++;
			deg -= 90.0f;

			if (count % 2 == 0)//偶数なら
			{
				Flag = true;
			}
			if (count % 2 == 1)//奇数なら
			{
				Flag = false;
			}
		}

		if (Flag = false)//90度より小さいなら
		{
			difference = 90.0f;
			difference -= deg * 2.0f;
			auto test = difference;//デバック用
		}
		if (Flag = true)//90度より大きいなら
		{
			difference = -90.0f;
			difference += deg * 2.0f;
			auto test = difference;
		}

		return XMConvertToRadians(difference);

	}


}