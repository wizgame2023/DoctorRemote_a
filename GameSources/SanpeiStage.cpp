/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void SanpeiStage::CreateViewLight() {
		//wstring dataDir;

		//サンプルのためアセットディレクトリを取得
		//App::GetApp()->GetAssetsDirectory(dataDir);//今仮で使っているので実際に実装するときは下のを使う
		auto path = App::GetApp()->GetDataDirWString();
		auto texPath = path + L"Textures/";
		wstring strTexture = texPath + L"hakusi.jpg";
		App::GetApp()->RegisterTexture(L"White", strTexture);
		strTexture = texPath + L"arrow2.png";
		App::GetApp()->RegisterTexture(L"Arrow", strTexture);
		strTexture = texPath + L"Black.jpg";
		App::GetApp()->RegisterTexture(L"Black", strTexture);

		// カメラの設定
		auto camera = ObjectFactory::Create<Camera>();
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

	void SanpeiStage::CreateBullet()
	{
		//弾生成　　引数は左から順番に初期位置→大きさ→スピード→角度（rad）→攻撃力 となっています
		auto Bulletptr = AddGameObject<Bullet>(Vec3(0.0f, 0.5f, 0.0f), Vec3(0.3f, 0.3f, 0.3f),1.0f, 0.785398f,1);
		Bulletptr->GetSpeed();
		//シェア配列にBulletを追加
		SetSharedGameObject(L"Bullet", Bulletptr);//これでAddしたゲームオブジェクトを取得できる
	}

	//Playerを追加する関数
	void SanpeiStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>();
		SetSharedGameObject(L"GamePlayer", ptrPlayer);//ゲームオブジェクトを取得
		auto ptrTarget = GetSharedObject(L"Bullet");//Addしたゲームオブジェクト(Bullet)を取得する

	}
	//レーダーを追加する関数
	void SanpeiStage::CreateRadar()
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
	void SanpeiStage::CreateEnemy()
	{
		auto ptrEnemy = AddGameObject<Enemy>();
		SetSharedGameObject(L"Enemy", ptrEnemy);//ゲームオブジェクトを取得
	}

	//敵の欠片を作成
	void SanpeiStage::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = {
			{
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(5.0f,0.5f,0.0f)
			},
			{
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(-5.0f,0.0f,5.0f)
			},
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<EnemyPiece>(v[0], (Quat)v[1], v[2]);
		}
	}


	void SanpeiStage::OnCreate() {
		try {
			auto& app = App::GetApp();

			auto path = app->GetDataDirWString();
			//auto texPath = path + L"Textures/";


			//ビューとライトの作成
			CreateViewLight();
			//弾を作成
			CreateBullet();
			//Playerを追加
			CreatePlayer();
			//敵のかけらを表示
			CreateEnemyPiece();
			CreateEnemy();
			AddGameObject<Ground>();//地面を表示
			//レーダーを追加
			CreateRadar();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
