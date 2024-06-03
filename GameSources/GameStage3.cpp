/*!
@file TitleStage.cpp
@brief タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
//	ゲームステージクラス実体
//--------------------------------------------------------------------------------------

//ビューとライトの作成
	void GameStage3::CreateViewLight() {


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

	void GameStage3::CreateEffect()//エフェクト生成
	{
		auto EffectPtr = AddGameObject<Effect>(L"PlayerEffectGreen", 0.5f, 8, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.1f, 0.1f, 0.1f));
		SetSharedGameObject(L"Effect", EffectPtr);
		auto EffectPtr2 = AddGameObject<EffectBreakWall>(L"PlayerEffectRed", 1.0f, 20, Vec3(0.2f, 0.6f, 0.2f), Vec3(0.4f, 0.4f, 0.4f));
		SetSharedGameObject(L"RedEffect", EffectPtr2);
		auto EffectPtr3 = AddGameObject<EffectMove>(L"PlayerEffectWhite", 1.5f, 15, 1.0f, Vec3(0.0f, 1.3f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
		SetSharedGameObject(L"PlayerEffectWhite", EffectPtr3);
		auto EffectPtr4 = AddGameObject<EffectChase>(L"PlayerEffectRed", 1.0f, 15, 1.0f, Vec3(0.5f, 0.8f, 0.5f), Vec3(0.85f, 0.85f, 0.85f));
		SetSharedGameObject(L"EffectChase", EffectPtr4);
		EffectPtr4 = AddGameObject<EffectChase>(L"PlayerEffectGreen", 1.5f, 15, 1.0f, Vec3(0.0f, 0.5f, 0.0f), Vec3(0.8f, 0.8f, 0.8f));
		SetSharedGameObject(L"PlayerEffectRecovery", EffectPtr4);
	}


	//Playerを追加する関数
	void GameStage3::CreatePlayer()//改善すべき点
	{
		int randamPlayer = 0;
		randamPlayer = rand() % 3;
		shared_ptr<Player> ptrPlayer;
		//randamPlayer = 0;//デバック
		//shared_ptr<GameObject> nanasiObject;
		//ランダムにPlayerの出現場所が決まる
		float deg = -90;
		float rad = XMConvertToRadians(deg);
		switch (randamPlayer)
		{
		case 0:
			ptrPlayer = AddGameObject<Player>(Vec3(10.0f, 0.5f, -40.0f), Vec3(0.0f, rad, 0.0f));
			break;
		case 1:
			ptrPlayer = AddGameObject<Player>(Vec3(-60.0f, 0.5f, 63.0f), Vec3(0.0f, rad, 0.0f));
			break;
		case 2:
			ptrPlayer = AddGameObject<Player>(Vec3(60.0f, 0.5f, 10.0f), Vec3(0.0f, rad, 0.0f));
			break;

		default:
			ptrPlayer = AddGameObject<Player>();
			break;
		}
		SetSharedGameObject(L"GamePlayer", ptrPlayer);//ゲームオブジェクトを生成


	}
	//レーダーを追加する関数
	void GameStage3::CreateRadar()
	{
		auto ptrPlayer = GetSharedObject(L"GamePlayer");//GamePlayerというオブジェクトを取得
		auto PlayerTrans = ptrPlayer->GetComponent<Transform>();//そのオブジェクトのTransformを取得
		auto PlayerPos = PlayerTrans->GetPosition();//Positionを取得
		auto ptrEnemy = GetSharedObject(L"Enemy");//Enemyというオブジェクトを取得
		auto EnemyTrans = ptrEnemy->GetComponent<Transform>();//そのオブジェクトのTransformを取得
		auto EnemyPos = EnemyTrans->GetPosition();//Positionを取得
		auto ptrRadar = AddGameObject<Radar>(PlayerPos, EnemyPos);//レーダーを生成
		SetSharedGameObject(L"Radar", ptrRadar);
	}

	//敵を作成
	void GameStage3::CreateEnemy()
	{
		int randamEnemy = 0;
		randamEnemy = rand() % 4;
		shared_ptr<Enemy> ptrEnemy;
		switch (randamEnemy)
		{
		case 0:
			ptrEnemy = AddGameObject<Enemy>(Vec3(-40.0f, 0.5f, -9.0f), Vec3(-0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
			break;
		case 1:
			ptrEnemy = AddGameObject<Enemy>(Vec3(-58.0f, 0.5f, 65.0f), Vec3(-0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
			break;
		case 2:
			ptrEnemy = AddGameObject<Enemy>(Vec3(41.0f, 0.5f, 63.0f), Vec3(-0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
			break;
		case 3:
			ptrEnemy = AddGameObject<Enemy>(Vec3(24.0f, 0.5f, -9.0f), Vec3(-0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
			break;
		default:
			break;
		}
		SetSharedGameObject(L"Enemy", ptrEnemy);//ゲームオブジェクトを取得
	}

	//敵の欠片を作成
	void GameStage3::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = {
			{//8				
				Vec3(-6.25f,1.0f,24.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.0f,1.0f,1.0f)

			},
			{//9
				Vec3(-4.56f,1.0f,40.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.0f,1.0f,1.0f)

			},
			{//10
				Vec3(-7.25f,1.0f,-45.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.0f,1.0f,1.0f)

			},
			{//11
				Vec3(28.9f,1.0f,-14.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.0f,1.0f,1.0f)
			},
			{//12
				Vec3(45.0f,1.0f,-7.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.0f,1.0f,1.0f)

			},
			{//13
				Vec3(16.0f,1.0f,10.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.0f,1.0f,1.0f)
			},
			{//14
				Vec3(12.0f,1.0f,41.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.0f,1.0f,1.0f)

			},
			{//15
				Vec3(0.6f,1.0f,34.3f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.0f,1.0f,1.0f)

			},
			{//16
				Vec3(10.0f,1.0f,20.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.0f,1.0f,1.0f)

			}

		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<EnemyPiece>(v[0], v[1], v[2]);
		}
	}

	void GameStage3::RandamPiecePosition(Vec3 originPosition)//引数を中心にランダムにかけらが置かれる
	{
		int randamCount = 0;
		randamCount = rand() % 9 + 1;
		randamCount = 5;

		Vec3 rotate = Vec3();
		Vec3 size = Vec3(1.0f, 1.0f, 1.1f);
		vector<Vec3> Trans;
		srand(time(0));//ランダムリセット

		for (int i = 0; i < randamCount; i++)
		{

			int x = rand() % 19 + 1;//ランダムに中心点からx座標がどれくらい離れているか決める

			srand(rand() * rand() % 7);

			int z = rand() % 19 + 1;//ランダムに中心点からy座標がどれくらい離れているか決める
			x - 10; z - 10;//これで離れている座標の差にマイナスを入れる ここ計算式意味ない書き方している可能性あり

			Vec3 Pos = Vec3(originPosition.x + x, originPosition.y, originPosition.z + z);//これでランダムにピースを置くことができる
			Trans.push_back(Pos);

		}
		for (auto i : Trans)
		{
			AddGameObject<EnemyPiece>(i, rotate, size);
		}

	}

	void GameStage3::CreateEnemyPiece2()
	{
		Vec3 lowerLeft = Vec3(-27.6f, 0.0f, -18.4f);//左下
		Vec3 lowerRight = Vec3(20.0f, 0.0f, -43.0f);//右下
		Vec3 upLeft = Vec3(-68.0f, 0.0f, 12.0f);//左上
		Vec3 upRight = Vec3(9.0f, 0.0f, 68.0f);//右上

		RandamPiecePosition(lowerLeft);
		RandamPiecePosition(lowerRight);
		RandamPiecePosition(upLeft);
		RandamPiecePosition(upRight);

	}

	void GameStage3::CerateBreakEnemyPiece()//壊れる壁の先にあるかけら
	{
		int randam = rand() % 3;
		randam = 0;
		//右上
		AddGameObject<BigPiece>(Vec3(10.0f, 0.0f, 6.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f));
		AddGameObject<BigPiece>(Vec3(4.0f, 0.0f, 20.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f));
		//左上
		AddGameObject<BigPiece>(Vec3(-5.0f, 0.0f, 46.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 0.5, 0.5f));
		//右下
		AddGameObject<BigPiece>(Vec3(67.0f, 0.0f, -60.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f));
		AddGameObject<BigPiece>(Vec3(65.0f, 0.0f, -54.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f));
		AddGameObject<BigPiece>(Vec3(70.0f, 0.0f, -31.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f));

		//左下
		AddGameObject<BigPiece>(Vec3(-40.0f, 0.0f, -50.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f));
	}


	void GameStage3::CreateMap()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/";
		vector<vector<int>> stageMap;

		ifstream ifs(levelPath += L"Level_3.csv");
		if (ifs)
		{
			string line;
			while (getline(ifs, line))
			{
				vector<int> mapData;

				string data;
				istringstream ss(line);
				while (getline(ss, data, ','))
				{
					int cellData = atoi(data.c_str());
					mapData.push_back(cellData);
				}

				stageMap.push_back(mapData);
			}
		}
		float stageW = static_cast<float>(stageMap[0].size());
		float stageD = static_cast<float>(stageMap.size());

		for (int r = 0; r < stageMap.size(); r++)
		{
			for (int c = 0; c < stageMap[0].size(); c++)
			{
				Vec3 startPos(-stageW * 0.5f + 0.5f, 2.5f, +stageD * 0.5f - 0.5f);
				Vec3 blockStartPos(-stageW * 0.5f + 0.5f, 1.5f, +stageD * 0.5f - 0.5f);
				Vec3 pos(static_cast<float>(c), 0.5f, -static_cast<float>(r));
				switch (stageMap[r][c])
				{
					{
						Vec3 startPos(-stageW * 0.5f + 0.5f, 0.0f, +stageD * 0.5f - 0.5f);
						Vec3 blockStartPos(-stageW * 0.5f + 0.5f, 1.25f, +stageD * 0.5f - 0.5f);
						Vec3 pos(static_cast<float>(c), 0.5f, -static_cast<float>(r));
						switch (stageMap[r][c])
						{
						case 1:
							AddGameObject<Wall>(startPos + pos, Vec3(0, 0, 0), Vec3(3.0, 10, 1.0));
							break;

						case 2:
							AddGameObject<Wall>(startPos + pos, Vec3(0, 0, 0), Vec3(1.0, 10, 3.0));
							break;

						case 3:

							AddGameObject<Wall>(startPos + pos, Vec3(0, XMConvertToRadians(45.0f), 0), Vec3(0.5, 10, 4.25));
							break;

						case 4:
							AddGameObject<Wall>(startPos + pos, Vec3(0, XMConvertToRadians(-45.0f), 0), Vec3(0.5, 10, 4.25));
							break;
						case 5:
							AddGameObject<BreakWall>(startPos + pos, Vec3(0, 0, 0), Vec3(3, 10, 1));
							break;
						case 6:
							AddGameObject<BreakWall>(startPos + pos, Vec3(0, 0, 0), Vec3(1, 10, 3));
							break;
						case 7:
							AddGameObject<BreakWall>(startPos + pos, Vec3(0, XMConvertToRadians(45.0f), 0), Vec3(0.5, 10, 4.25));
							break;
						case 8:
							AddGameObject<BreakWall>(startPos + pos, Vec3(0, XMConvertToRadians(-45.0f), 0), Vec3(0.5, 10, 4.25));
							break;
						case 9:
							AddGameObject<Block>(blockStartPos + pos, Vec3(0, 0, 0));
							break;
						case 10:
							AddGameObject<BlockSecond>(startPos + pos, Vec3(0, 0, 0), Vec3(20.0f, 10.0f, 20.0f));
							break;
						case 11:
							AddGameObject<BlockSecond>(startPos + pos, Vec3(0, 0, 0), Vec3(25.0f, 10.0f, 25.0f));
							break;
						case 14:
							AddGameObject<Wall>(startPos + pos, Vec3(0, 0, 0), Vec3(2.0, 10, 1.0));
							break;
						}
					}
				}

			}

		}
	}

	void GameStage3::CreateMiniMap()
	{
		float Lenght = 225.0f;//ミニマップの直径
		auto miniMap = AddGameObject<Sprite>(Lenght, Lenght, L"MiniMap", Vec3(640.0f - (Lenght / 2.0f), 400.0f - (Lenght / 2.0f), 0.0f), 1);//ミニマップ生成
		AddGameObject<MiniMapPlayer>(Vec3(640.0f - (Lenght / 2.0f), 400.0f - (Lenght / 2.0f), 0.0f), 3.0f, 150.0f, Lenght);//ミニマップ上でPlayerの位置を表示

	}



	//BGMの再生
	void GameStage3::BaseBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"ScaryBGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}
	void GameStage3::BossBGM() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"BossBGM", XAUDIO2_LOOP_INFINITE, 0.3f);
	}
	void GameStage3::OnDestroy()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameStage3::CollisionActive(bool On)
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"GamePlayer");
		auto PlayerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();

		if (On == true)
		{
			AABB CollisionActiveArea = AABB(PlayerPos + Vec3(-50.0f, -50.0f, -50.0f), PlayerPos + Vec3(50.0f, 50.0f, 50.0f));
			GetCollisionManager()->SetRootAABB(CollisionActiveArea);
		}
		if (On == false)
		{
			AABB CollisionActiveArea = AABB(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
			GetCollisionManager()->SetRootAABB(CollisionActiveArea);
		}

	}

	void GameStage3::SetCollisionSwich(bool ONorOFF)
	{
	}


	void GameStage3::OnCreate() {
		try {
			//テクスチャ、モデルの設定データ
			//auto data = AddGameObject<Data>();
			AddGameObject<TimeManager>();//時間制限
			//ビューとライトの作成
			CreateViewLight();
			//Effectの追加
			CreateEffect();
			//Playerを追加
			CreatePlayer();
			//敵のかけらを表示
			CreateEnemyPiece();
			CreateEnemyPiece2();//ランダムにかけらが出るようになる
			CerateBreakEnemyPiece();
			//CreateRecoveryWall();//治す壁を生成 現在没データ化
			AddGameObject<Ground>();//地面を生成
			CreateMap();//マップを生成
			CreateMiniMap();//ミニマップ生成
			//CreateWall();//これでステージの壁を作る
			//CreateBreakWall();//壊れる壁の作成
			//CreateBlockSecond();
			//CreateBlock();//障害物を生成
			//ゲージを追加
			auto garge = AddGameObject<PieceGarge2>();
			SetSharedGameObject(L"Garge", garge);
			auto PGarge = AddGameObject<PlayerGarge>();
			auto stageManager = AddGameObject<StageManager>();//ステージマネージャーを生成
			SetSharedGameObject(L"StageManager", stageManager);

			//BGM
			BaseBGM();

		}
		catch (...) {
			throw;
		}
	}

	void GameStage3::OnUpdate()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"GamePlayer");
		CollisionActive(true);
		if (ptrPlayer->GetRadarFlag() && m_PieceFlag == 0)
		{
			//敵を生成
			CreateEnemy();
			//レーダーを生成
			CreateRadar();
			m_PieceFlag = 1;

			OnDestroy();
			BossBGM();
		}

	}

}