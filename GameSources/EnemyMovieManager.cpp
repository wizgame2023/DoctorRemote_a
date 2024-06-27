/*!
@file EnemyMovieManager.cpp
@brief Enemyに出会ったときの演出
担当：三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EnemyMovieManager::EnemyMovieManager(shared_ptr<Stage>& stage,Vec3 pos,Vec3 scale,Vec3 moviePos,Vec3 movieAt) :
		GameObject(stage),
		m_Position(pos),
		m_Scale(scale),
		m_MoviePos(moviePos),
		m_MovieAt(movieAt),
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
		collider->SetDrawActive(false);//コリジョンを見えるようにする



		//描画コンポーネント
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"WallBreak");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		AddTag(L"Ground");
	}

	void EnemyMovieManager::OnUpdate()
	{
		if (m_Count == 1)//動作①
		{
			//AtをEnemyに合わせる
			auto EnemyPos = GetStage()->GetSharedGameObject<Enemy>(L"Enemy")->GetComponent<Transform>()->GetPosition();
			Vec3 cameraAt = m_MovieCamera->GetAt();//注視点

			if (cameraAt != EnemyPos)
			{
				cameraAt.y = 2.5f;
				cameraAt += MoveVec(5.0f, cameraAt, m_MovieAt);

				m_MovieCamera->SetAt(cameraAt);//数値をセットする

				 if (abs(cameraAt.x - m_MovieAt.x) <= 1.5f && abs(cameraAt.z - m_MovieAt.z) <= 1.5f)//ほぼ注視点がEnemyのPosと一緒なら
				 {
					 EnemyPos.y = cameraAt.y;
					 m_MovieCamera->SetAt(EnemyPos);//一緒とみなす
					 //GetStage()->RemoveGameObject<Sprite>(m_MovieBand);//帯を消す
					 m_Count = 2;
				 }

			}

		}

		if (m_Count == 2)//動作②
		{
			//Posを指定の場所に移動させる
			Vec3 cameraEye = m_MovieCamera->GetEye();//カメラのPos
			//m_MoviePos = Vec3(9.5f, 4.0f, -20.0f);//指定の場所
			if (cameraEye != m_MoviePos)
			{
				cameraEye += MoveVec(8.0f, cameraEye, m_MoviePos);
				m_MovieCamera->SetEye(cameraEye);

				if (abs(cameraEye.x - m_MoviePos.x) <= 0.3f && abs(cameraEye.z - m_MoviePos.z) <= 0.3f)//ほぼPosがターゲットののPosと一緒なら
				{
					m_MoviePos.y = cameraEye.y;
					m_MovieCamera->SetEye(m_MoviePos);//一緒とみなす
					//GetStage()->RemoveGameObject<Sprite>(m_MovieBand);//帯を消す
					m_Count = 3;
				}

			}
		}

		if (m_Count == 3)//動作③
		{
			m_BossMoji = GetStage()->AddGameObject<Sprite>(200, 100, L"BossMoji", Vec3(-620.0f+100.0f, -390.0f+50.0f, 0.0f), 0);//文字生成
			m_Count = 4;
		}

		if (m_Count == 4)//動作④
		{
			//待機時間
			auto& app = App::GetApp();
			float delta = app->GetElapsedTime();//デルタタイムを取得

			m_Time -= delta;
			if (m_Time < 0)
			{
				m_Player.lock()->GetComponent<Transform>()->SetScale(m_AfterPlayerScale);//変更前のサイズに戻す
				m_Player.lock()->GetComponent<PNTBoneModelDraw>()->SetMeshToTransformMatrix(m_AfterPlayerMat);//変更前の差分行列の数値に戻す

				GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetStartFlag(true);//Playerの操作を効かせる

				auto View = GetStage()->CreateView<SingleView>();
				View->SetCamera(m_StageCamera.lock());
				GetStage()->SetView(View);
				//GetStage()->GetSharedGameObject<UIManager>(L"UIManager")
				GetStage()->GetSharedGameObject<UIManager>(L"UIManager")->AllClear();//透明から戻す	

				int numPtr1 = m_BossMoji->GetNumPtr();//スプライトの配列番号を取得
				GetStage()->GetSharedGameObject<UIManager>(L"UIManager")->EraseUiPtr(numPtr1);//配列に帯のポインタを消す
				GetStage()->RemoveGameObject<Sprite>(m_BossMoji);//文字を消す

				//int numPtr2 = m_MovieBand->GetNumPtr();//スプライトの配列番号を取得
				numPtr1 = m_MovieBand->GetNumPtr();//スプライトの配列番号を取得
				GetStage()->GetSharedGameObject<UIManager>(L"UIManager")->EraseUiPtr(numPtr1);//配列に帯のポインタを消す
				GetStage()->RemoveGameObject<Sprite>(m_MovieBand);//帯を消す

				GetStage()->GetSharedGameObject<StageManager>(L"StageManager")->SetCareerFlag(2);//進行度を進める(Bossが攻撃するようになる予定)

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
			m_Player = stage->GetSharedGameObject<Player>(L"GamePlayer");//GamePlayerを取得
			m_AfterPlayerScale = m_Player.lock()->GetComponent<Transform>()->GetScale();//変更前のサイズを取得
			m_AfterPlayerMat = m_Player.lock()->GetComponent<PNTBoneModelDraw>()->GetMeshToTransformMatrix();//変更前の差分行列を取得

			stage->GetSharedGameObject<StageManager>(L"StageManager")->SetStartFlag(false);//Playerの操作を効かなくさせる


			m_Player.lock()->GetComponent<Transform>()->SetScale(1.0f, 1.0f, 1.0f);//ムービー用のサイズにする
			Mat4x4 spanMat;
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, XM_PI, 0.0f),
				Vec3(0.0f, -0.5f, -0.05f)
			);
			m_Player.lock()->GetComponent<PNTBoneModelDraw>()->SetMeshToTransformMatrix(spanMat);//ムービー用のメッシュの大きさにする


			m_Count = 1;
			m_StageView = GetStage()->GetView();
			m_StageCamera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
			//stageCamera->SetEye(Vec3(9.5f, 3.0f, 18.4f));

			auto EnemyPos = GetStage()->GetSharedGameObject<Enemy>(L"Enemy")->GetComponent<Transform>()->GetPosition();

			stage->GetSharedGameObject<UIManager>(L"UIManager")->AllClear();//Uiを透明にする
			stage->GetSharedGameObject<Radar>(L"Radar")->MyRemove();//レーダーを消去する

			m_MovieBand = stage->AddGameObject<Sprite>(1280, 800, L"MovieBand", Vec3(), 0);//帯を出す
			m_MovieBand->AddTag(L"MovieSprite");//ムービー用のスプライトタグを追加

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