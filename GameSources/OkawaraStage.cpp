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
	void O_GameStage::CreateViewLight() {
		// カメラの設定
		//App::GetApp()->GetAssetsDirectory(dataDir);//今仮で使っているので実際に実装するときは下のを使う
		auto& app = App::GetApp();

		auto path = app->GetDataDirWString();
		auto texPath = path + L"Textures/";
		auto modPath = path + L"Models/";
		auto levelPath = path + L"Levels/"; 


		wstring strTexture = texPath + L"hakusi.jpg";
		app->RegisterTexture(L"White", strTexture);
		strTexture = texPath + L"arrow2.png";
		app->RegisterTexture(L"Arrow", strTexture);
		strTexture = texPath + L"Black.jpg";
		app->RegisterTexture(L"Black", strTexture);
		strTexture = texPath + L"InternalSkin.png";
		app->RegisterTexture(L"Internal", strTexture);

		wstring strModel = modPath;

		//auto staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(strModel, L"Sensuikan.bmf");
		//app->RegisterResource(L"Sensuikan_Mesh", staticMultiModelMesh);

		//スタティックモデル(マルチメッシュ)の通常リソース
		auto staticMultiModelMesh = MultiMeshResource::CreateStaticModelMultiMesh(modPath, L"Sensuikan.bmf");
		App::GetApp()->RegisterResource(L"Sensuikan_Mesh", staticMultiModelMesh);


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

	void O_GameStage::CreateBullet()
	{
		//弾生成　　引数は左から順番に初期位置→大きさ→スピード→角度（rad）→攻撃力 となっています
		auto Bulletptr = AddGameObject<Bullet>(Vec3(-1.0f, 0.5f, 0.0f), Vec3(0.3f, 0.3f, 0.3f), 1.0f, 0.0f, 1);
		Bulletptr->GetSpeed();
		//シェア配列にBulletを追加
		SetSharedGameObject(L"Bullet", Bulletptr);//これでAddしたゲームオブジェクトを取得できる
	}

	//Playerを追加する関数
	void O_GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>();
		SetSharedGameObject(L"GamePlayer", ptrPlayer);//ゲームオブジェクトを取得
		//auto ptrTarget = GetSharedObject(L"Bullet");//Addしたゲームオブジェクト(Bullet)を取得する

	}
	//レーダーを追加する関数
	void O_GameStage::CreateRadar()
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
	void O_GameStage::CreateEnemy()
	{
		auto ptrEnemy = AddGameObject<Enemy>();
		SetSharedGameObject(L"Enemy", ptrEnemy);//ゲームオブジェクトを取得
	}

	//敵の欠片を作成
	void O_GameStage::CreateEnemyPiece() {

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


	void O_GameStage::CreateBlock()
	{
		auto& app = App::GetApp();

		auto path = app->GetDataDirWString();

		const int MAP_ROWS = 30;
		const int MAP_COLS = 30;
		int stageMap[MAP_ROWS][MAP_COLS];
		auto levelPath = path + L"Levels/";


		// 外部ファイルからマップデータを読み込む
		ifstream ifs(levelPath + L"Pt_Wall2.csv");
		if (ifs)
		{
			int c = 0; // マップデータ参照用

			string line;
			while (getline(ifs, line)) // ファイルから1行読み取る
			{
				string data;
				istringstream ss(line); // 読み取った内容をストリームに変換する
				while (getline(ss, data, ',')) // そのストリームからカンマ区切りでデータを読み込む
				{
					int cellData = atoi(data.c_str()); // 読み取ったデータをint型に変換する
					stageMap[0][c++] = cellData; // マップデータにCSVのデータをコピーする
				}
			}
		}

		// ブロック（二次元配列の「1」の位置にブロックを置く）
		for (int r = 0; r < MAP_ROWS; r++)
		{
			for (int c = 0; c < MAP_COLS; c++)
			{
				Vec3 startPos(-0.0f, 0.0f, +0.0f); // 基準となるオフセット座標
				Vec3 pos(static_cast<float>(c), 0.5f, -static_cast<float>(r)); // ブロックの位置

				// 要素の値によってブロックを配置する
				switch (stageMap[r][c])
				{
				case 1:
					auto block = AddGameObject<Block>();
					auto blockTransComp = block->GetComponent<Transform>();
					blockTransComp->SetPosition(startPos + pos);

					break;
				}
			}
		}


	}

	void O_GameStage::OnCreate() {
		try {
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

			CreateBlock();
		}
		catch (...) {
			throw;
		}
	}
}
//end basecross
