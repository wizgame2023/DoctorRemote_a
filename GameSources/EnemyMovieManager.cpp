/*!
@file EnemyMovieManager.cpp
@brief Enemyに出会ったときの演出
担当：三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EnemyMovieManager::EnemyMovieManager(shared_ptr<Stage>& stage,Vec3 pos,Vec3 scale) :
		GameObject(stage),
		m_Position(pos),
		m_Scale(scale),
		m_Count(0),
		m_Time(3.0f)
	{

	}

	EnemyMovieManager::~EnemyMovieManager()
	{

	}

	void EnemyMovieManager::OnCreate()
	{
		m_Trans = GetComponent<Transform>();//toransformを取得

		m_Trans->SetPosition(m_Position);//位置を設定	
		m_Trans->SetRotation(0.0f,0.0f,0.0f);//ローテーション（回転）を設定
		m_Trans->SetScale(m_Scale);//大きさを設定
		//接触のコリジョンを追加
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto collider = AddComponent<CollisionObb>();
		//collider->SetFixed(true);//これでぶつかっても動かないようにする
		collider->SetAfterCollision(AfterCollision::None);
		collider->SetDrawActive(true);//コリジョンを見えるようにする



		//描画コンポーネント
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"WallBreak");
		ptrDraw->SetMeshToTransformMatrix(spanMat);


	}

	void EnemyMovieManager::OnUpdate()
	{
		if (m_Count == 1)
		{
			//AtをEnemyに合わせる
			auto EnemyPos = GetStage()->GetSharedGameObject<Enemy>(L"Enemy")->GetComponent<Transform>()->GetPosition();
			Vec3 cameraAt = m_MovieCamera->GetAt();//注視点

			if (cameraAt != EnemyPos)
			{
				cameraAt.y = 1.5f;
				cameraAt += MoveVec(5.0f, cameraAt, Vec3(11.3f, 0.5f, -8.3f));

				m_MovieCamera->SetAt(cameraAt);//数値をセットする

				 if (abs(cameraAt.x - EnemyPos.x) <= 0.5f && abs(cameraAt.z - EnemyPos.z) <= 0.5f)//ほぼ注視点がEnemyのPosと一緒なら
				 {
					 EnemyPos.y = cameraAt.y;
					 m_MovieCamera->SetAt(EnemyPos);//一緒とみなす
					 //GetStage()->RemoveGameObject<Sprite>(m_MovieBand);//帯を消す
					 m_Count = 2;
				 }

			}

		}

		if (m_Count == 2)
		{
			//Posを指定の場所に移動させる
			Vec3 cameraEye = m_MovieCamera->GetEye();//カメラのPos
			Vec3 MoviePos = Vec3(9.5f, 3.0f, -18.0f);
			if (cameraEye != MoviePos)
			{
				cameraEye += MoveVec(8.0f, cameraEye, MoviePos);
				m_MovieCamera->SetEye(cameraEye);

				if (abs(cameraEye.x - MoviePos.x) <= 0.1f && abs(cameraEye.z - MoviePos.z) <= 0.1f)//ほぼPosがターゲットののPosと一緒なら
				{
					MoviePos.y = cameraEye.y;
					m_MovieCamera->SetEye(MoviePos);//一緒とみなす
					//GetStage()->RemoveGameObject<Sprite>(m_MovieBand);//帯を消す
					m_Count = 3;
				}

			}
		}

		if (m_Count == 3)
		{
			//待機時間
			auto& app = App::GetApp();
			float delta = app->GetElapsedTime();//デルタタイムを取得

			m_Time -= delta;
			if (m_Time < 0)
			{
				GetStage()->RemoveGameObject<Sprite>(m_MovieBand);//帯を消す

				auto View = GetStage()->CreateView<SingleView>();
				View->SetCamera(m_StageCamera.lock());
				GetStage()->SetView(View);
				GetStage()->RemoveGameObject<EnemyMovieManager>(GetThis<EnemyMovieManager>());//自分自身を消す

			}

		}
	
		if (m_Count > 0)
		{
			wstringstream wss(L"");
			auto scene = App::GetApp()->GetScene<Scene>();
			auto gameStage = scene->GetGameStage();
			wss << L"At.X : "
				<< L""
				<< m_MovieCamera->GetAt().x
				<< L"\nAt.Y"
				<< m_MovieCamera->GetAt().y
				<< L"\nAt.Z"
				<< m_MovieCamera->GetAt().z
				<< endl;
			scene->SetDebugString(wss.str());

		}

	}

	Vec3 EnemyMovieManager::MoveVec(float speed, Vec3 pos, Vec3 tagetPos)//移動する距離を決めている
	{
		float VecX = tagetPos.x - pos.x;//目標位置とPlayerとのX座標の距離を測っている
		float VecZ = tagetPos.z - pos.z;//目標位置とPlayerとのZ座標の距離を測っている
		float rad = atan2(VecZ, VecX);//角度を求める（ラジアン）

		Vec3 moveVec(0.0f, 0.0f, 0.0f);

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();//デルタタイムを取得
		moveVec.x = (speed * cos(rad)) * delta;//間接的に距離を足している
		moveVec.z = (speed * sin(rad)) * delta;//間接的に距離を足している

		return moveVec;
	}

	void EnemyMovieManager::OnCollisionEnter(shared_ptr<GameObject>& obj)
	{
		auto stage = GetStage();
		if (obj->FindTag(L"Player")&&m_Count==0)
		{
			m_Count = 1;
			m_StageView = GetStage()->GetView();
			m_StageCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
			//stageCamera->SetEye(Vec3(9.5f, 3.0f, 18.4f));

			auto EnemyPos = GetStage()->GetSharedGameObject<Enemy>(L"Enemy")->GetComponent<Transform>()->GetPosition();

			m_MovieBand = stage->AddGameObject<Sprite>(1280, 800, L"MovieBand", Vec3(), 0);//帯を出す

			//デバック用
			m_MovieCamera = ObjectFactory::Create<Camera>();
			m_MovieCamera->SetEye(m_StageCamera.lock()->GetEye());
			m_MovieCamera->SetAt(m_StageCamera.lock()->GetAt());
			auto testView = GetStage()->CreateView<SingleView>();
			testView->SetCamera(m_MovieCamera);
			GetStage()->SetView(testView);

		}
	}
}