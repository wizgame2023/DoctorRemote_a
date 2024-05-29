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
	void SanpeiStage::CreateViewLight() 
	{
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
		//camera->SetEye(Vec3(0.0f, 15.0f, -5.0f));
		//camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		m_View = CreateView<SingleView>();
		m_View->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定	

		//AddGameObject<MyLight>();//光の表現をこれでやる

	}

	void SanpeiStage::CreateEffect()//エフェクト生成
	{
		auto EffectPtr = AddGameObject<Effect>(L"PlayerEffectGreen", 0.5f, 8, Vec3(0.0f, 0.0f, 0.0f),Vec3(0.1f,0.1f,0.1f));
		SetSharedGameObject(L"Effect", EffectPtr);
		auto EffectPtr2 = AddGameObject<EffectBreakWall>(L"PlayerEffectRed", 1.0f, 20, Vec3(0.2f, 0.6f, 0.2f),Vec3(0.4f,0.4f,0.4f));//使わない
		SetSharedGameObject(L"RedEffect", EffectPtr2);
		auto EffectPtr3 = AddGameObject<EffectMove>(L"PlayerEffectWhite", 1.5f, 15, 1.0f, Vec3(0.0f, 1.3f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
		SetSharedGameObject(L"PlayerEffectWhite", EffectPtr3);
		auto EffectPtr4 = AddGameObject<EffectChase>(L"PlayerEffectRed", 1.0f, 15, 1.0f, Vec3(0.5f, 0.8f, 0.5f), Vec3(0.85f, 0.85f, 0.85f));
		SetSharedGameObject(L"EffectChase", EffectPtr4);
		EffectPtr4 = AddGameObject<EffectChase>(L"PlayerEffectGreen", 1.5f, 15, 1.0f, Vec3(0.0f, 0.5f, 0.0f), Vec3(0.8f, 0.8f, 0.8f));
		SetSharedGameObject(L"PlayerEffectRecovery", EffectPtr4);


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
		auto ptrEnemy = AddGameObject<Enemy>(Vec3(10.0f,0.0f,10.0f),Vec3(0.0f,0.0f,0.0f),Vec3(1.0f,1.0f,1.0f));
		SetSharedGameObject(L"Enemy", ptrEnemy);//ゲームオブジェクトを取得
	}

	//敵の欠片を作成
	void SanpeiStage::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = 
		{
			{//8				
				Vec3(-6.25f,0.0f,24.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.5f,0.5f,0.5f)

			},
			{//9
				Vec3(-4.56f,0.0f,40.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.5f,0.5f,0.5f)

			},
			{//10
				Vec3(-7.25f,0.0f,-45.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.5f,0.5f,0.5f)

			},
			{//11
				Vec3(28.9f,0.0f,-14.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.5f,0.5f,0.5f)
			},
			{//12
				Vec3(45.0f,0.0f,-7.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.5f,0.5f,0.5f)

			},
			{//13
				Vec3(16.0f,0.0f,10.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.5f,0.5f,0.5f)
			},
			{//14
				Vec3(12.0f,0.0f,41.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.5f,0.5f,0.5f)

			},
			{//15
				Vec3(0.6f,0.0f,34.3f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.5f,0.5f,0.5f)

			},
			{//16
				Vec3(10.0f,0.0f,20.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(0.5f,0.5f,0.5f)

			}

		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<EnemyPiece>(v[0], v[1], v[2]);
		}
	}

	void SanpeiStage::SetMiniMap()//ミニマップ生成 分からないところが多すぎるのでしっかり授業のデータを見直して考える
	{
		float Lenght = 225.0f;//ミニマップの直径
		auto miniMap = AddGameObject<Sprite>(Lenght, Lenght, L"MiniMap", Vec3(640.0f - (Lenght / 2.0f), 400.0f - (Lenght / 2.0f), 0.0f), 1);//ミニマップ生成
		AddGameObject<MiniMapPlayer>(Vec3(640.0f - (Lenght / 2.0f), 400.0f - (Lenght / 2.0f), 0.0f), 3.0f, 150.0f, Lenght);//ミニマップ上でPlayerの位置を表示
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
			//ミニマップを生成
			SetMiniMap();

			//地面を生成
			AddGameObject<Ground>();
			//ゲージを追加
			auto garge = AddGameObject<PieceGarge>(GetSharedGameObject<Player>(L"GamePlayer"));
			SetSharedGameObject(L"Garge", garge);
			auto PGarge = AddGameObject<PlayerGarge>();

			AddGameObject<TimeManager>();//時間制限

			//壁を出現（テスト）
			AddGameObject<BreakWall>(Vec3(5.0f, -0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(2.0f, 2.0f, 2.0f));
			AddGameObject<BreakWall>(Vec3(7.0f, -0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(2.0f, 2.0f, 2.0f));
			AddGameObject<BreakWall>(Vec3(3.0f, -0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(2.0f, 2.0f, 2.0f));
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

	void SanpeiStage::OnUpdate()
	{
		Vec3 PlayerPos = GetSharedGameObject<Player>(L"GamePlayer")->GetComponent<Transform>()->GetPosition();
		//デバック用
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
			AddGameObject<EscapeManager>(Vec3(-10.0f, 8.0f, -15.0f), Vec3(-10.0f, 2.0f, 0.0f), Vec3(-20.0f, 0.0f, 3.0f), Vec3(-3.0f, 0.0f, 8.0f), Vec3(-10.0f, 2.0f, 0.0f), Vec3(-10.0f, 2.0f, 26.0f));
			int test = 1;
			//カメラの設定
		   //auto camera = ObjectFactory::Create<Camera>();
		   //camera->SetEye(Vec3(0.0f, 15.0f, -5.0f));
		   //camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		   //m_View->SetCamera(camera);

		}
	}
}
//end basecross
