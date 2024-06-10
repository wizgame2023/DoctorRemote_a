/*!
@file TutorialStage.cpp
@brief チュートリアルステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
//	ゲームステージクラス実体
//--------------------------------------------------------------------------------------

//ビューとライトの作成
	void TutorialStage::CreateViewLight() {


		// カメラの設定
		auto camera = ObjectFactory::Create<MainCamera>(180.0f);
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

	void TutorialStage::CreateEffect()//エフェクト生成
	{
		auto EffectPtr = AddGameObject<Effect>(L"PlayerEffectGreen", 0.5f, 8, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.1f, 0.1f, 0.1f));
		SetSharedGameObject(L"Effect", EffectPtr);
		auto EffectPtr2 = AddGameObject<EffectBreakWall>(L"PlayerEffectRed", 1.0f, 20, Vec3(0.2f, 0.6f, 0.2f), Vec3(0.4f, 0.4f, 0.4f));
		SetSharedGameObject(L"RedEffect", EffectPtr2);
		auto EffectPtr3 = AddGameObject<EffectMove>(L"GetEffect", 1.5f, 5, 1.0f, Vec3(0.0f, 1.3f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
		SetSharedGameObject(L"PlayerEffectWhite", EffectPtr3);
		auto EffectPtr4 = AddGameObject<EffectChase>(L"PlayerEffectRed", 1.0f, 15, 1.0f, Vec3(0.5f, 0.8f, 0.5f), Vec3(0.85f, 0.85f, 0.85f));
		SetSharedGameObject(L"EffectChase", EffectPtr4);
		EffectPtr4 = AddGameObject<EffectChase>(L"PlayerEffectGreen", 1.5f, 15, 1.0f, Vec3(0.0f, 0.5f, 0.0f), Vec3(0.8f, 0.8f, 0.8f));
		SetSharedGameObject(L"PlayerEffectRecovery", EffectPtr4);
	}


	//Playerを追加する関数
	void TutorialStage::CreatePlayer()//改善すべき点
	{
		float deg = 90.0f;
		float rad = XMConvertToRadians(deg);
		shared_ptr<Player> ptrPlayer = AddGameObject<Player>(Vec3(-27.5f, 0.5f, -13.0f), Vec3(0.0f, rad, 0.0f),4.0f);//Player生成
		SetSharedGameObject(L"GamePlayer", ptrPlayer);//ゲームオブジェクトを生成


	}
	//レーダーを追加する関数
	void TutorialStage::CreateRadar()
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
	void TutorialStage::CreateEnemy()
	{
		int randamEnemy = 0;
		randamEnemy = rand() % 4;
		shared_ptr<Enemy> ptrEnemy;
		ptrEnemy = AddGameObject<Enemy>(Vec3(15.5f, 0.5f, -7.0f), Vec3(-0.0f, 0.0f, 0.0f), Vec3(3.0f, 3.0f, 3.0f));
		SetSharedGameObject(L"Enemy", ptrEnemy);//ゲームオブジェクトを取得
	}

	//敵の欠片を作成
	void TutorialStage::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = {
			{//8				
				Vec3(-6.25f,1.0f,24.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//9
				Vec3(-4.56f,1.0f,40.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//10
				Vec3(-7.25f,1.0f,-45.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//11
				Vec3(28.9f,1.0f,-14.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)
			},
			{//12
				Vec3(45.0f,1.0f,-7.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//13
				Vec3(16.0f,1.0f,10.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)
			},
			{//14
				Vec3(12.0f,1.0f,41.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//15
				Vec3(0.6f,1.0f,34.3f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//16
				Vec3(10.0f,1.0f,20.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			}

		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<EnemyPiece>(v[0], v[1], v[2]);
		}
	}

	void TutorialStage::RandamPiecePosition(Vec3 originPosition)//引数を中心にランダムにかけらが置かれる
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

	void TutorialStage::CreateEnemyPiece2()
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

	void TutorialStage::CerateBreakEnemyPiece()//壊れる壁の先にあるかけら
	{

		Vec3 Pos[] = { Vec3(-26.0f,0.2f,1.0f),Vec3(-23.0f,0.2f,20.0f),Vec3(20.0f,0.2f,2.0f) };//BigPieceのPos一覧
		m_BigPieceLength = sizeof(Pos) / sizeof(Vec3);//BigPieceの合計の数
		for (int i = 0; i < m_BigPieceLength; i++)
		{
			auto Piece = AddGameObject<BigPiece>(Pos[i], Vec3(0.0f, 0.0f, 0.0f), Vec3(1.5f, 1.5f, 1.5f));//オブジェクトを生成する
			wstring Name = L"BigPiece";//オブジェクトの共通の名前を決める
			Name += to_wstring(i + 1);//オブジェクトの共通の名前にプラスして番号をふる　例：BigPiece1,BigPiece2
			SetSharedGameObject(Name, Piece);//生成したオブジェクトに名前を付ける
		}


		//AddGameObject<BigPiece>(Vec3(-26.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.3f, 1.3f, 1.3f));
		//AddGameObject<BigPiece>(Vec3(-23.0f, 0.0f, 20.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.3f, 1.3, 1.3f));
		//auto bigPiece = AddGameObject<BigPiece>(Vec3(-20.0f, 0.0f, 2.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.3f, 1.3f, 1.3f));
		//SetSharedGameObject(L"BigPiece", bigPiece);
	}


	void TutorialStage::CreateMap()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/";
		vector<vector<int>> stageMap;

		ifstream ifs(levelPath += L"Tutorial.csv");
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
				case 1:
					AddGameObject<Wall>(startPos + pos, Vec3(0, 0, 0), Vec3(37.0, 10, 1.0));
					break;

				case 2:
					AddGameObject<Wall>(startPos + pos, Vec3(0, 0, 0), Vec3(1.0, 10, 37.0));
					break;

				case 3:
					AddGameObject<BreakWall>(startPos + pos, Vec3(0, 0, 0), Vec3(1, 10, 3));
					break;
				case 4:
					AddGameObject<BreakWall>(startPos + pos, Vec3(0, XMConvertToRadians(45.0f), 0), Vec3(0.5, 10, 4.25));
					break;
				case 5:
					AddGameObject<BreakWall>(startPos + pos, Vec3(0, XMConvertToRadians(-45.0f), 0), Vec3(0.5, 10, 4.25));
					break;
				case 6:
					AddGameObject<Block>(startPos + pos, Vec3(0, 0, 0));
					break;
				case 7:
					AddGameObject<Block3>(blockStartPos + pos, Vec3(0, XMConvertToRadians(260.0f), 0), Vec3(20.0f, 10.0f, 20.0f));
					break;
				case 8:
					AddGameObject<BlockSecond>(startPos + pos, Vec3(0, 0, 0), Vec3(25.0f, 10.0f, 25.0f));
					break;
				}
			}

		}
	}

	void TutorialStage::CreateMiniMap()
	{
		float Lenght = 225.0f;//ミニマップの直径
		auto miniMap = AddGameObject<Sprite>(Lenght, Lenght, L"MiniMapTutorial", Vec3(640.0f - (Lenght / 2.0f) - 50.0f, 400.0f - (Lenght / 2.0f) - 50.0f, 0.0f), 5);//ミニマップ生成
		SetSharedGameObject(L"MiniMap", miniMap);

		AddGameObject<MiniMapPlayer>(Vec3(640.0f - (Lenght / 2.0f) - 50.0f, 400.0f - (Lenght / 2.0f) - 50.0f, 0.0f), 3.0f, 75.0f, Lenght);//ミニマップ上でPlayerの位置を表示

		Vec3 StartPos = Vec3(640.0f - (Lenght / 2.0f) - 50.0f, 400.0f - (Lenght / 2.0f) - 50.0f, 0.0f);
		float Bairitu = Lenght / 75.0f;//現在のミニマップの倍率(どれくらい引き延ばしているかを表す)

		for (int i = 0; i < m_BigPieceLength; i++)
		{
			wstring BigPieceName = L"BigPiece";//参照元の名前
			BigPieceName += to_wstring(i + 1);//番号振り分け
			wstring miniMapBigPieceName = L"MiniMapBigPiece";//参照元の名前
			miniMapBigPieceName += to_wstring(i + 1);//番号振り分け
			auto PiecePos = GetSharedGameObject<BigPiece>(BigPieceName)->GetComponent<Transform>()->GetPosition();//ビックピースの場所を取得
			auto miniMapBigPiece = AddGameObject<MiniMapBigPiece>(3.0f, 3.0f, L"MiniMapBigPiece", Vec3(StartPos.x + (PiecePos.x * Bairitu), StartPos.y + (PiecePos.z * Bairitu), 0.0f), 6, BigPieceName);
			SetSharedGameObject(miniMapBigPieceName, miniMapBigPiece);//ミニマップに表示されるビックピースの名前を決める
			GetSharedGameObject<BigPiece>(BigPieceName)->MyMiniMapName(miniMapBigPieceName);//ビックピースにミニマップのビックピースの名前を教える
		}


	}



	//BGMの再生
	void TutorialStage::BaseBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"ScaryBGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}
	void TutorialStage::BossBGM() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"BossBGM", XAUDIO2_LOOP_INFINITE, 0.3f);
	}
	void TutorialStage::OnDestroy()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void TutorialStage::CollisionActive(bool On)
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

	void TutorialStage::SetCollisionSwich(bool ONorOFF)
	{
	}


	void TutorialStage::OnCreate() {
		try {
			App::GetApp()->GetScene<Scene>()->SetGameStage(0);
			//テクスチャ、モデルの設定データ
			//auto data = AddGameObject<Data>();
			auto timeManager = AddGameObject<TimeManager>();//時間制限
			SetSharedGameObject(L"TimeManager", timeManager);
			//ビューとライトの作成
			CreateViewLight();
			//Effectの追加
			CreateEffect();
			//Playerを追加
			CreatePlayer();
			//敵のかけらを表示
			//CreateEnemyPiece();
			//CreateEnemyPiece2();//ランダムにかけらが出るようになる
			AddGameObject<RandCreateManager>(L"kakeraMapDateLevels.csv", 75, 7);//ランダムにかけらが出るようになる

			CerateBreakEnemyPiece();
			//CreateRecoveryWall();//治す壁を生成 現在没データ化
			AddGameObject<Ground>();//地面を生成
			CreateMap();//マップを生成
			CreateMiniMap();//ミニマップ生成
			//ゲージを追加
			auto garge = AddGameObject<PieceGarge2>();
			SetSharedGameObject(L"Garge", garge);
			auto PGarge = AddGameObject<PlayerGarge>();
			auto stageManager = AddGameObject<StageManager>();//ステージマネージャーを生成
			SetSharedGameObject(L"StageManager", stageManager);
			stageManager->SetStartFlag(false);
			auto collisionManager = AddGameObject<StageCollisionManager>();//コリジョンマネージャー
			SetSharedGameObject(L"StageCollisionManager",collisionManager);
			AddGameObject<JoinManager>(Vec3(-12.0f, 0.5f, -13.0f));//侵入のムービー
			//BGM
			BaseBGM();
			auto tutorialManager = AddGameObject<TutorialManager>();
			SetSharedGameObject(L"TutorialManager", tutorialManager);
		}
		catch (...) {
			throw;
		}
	}

	void TutorialStage::OnUpdate()
	{		
		//GetSharedGameObject<StageCollisionManager>(L"StageCollisionManager")->SetCollisionSwhich(false);//デバック用

		auto ptrPlayer = GetSharedGameObject<Player>(L"GamePlayer");
		if (ptrPlayer->GetRadarFlag() && m_CareerFlag == 0)
		{
			//敵を生成
			CreateEnemy();
			GetSharedGameObject<Enemy>(L"Enemy")->SetEnemy(true);
			//レーダーを生成
			CreateRadar();
			m_CareerFlag = 1;

			OnDestroy();
			BossBGM();
			GetSharedGameObject<StageManager>(L"StageManager")->SetCareerFlag(1);//進行度を進める



		}
		if (m_CareerFlag == 1)
		{
			m_CareerFlag = GetSharedGameObject<StageManager>(L"StageManager")->GetStageFlag();//進行度を更新
		}
		if (m_CareerFlag == 2)//敵を倒したとき
		{
			GetSharedGameObject<Radar>(L"Radar")->MyRemove();//レーダーを消去する

			AddGameObject<EscapeManager>(Vec3(-6.2f, 3.0f, -14.8f), Vec3(-27.0f, 0.5f, -14.5f), Vec3(-21.0f, 0.5f, -26.0f), Vec3(-10.0f, 0.5f, 5.8f), Vec3(-12.0f, 0.5f, -13.0f), Vec3(-27.5f, 0.5f, -14.5f));

			auto StartPos = GetSharedGameObject<Sprite>(L"MiniMap")->GetComponent<Transform>()->GetPosition();
			float Bairitu = 225.0f / 150.0f;//現在のミニマップの倍率(どれくらい引き延ばしているかを表す)
			AddGameObject<Sprite>(15.0f, 15.0f, L"White", StartPos + Vec3(-39.0f, -41.0f, 0.0f), 6);

			m_CareerFlag = 3;

			OnDestroy();
			BaseBGM();

		}

	}

}