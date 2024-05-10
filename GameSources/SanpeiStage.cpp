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
		//auto path = App::GetApp()->GetDataDirWString();
		//auto texPath = path + L"Textures/";
		//auto modelPath = path + L"Models/";
		//wstring strTexture = texPath + L"hakusi.jpg";
		//App::GetApp()->RegisterTexture(L"White", strTexture);
		//strTexture = texPath + L"arrow2.png";
		//App::GetApp()->RegisterTexture(L"Arrow", strTexture);
		//strTexture = texPath + L"Black.jpg";
		//App::GetApp()->RegisterTexture(L"Black", strTexture);
		//strTexture = texPath + L"InternalSkin.png";
		//App::GetApp()->RegisterTexture(L"Internal", strTexture);
		//strTexture = texPath + L"Bar.png";
		//App::GetApp()->RegisterTexture(L"Bar", strTexture);
		//strTexture = texPath + L"Radaryoko1.png";
		//App::GetApp()->RegisterTexture(L"Radar", strTexture);
		//strTexture = texPath + L"RadarBlueYoko.png";
		//App::GetApp()->RegisterTexture(L"RadarBlue", strTexture);
		//strTexture = texPath + L"RadarOrangeYoko.png";
		//App::GetApp()->RegisterTexture(L"RadarOrange", strTexture);
		//strTexture = texPath + L"RadarRedYoko.png";
		//App::GetApp()->RegisterTexture(L"RadarRed", strTexture);

		//Playerのモデル生成
		//auto staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Sensuikan.bmf");
		//App::GetApp()->RegisterResource(L"Sensuikan_Mesh", staticMultiModelMesh);

		//auto strModel = MultiMeshResource::CreateStaticModelMultiMesh(modelPath, L"Sensuikan.bmf");
		//App::GetApp()->RegisterResource(L"PLAYER_MODEL", strModel);

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

		AddGameObject<MyLight>();//光の表現をこれでやる

	}

	void SanpeiStage::CreateEffect()//エフェクト生成
	{
		auto EffectPtr = AddGameObject<Effect>(L"PlayerEffectGreen", 0.5f, 8, Vec3(0.0f, 0.0f, 0.0f),Vec3(0.1f,0.1f,0.1f));
		SetSharedGameObject(L"Effect", EffectPtr);
		EffectPtr = AddGameObject<Effect>(L"PlayerEffectRed", 1.0f, 10, Vec3(0.3f, 0.8f, 0.3f));
		SetSharedGameObject(L"RedEffect", EffectPtr);
	}

	void SanpeiStage::CreateBullet()
	{
		//弾生成　　引数は左から順番に初期位置→大きさ→スピード→角度（rad）→攻撃力 となっています
		auto Bulletptr = AddGameObject<Bullet>(Vec3(-1.0f, 0.5f, 0.0f), Vec3(0.3f, 0.3f, 0.3f), 1.0f, 0.0f, 1);
		Bulletptr->GetSpeed();
		//シェア配列にBulletを追加
		SetSharedGameObject(L"Bullet", Bulletptr);//これでAddしたゲームオブジェクトを取得できる
	}

	//Playerを追加する関数
	void SanpeiStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>(Vec3(0.0f, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"GamePlayer", ptrPlayer);//ゲームオブジェクトを取得
		//auto ptrTarget = GetSharedObject(L"Bullet");//Addしたゲームオブジェクト(Bullet)を取得する

	}
	//レーダーを追加する関数
	void SanpeiStage::CreateRadar()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"GamePlayer");//GamePlayerというオブジェクトを取得
		auto PlayerTrans = ptrPlayer->GetComponent<Transform>();//そのオブジェクトのTransformを取得
		auto PlayerPos = PlayerTrans->GetPosition();//Positionを取得
		/////auto PlayerAngle = ptrPlayer;//Playerの向いている角度を取得する


		auto ptrEnemy = GetSharedObject(L"Enemy");//Enemyというオブジェクトを取得
		auto EnemyTrans = ptrEnemy->GetComponent<Transform>();//そのオブジェクトのTransformを取得
		auto EnemyPos = EnemyTrans->GetPosition();//Positionを取得
		auto ptrRadar = AddGameObject<Radar>(PlayerPos, EnemyPos);//レーダーを生成
	}

	//敵を作成
	void SanpeiStage::CreateEnemy()
	{
		auto ptrEnemy = AddGameObject<Enemy>(Vec3(0.0f,0.0f,0.0f),Vec3(0.0f,0.0f,0.0f),Vec3(1.0f,1.0f,1.0f));
		SetSharedGameObject(L"Enemy", ptrEnemy);//ゲームオブジェクトを取得
	}

	//敵の欠片を作成
	void SanpeiStage::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = {
			{//1
				Vec3(5.0f,0.5f,0.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.5f,0.5f,0.5f),
			},
			{//2
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(-20.0f,0.0f,5.0f)
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
				Vec3(0.0f,0.0f,3.0f)
			},
			{//7
				Vec3(0.5f,0.5f,0.5f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.0f,0.0f,0.0f)
			}

		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<EnemyPiece>(v[0], v[1], v[2]);
		}
	}


	void SanpeiStage::OnCreate() {
		try {

			//テクスチャ、モデルの設定データ
			//auto data = AddGameObject<Data>();

			auto& app = App::GetApp();

			auto path = app->GetDataDirWString();
			//auto texPath = path + L"Textures/";


			//ビューとライトの作成
			CreateViewLight();
			//弾を作成
			//CreateBullet();
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
			auto PGarge = AddGameObject<PlayerGarge>();

			//壁を出現（テスト）
			AddGameObject<BreakWall>(Vec3(5.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(2.0f, 2.0f, 2.0f));
			AddGameObject<RecoveryWall>(Vec3(15.0f, 0.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));

			AddGameObject<Block>(Vec3(10.0f, -0.5f,-2.0f), Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject<BlockSecond>(Vec3(-10.5f, 4.5f, 15.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));


			auto stageManager = AddGameObject<StageManager>();//ステージマネージャー追加
			SetSharedGameObject(L"StageManager", stageManager);


			//エフェクトを出現（テスト）
			//AddGameObject<EffectBullet>(L"DamageBullet",3, 2, Vec3(-1.0f, 0.5f, 0.0f), 0.1f);

			CreateEffect();//エフェクト生成

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
