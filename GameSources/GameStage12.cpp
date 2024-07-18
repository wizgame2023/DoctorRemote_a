/*!
@file GameStage12.cpp
@brief ゲームステージ12の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
//	ゲームステージクラス実体
//--------------------------------------------------------------------------------------

//ビューとライトの作成
	void GameStage12::CreateViewLight() {


		// カメラの設定
		auto camera = ObjectFactory::Create<MainCamera>(90.0f);
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

	void GameStage12::CreateEffect()//エフェクト生成
	{
		auto EffectPtr = AddGameObject<Effect>(L"PlayerEffectGreen", 0.5f, 8, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.1f, 0.1f, 0.1f));
		SetSharedGameObject(L"Effect", EffectPtr);
		auto EffectPtr2 = AddGameObject<EffectBreakWall>(L"SmokeEffect", 1.0f, 40);
		SetSharedGameObject(L"RedEffect", EffectPtr2);
		auto EffectPtr3 = AddGameObject<EffectMove>(L"GetEffect", 1.5f, 5, 1.0f, Vec3(0.0f, 1.3f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
		SetSharedGameObject(L"PlayerEffectWhite", EffectPtr3);
		auto EffectPtr4 = AddGameObject<EffectMove>(L"EnemyDamageEffect", 1.5f, 30, 1.0f, Vec3(0.0f, 3.0f, 0.0f), Vec3(0.7f, 0.7f, 0.7f));
		SetSharedGameObject(L"EnemyEffectPurple", EffectPtr4);
		auto EffectPtr5 = AddGameObject<EffectMove>(L"EnemyPieceEffect", 0.7f, 10, 1.0f, Vec3(1.0f, 1.0f, 0.0f), Vec3(0.3f, 0.3f, 0.3f));
		SetSharedGameObject(L"EnemyPieceEffectPurple", EffectPtr5);
		auto EffectPtr6 = AddGameObject<EffectMove>(L"BigPieceEffect", 1.5f, 15, 1.0f, Vec3(1.0f, 1.0f, 0.0f), Vec3(0.5f, 0.5f, 0.5f));
		SetSharedGameObject(L"BigPieceEffectPurple", EffectPtr6);
		auto EffectPtr7 = AddGameObject<EffectChase>(L"PlayerEffectRed", 1.0f, 15, 1.0f, Vec3(0.5f, 0.8f, 0.5f), Vec3(0.85f, 0.85f, 0.85f));
		SetSharedGameObject(L"EffectChase", EffectPtr7);
		EffectPtr7 = AddGameObject<EffectChase>(L"PlayerEffectGreen", 1.5f, 15, 1.0f, Vec3(0.0f, 0.5f, 0.0f), Vec3(0.8f, 0.8f, 0.8f));
		SetSharedGameObject(L"PlayerEffectRecovery", EffectPtr7);
	}


	//Playerを追加する関数
	void GameStage12::CreatePlayer()//改善すべき点
	{
		//Playerの出現場所を決める
		float deg = -180;
		float rad = XMConvertToRadians(deg);
		shared_ptr<Player> ptrPlayer = AddGameObject<Player>(Vec3(0.0f, 0.5f, 0.0f), Vec3(0.0f, rad, 0.0f),1.7f);
		SetSharedGameObject(L"GamePlayer", ptrPlayer);//ゲームオブジェクトを生成

	}
	//レーダーを追加する関数
	void GameStage12::CreateRadar()
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
	void GameStage12::CreateEnemy()
	{
		auto ptrEnemy = AddGameObject<Enemy>(Vec3(-60.0f, 0.5f, 13.0f), Vec3(-0.0f, 0.0f, 0.0f), Vec3(3.0f, 3.0f, 3.0f));
		SetSharedGameObject(L"Enemy", ptrEnemy);//ゲームオブジェクトを取得
		auto EnemyPos = ptrEnemy->GetComponent<Transform>()->GetPosition();
		EnemyPos.y = 0.5;
		//Enemyのムービーシーン
		AddGameObject<EnemyMovieManager>(EnemyPos+Vec3(0.0f,0.0f,5.0f), Vec3(30.0f, 0.1f, 30.0f), Vec3(-56.6f, 4.0f, 2.27f), EnemyPos);

	}

	//敵の欠片を作成
	void GameStage12::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = {
			{//1			
				Vec3(7.0f,0.1f,-25.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//2
				Vec3(-6.0f,0.1f,-45.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//3
				Vec3(32.0f,0.1f,-14.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//4
				Vec3(42.0f,0.1f,-27.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)
			},
			{//5
				Vec3(34.0f,0.1f,-22.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//6
				Vec3(15.0f,0.1f,29.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)
			},
			{//7
				Vec3(19.0f,0.1f,38.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//8
				Vec3(12.0f,0.1f,36.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//9
				Vec3(-25.0f,0.1f,4.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//10
				Vec3(-23.0f,0.1f,18.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//11
				Vec3(-21.0f,0.1f,31.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//12
				Vec3(-31.0f,0.1f,-34.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//13
				Vec3(-8.0f,0.1f,29.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			}


		};
		//オブジェクトの作成
		for (auto v : vec) {
			auto& piece = AddGameObject<EnemyPiece>(v[0], v[1], v[2]);
			PieceManager::enemyPieces.push_back(piece);
		}
	}

	void GameStage12::RandamPiecePosition(Vec3 originPosition)//引数を中心にランダムにかけらが置かれる
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

	void GameStage12::CreateEnemyPiece2()
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

	void GameStage12::CerateBreakEnemyPiece()//壊れる壁の先にあるかけら
	{
		Vec3 Pos[] = { Vec3(30.0f,0.3f,30.0f),Vec3(-35.0f,0.3f, -15.0f),Vec3(-58.0f,0.3f,45.0f),Vec3(45.0f,0.3f,-9.0f),Vec3(-11.0f,0.3f,38.0f),Vec3(21.0f,0.3f,-37.0f) };//BigPieceのPosision一覧
		m_BigPieceLength = sizeof(Pos) / sizeof(Vec3);//BigPieceの合計の数

		for (int i = 0; i < m_BigPieceLength; i++)
		{
			int randMesh = rand() % 3 + 1;//ランダムにどのどのメッシュになるかが決まる
			auto Piece = AddGameObject<BigPiece>(Pos[i], Vec3(0.0f, 0.0f, 0.0f), Vec3(3.5f, 3.5f, 3.5f), randMesh);//オブジェクトを生成する
			wstring Name = L"BigPiece";//オブジェクトの共通の名前を決める
			Name += to_wstring(i + 1);//オブジェクトの共通の名前にプラスして番号をふる　例：BigPiece1,BigPiece2
			SetSharedGameObject(Name, Piece);//生成したオブジェクトに名前を付ける
		}

	}


	void GameStage12::CreateMap()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/";
		vector<vector<int>> stageMap;

		ifstream ifs(levelPath += L"Level_9.csv");
		if (ifs)
		{
			string line;
			while (getline(ifs, line))
			{
				vector<int> mapData;

				line += ",";
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

		//ミニマップ表示のために使用
		float SpriteLenght = 225.0f;
		Vec3 SpriteStartPos = Vec3(640.0f - (SpriteLenght / 2.0f) - 50.0f, 400.0f - (SpriteLenght / 2.0f) - 50.0f, 0.0f);

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
					AddGameObject<Wall>(startPos + pos, Vec3(0, 0, 0), Vec3(140.0, 10, 1.0));
					break;
				case 2:
					AddGameObject<Wall>(startPos + pos, Vec3(0, 0, 0), Vec3(1.0, 10, 140.0));
					break;
				case 3:
					AddGameObject<Wall>(startPos + pos, Vec3(0, 0, 0), Vec3(3.0, 10, 1.0));
					break;
				case 4:
					AddGameObject<Wall>(startPos + pos, Vec3(0, 0, 0), Vec3(1.0, 10, 3.0));
					break;
				case 5:
					AddGameObject<Wall>(startPos + pos, Vec3(0, XMConvertToRadians(45.0f), 0), Vec3(0.5, 10, 4.25));
					break;
				case 6:
					AddGameObject<Wall>(startPos + pos, Vec3(0, XMConvertToRadians(-45.0f), 0), Vec3(0.5, 10, 4.25));
					break;
				case 7:
					AddGameObject<BreakWall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, XMConvertToRadians(90.0f), 0), Vec3(1, 10, 3), 150, SpriteLenght, SpriteStartPos);
					AddGameObject<Wall>(startPos + pos + Vec3(0.0f, 10.0f, 0.0f), Vec3(0, XMConvertToRadians(90.0f), 0), Vec3(0.5f, 1.0f, 3.0f));
					break;
				case 8:
					AddGameObject<BreakWall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, 0, 0), Vec3(1, 10, 3), 150, SpriteLenght, SpriteStartPos);
					AddGameObject<Wall>(startPos + pos + Vec3(0.0f, 10.0f, 0.0f), Vec3(0, 0, 0), Vec3(1.0f, 1.0f, 3.0f));
					break;
				case 9:
					AddGameObject<BreakWall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, XMConvertToRadians(45.0f), 0), Vec3(0.5, 10, 4.25), 150, SpriteLenght, SpriteStartPos);
					AddGameObject<Wall>(startPos + pos + Vec3(0.0f, 10.0f, 0.0f), Vec3(0, XMConvertToRadians(45.0f), 0), Vec3(0.5f, 1.0f, 4.25f));
					break;
				case 10:
					AddGameObject<BreakWall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, XMConvertToRadians(-45.0f), 0), Vec3(0.5, 10, 4.25), 150, SpriteLenght, SpriteStartPos);
					AddGameObject<Wall>(startPos + pos + Vec3(0.0f, 10.0f, 0.0f), Vec3(0, XMConvertToRadians(-45.0f), 0), Vec3(0.5f, 1.0f, 4.25f));
					break;
				case 11:
					AddGameObject<Block>(blockStartPos + pos, Vec3(0, 0, 0));
					break;
				case 12:
					AddGameObject<BlockSecond>(startPos + pos, Vec3(0, 0, 0), Vec3(20.0f, 10.0f, 20.0f));
					break;
				case 13:
					AddGameObject<Block3>(startPos + pos, Vec3(0, 0, 0), Vec3(25.0f, 10.0f, 25.0f));
					break;
				case 14:
					AddGameObject<Wall>(startPos + pos, Vec3(0, 0, 0), Vec3(21.0, 10, 1.0));
					break;
				}

			}

		}
	}

	void GameStage12::CreateMiniMap()
	{
		float Lenght = 225.0f;//ミニマップの直径	
		Vec3 StartPos = Vec3(640.0f - (Lenght / 2.0f) - 50.5f, 400.0f - (Lenght / 2.0f) - 50.0f, 0.0f);
		float Bairitu = Lenght / 150.0f;//現在のミニマップの倍率(どれくらい引き延ばしているかを表す)

		auto miniMap = AddGameObject<Sprite>(Lenght, Lenght, L"MiniMapStage9", StartPos, 5);//ミニマップ生成
		SetSharedGameObject(L"MiniMap", miniMap);

		auto miniMapPlayer = AddGameObject<MiniMapPlayer>(StartPos, 4.0f, 150.0f, Lenght);//ミニマップ上でPlayerの位置を表示
		SetSharedGameObject(L"MiniMapPlayer", miniMapPlayer);


		//BigPieceの場所をミニマップに映す
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
	void GameStage12::BaseBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"ScaryBGM", XAUDIO2_LOOP_INFINITE, 0.3f);
	}
	void GameStage12::BossBGM() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"BossBGM", XAUDIO2_LOOP_INFINITE, 0.3f);
	}
	void GameStage12::OnDestroy()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameStage12::CollisionActive(bool On)
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

	void GameStage12::SetCollisionSwich(bool ONorOFF)
	{
	}


	void GameStage12::OnCreate() {
		try {
			auto scene = App::GetApp()->GetScene<Scene>();
			scene->SetGameStage(9);
			scene->SetPlayFlag(true);

			auto stageManager = AddGameObject<StageManager>();//ステージマネージャーを生成
			SetSharedGameObject(L"StageManager", stageManager);

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
			CreateEnemyPiece();
			//CreateEnemyPiece2();//ランダムにかけらが出るようになる
			AddGameObject<RandCreateManager>(L"kakeraMapLevel9.csv", 150, 70);//ランダムにかけらが出るようになる

			CerateBreakEnemyPiece();
			//CreateRecoveryWall();//治す壁を生成 現在没データ化
			AddGameObject<Ground>();//地面を生成
			CreateMap();//マップを生成
			CreateMiniMap();//ミニマップ生成
			auto stageCollsionManager = AddGameObject<StageCollisionManager>();//コリジョンマネージャー追加
			SetSharedGameObject(L"StageCollisionManager", stageCollsionManager);
			AddGameObject<JoinManager>(Vec3(0.0f, 0.5f, 0.0f), Vec3(0.0f, 0.5f, -13.0f));//導入を追加

			//BGM
			BaseBGM();

			////敵を生成
			//CreateEnemy();
			//GetSharedGameObject<Enemy>(L"Enemy")->SetEnemy(true);
			////レーダーを生成
			//CreateRadar();
			//m_CareerFlag = 1;


		}
		catch (...) {
			throw;
		}
	}

	void GameStage12::OnUpdate()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"GamePlayer");
		//GetSharedGameObject<StageCollisionManager>(L"StageCollisionManager")->SetCollisionSwhich(false);//デバック用
		//CollisionActive(true);
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
		if (m_CareerFlag == 1 || m_CareerFlag == 2)
		{
			m_CareerFlag = GetSharedGameObject<StageManager>(L"StageManager")->GetStageFlag();//進行度を更新
		}
		if (m_CareerFlag == 3)//敵を倒したとき
		{
			AddGameObject<EscapeManager>(Vec3(0.0f, 3.0f, -18.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(-9.0f, 0.5f, -17.0f), Vec3(9.0f, 0.5f, -12.0f), Vec3(0.0f, 0.5f, -13.0f), Vec3(0.0f, 0.5f, 0.0f), 100);
			AddGameObject<EscapeManager>(Vec3(0.0f, 3.0f, 20.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(-9.0f, 0.5f, 12.0f), Vec3(9.0f, 0.5f, 17.0f), Vec3(0.0f, 0.5f, 10.0f), Vec3(0.0f, 0.5f, 0.0f), 100);

			GetSharedGameObject<StageManager>(L"StageManager")->SetCareerFlag(4);//進行度を更新
			m_CareerFlag = 4;

			OnDestroy();
			BaseBGM();

		}

	}


}