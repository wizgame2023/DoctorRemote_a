/*!
@file HemmiStage.cpp
@brief サンプルステージ
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void HemmiStage::CreateViewLight() {


		// カメラの設定
		auto camera = ObjectFactory::Create<MainCamera>();
		camera->SetEye(Vec3(0.0f, 15.0f, -5.0f));
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定	

		//AddGameObject<MyLight>();//光の表現をこれでやる

	}

	void HemmiStage::CreateBullet()
	{
		//弾生成　　引数は左から順番に初期位置→大きさ→スピード→角度（rad）→攻撃力 となっています
		auto Bulletptr = AddGameObject<Bullet>(Vec3(-1.0f, 0.5f, 0.0f), Vec3(0.3f, 0.3f, 0.3f), 1.0f, 0.0f, 1);
		Bulletptr->GetSpeed();
		//シェア配列にBulletを追加
		SetSharedGameObject(L"Bullet", Bulletptr);//これでAddしたゲームオブジェクトを取得できる
	}

	//Playerを追加する関数
	void HemmiStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>();
		SetSharedGameObject(L"GamePlayer", ptrPlayer);//ゲームオブジェクトを取得
		//auto ptrTarget = GetSharedObject(L"Bullet");//Addしたゲームオブジェクト(Bullet)を取得する

	}
	//レーダーを追加する関数
	void HemmiStage::CreateRadar()
	{
		auto ptrPlayer = GetSharedObject(L"GamePlayer");//GamePlayerというオブジェクトを取得
		auto PlayerTrans = ptrPlayer->GetComponent<Transform>();//そのオブジェクトのTransformを取得
		auto PlayerPos = PlayerTrans->GetPosition();//Positionを取得
		auto ptrEnemy = GetSharedObject(L"Enemy");//Enemyというオブジェクトを取得
		auto EnemyTrans = ptrEnemy->GetComponent<Transform>();//そのオブジェクトのTransformを取得
		auto EnemyPos = EnemyTrans->GetPosition();//Positionを取得
		auto ptrRadar = AddGameObject<Radar>(PlayerPos, EnemyPos);//レーダーを生成
	}

	//敵を作成
	void HemmiStage::CreateEnemy()
	{
		auto ptrEnemy = AddGameObject<Enemy>();
		SetSharedGameObject(L"Enemy", ptrEnemy);//ゲームオブジェクトを取得
	}

	//敵の欠片を作成
	void HemmiStage::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = {
			{//1
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(5.0f,0.5f,0.0f)
			},
			{//2
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(-5.0f,0.0f,5.0f)
			},
			{//3
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(-8.0f,0.0f,3.0f)
			},
			{//4
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(-10.0f,0.0f,23.0f)
			},
			{//5
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(-23.0f,0.0f,13.0f)
			},
			{//6
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(-18.0f,0.0f,3.0f)
			},
			{//7
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(15.0f,0.0f,12.0f)
			}

		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<EnemyPiece>(v[0], (Quat)v[1], v[2]);
		}
	}


	void HemmiStage::OnCreate() {
		try {

			//テクスチャ、モデルの設定データ
			auto data = AddGameObject<Data>();

			//ビューとライトの作成
			CreateViewLight();
			//Playerを追加
			CreatePlayer();
			//敵のかけらを表示
			CreateEnemyPiece();
			CreateEnemy();
			//AddGameObject<Ground>();//地面を表示
			//レーダーを追加
			CreateRadar();
			//地面を生成
			AddGameObject<Ground>();
			//ゲージを追加
			auto garge = AddGameObject<PieceGarge>(GetSharedGameObject<Player>(L"GamePlayer"));
			SetSharedGameObject(L"Garge", garge);
			
			auto garge2 = AddGameObject<PieceGarge2>();

			auto player = GetSharedGameObject<Player>(L"GamePlayer");
			//garge->UpdateValue(0.1f);

			auto playerGarge = AddGameObject<PlayerGarge>();
			//playerGarge->GetComponent<Transform>()->SetPosition(300, -300, 0);
		}
		catch (...) {
			throw;
		}
	}

}
//end namespace basecross