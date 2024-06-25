/*!
@file GameStage4.cpp
@brief ゲームステージ4の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void GameStage4::CreateViewLight() {


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

	}

	void GameStage4::CreateEffect()//エフェクト生成
	{
		auto EffectPtr = AddGameObject<Effect>(L"PlayerEffectGreen", 0.5f, 8, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.1f, 0.1f, 0.1f));
		SetSharedGameObject(L"Effect", EffectPtr);
		auto EffectPtr2 = AddGameObject<EffectBreakWall>(L"SmokeEffect", 1.0f, 40);
		SetSharedGameObject(L"RedEffect", EffectPtr2);
		auto EffectPtr3 = AddGameObject<EffectMove>(L"GetEffect", 1.5f, 5, 1.0f, Vec3(0.0f, 1.3f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
		SetSharedGameObject(L"PlayerEffectWhite", EffectPtr3);
		auto EffectPtr4 = AddGameObject<EffectChase>(L"PlayerEffectRed", 1.0f, 10, 1.0f, Vec3(0.5f, 0.8f, 0.5f), Vec3(0.85f, 0.85f, 0.85f));
		SetSharedGameObject(L"EffectChase", EffectPtr4);
		EffectPtr4 = AddGameObject<EffectChase>(L"PlayerEffectGreen", 1.5f, 15, 1.0f, Vec3(0.0f, 0.5f, 0.0f), Vec3(0.8f, 0.8f, 0.8f));
		SetSharedGameObject(L"PlayerEffectRecovery", EffectPtr4);
	}


	//Playerを追加する関数
	void GameStage4::CreatePlayer()//改善すべき点
	{
		//Playerの出現場所を決める
		float deg = -180;
		float rad = XMConvertToRadians(deg);
		shared_ptr<Player> ptrPlayer= AddGameObject<Player>(Vec3(0.0f,0.5f,0.0f),Vec3(0.0f,rad,0.0f),100.0f);//1.7f
		SetSharedGameObject(L"GamePlayer", ptrPlayer);//ゲームオブジェクトを生成

	}
	//レーダーを追加する関数
	void GameStage4::CreateRadar()
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
	void GameStage4::CreateEnemy()
	{
		int randamEnemy = 3;
		randamEnemy = rand() % 4;
		shared_ptr<Enemy> ptrEnemy;
		switch (randamEnemy)
		{
		case 0:
			ptrEnemy = AddGameObject<Enemy>(Vec3(-22.0f, 0.5f, -42.0f), Vec3(-0.0f, 0.0f, 0.0f), Vec3(0.8f, 0.8f, 0.8f));
			break;
		case 1:
			ptrEnemy = AddGameObject<Enemy>(Vec3(-34.0f, 0.5f, 35.0f), Vec3(-0.0f, 0.0f, 0.0f), Vec3(0.8f, 0.8f, 0.8f));
			break;
		case 2:
			ptrEnemy = AddGameObject<Enemy>(Vec3(44.0f, 0.5f, 35.0f), Vec3(-0.0f, 0.0f, 0.0f), Vec3(0.8f, 0.8f, 0.8f));
			break;
		case 3:
			ptrEnemy = AddGameObject<Enemy>(Vec3(60.5f, 0.5f, -64.0f), Vec3(-0.0f, 0.0f, 0.0f), Vec3(0.8f, 0.8f, 0.8f));
			break;
		default:
			break;
		}	
		SetSharedGameObject(L"Enemy", ptrEnemy);//ゲームオブジェクトを取得
	}

	//固定の敵の欠片を作成
	void GameStage4::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = {
			{//8				
				Vec3(-6.25f,0.1f,24.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//9
				Vec3(-4.56f,0.1f,40.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//10
				Vec3(-7.25f,0.1f,-45.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},			
			{//11
				Vec3(27.7f,0.1f,-9.1f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)
			},
			{//12
				Vec3(31.0f,0.1f,-6.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//13
				Vec3(39.0f,0.1f,6.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)
			},
			{//14
				Vec3(29.0f,0.1f,15.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},
			{//15
				Vec3(13.0f,0.1f,44.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(2.0f,2.0f,2.0f)

			},

		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<EnemyPiece>(v[0], v[1], v[2]);
		}
		
		//for(auto a : Get)
	}

	void GameStage4::RandamPiecePosition(Vec3 originPosition)//引数を中心にランダムにかけらが置かれる 消去予定
	{
		int randamCount = 0;
		randamCount = rand() % 9 + 1;
		randamCount = 5;

		Vec3 rotate = Vec3();
		Vec3 size = Vec3(1.0f, 1.0f, 1.0f);
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

	void GameStage4::CreateEnemyPiece2()//ランダムな場所にかけらを生成する
	{

		auto& app = App::GetApp();
		auto path = app->GetDataDirWString();
		auto levelPath = path + L"Levels/";

		vector<vector<int>> kakeraMap;//マップの2次元座標を表す変数

		ifstream ifs(levelPath + L"kakeraMapDateLevels.csv");
		if (ifs)
		{
			string line;
			while (getline(ifs, line))
			{
				vector<int> datas;

				string data;
				istringstream ss(line);
				while (getline(ss, data, ','))
				{
					int cellData = atoi(data.c_str());//読み取ったデータをint型に変換する
					datas.push_back(cellData);//マップデータにCSVのデータをコピーする
				}

				kakeraMap.push_back(datas);//マップデータを一行一行入れていく
			}
		}

		int count = 0;//どれくらい生成したか数える
		while (count < 30)
		{
			int kakeraPosX = (rand() % 1500) - 750;//ランダムにかけらの場所を決める
			float fKakeraPosX = (float)kakeraPosX / 10;//floatに変更
			int kakeraPosZ = (rand() % 1500) - 750;//ランダムにかけらの場所を決める
			float fKakeraPosZ = (float)kakeraPosZ / 10;//floatに変更
			Vec3 Pos(fKakeraPosX, 0.1f, fKakeraPosZ);//かけらの場所

			int charkX = (int)fKakeraPosX+75;//小数点切り捨て
			int charkZ = (int)fKakeraPosZ+75;//小数点切り捨て
			int testyou = 0;//デバック用変数

			switch (kakeraMap[charkZ][charkX])
			{
			case 0:
				AddGameObject<EnemyPiece>(Pos, Vec3(), Vec3(1.25f, 1.25f, 1.25f));//オブジェクト生成
				count++;//カウント
			default:
				break;
			}
		}


	}

	void GameStage4::CerateBreakEnemyPiece()//壊れる壁の先にあるかけら
	{
		Vec3 Pos[] = { Vec3(52.0f,0.3f,70.0f),Vec3(-10.0f,0.3f,10.0f),Vec3(52.0f,0.3f,-44.0f),Vec3(-43.0f,0.3f,-6.0f) };//BigPieceのPos一覧
		m_BigPieceLength = sizeof(Pos) / sizeof(Vec3);//BigPieceの合計の数
		for (int i = 0; i < m_BigPieceLength; i++)
		{		
			int randMesh = rand() % 3 + 1;//ランダムにどのどのメッシュになるかが決まる
			auto Piece = AddGameObject<BigPiece>(Pos[i], Vec3(0.0f, 0.0f, 0.0f), Vec3(3.5f, 3.5f, 3.5f),randMesh);//オブジェクトを生成する
			wstring Name = L"BigPiece";//オブジェクトの共通の名前を決める
			Name += to_wstring(i + 1);//オブジェクトの共通の名前にプラスして番号をふる　例：BigPiece1,BigPiece2
			SetSharedGameObject(Name, Piece);//生成したオブジェクトに名前を付ける
		}

	}


	void GameStage4::CreateMap()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/";
		vector<vector<int>> stageMap;

		ifstream ifs(levelPath += L"Level_4.csv");
		auto a = 0;
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
					AddGameObject<Wall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, 0, 0), Vec3(3.0, 10, 1.0));
					break;
				case 2:
					AddGameObject<Wall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, 0, 0), Vec3(1.0, 10, 3.0));
					break;
				case 3:
					AddGameObject<Wall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, XMConvertToRadians(45.0f), 0), Vec3(0.5, 10, 4.25));
					break;
				case 4:
					AddGameObject<Wall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, XMConvertToRadians(-45.0f), 0), Vec3(0.5, 10, 4.25));
					break;
				case 5:
					AddGameObject<BreakWall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, XMConvertToRadians(90.0f), 0), Vec3(1, 10, 3), 150.0f, SpriteLenght, SpriteStartPos);
					break;
				case 6:
					AddGameObject<BreakWall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, XMConvertToRadians(45.0f), 0), Vec3(0.5, 10, 4.25), 150.0f, SpriteLenght, SpriteStartPos);
					break;
				case 7:
					AddGameObject<BreakWall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, XMConvertToRadians(-45.0f), 0), Vec3(0.5, 10, 4.25), 150.0f, SpriteLenght, SpriteStartPos);
					break;
				case 8:
					AddGameObject<Block>(blockStartPos + pos, Vec3(0, 0, 0));
					break;
				case 9:
					AddGameObject<BlockSecond>(startPos + pos, Vec3(0, 0, 0), Vec3(23.0f, 10.0f, 18.0f));
					break;
				case 10:
					AddGameObject<Block3>(startPos + pos, Vec3(0, 0.0, 0), Vec3(23.0f, 10.0f, 18.0f));
					break;
				case 13:
					AddGameObject<Wall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, 0, 0), Vec3(140.0, 10, 1.0));
					break;
				case 14:
					AddGameObject<Wall>(startPos + pos + Vec3(0.0f, 1.5f, 0.0f), Vec3(0, 0, 0), Vec3(1.0, 10, 140.0));
					break;

				}

			}
		}
	}

	void GameStage4::CreateMiniMap()
	{
		float Lenght = 225.0f;//ミニマップの直径
		auto miniMap = AddGameObject<Sprite>(Lenght, Lenght, L"MiniMapStage4", Vec3(640.0f - (Lenght / 2.0f)-50.0f, 400.0f - (Lenght / 2.0f)-50.0f, 0.0f), 5);//ミニマップ生成
		SetSharedGameObject(L"MiniMap", miniMap);

		auto miniMapPlayer = AddGameObject<MiniMapPlayer>(Vec3(640.0f - (Lenght / 2.0f)-50.0f, 400.0f - (Lenght / 2.0f)-50.0f, 0.0f), 4.0f, 150.0f, Lenght);//ミニマップ上でPlayerの位置を表示
		SetSharedGameObject(L"MiniMapPlayer", miniMapPlayer);

		Vec3 StartPos = Vec3(640.0f - (Lenght / 2.0f) - 50.0f, 400.0f - (Lenght / 2.0f) - 50.0f, 0.0f);
		float Bairitu = Lenght / 150.0f;//現在のミニマップの倍率(どれくらい引き延ばしているかを表す)

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
	void GameStage4::BaseBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"ScaryBGM", XAUDIO2_LOOP_INFINITE, 0.3f);
	}
	void GameStage4::BossBGM() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"BossBGM", XAUDIO2_LOOP_INFINITE, 0.3f);
	}
	void GameStage4::OnDestroy() 
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameStage4::OnCreate() {
		try {	
			auto scene = App::GetApp()->GetScene<Scene>();
			scene->SetGameStage(4);
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
			AddGameObject<RandCreateManager>(L"kakeraMapDateLevels.csv", 150, 30);//ランダムにかけらが出るようになる
			CerateBreakEnemyPiece();
			//CreateRecoveryWall();//治す壁を生成 現在没データ化
			AddGameObject<Ground>();//地面を生成
			CreateMap();//マップを生成
			CreateMiniMap();//ミニマップ生成
			auto stageCollsionManager = AddGameObject<StageCollisionManager>();//コリジョンマネージャー追加
			SetSharedGameObject(L"StageCollisionManager", stageCollsionManager);

			auto joinManager = AddGameObject<JoinManager>(Vec3(0.0f, 0.5f, 0.0f), Vec3(0.0f, 0.5f, -13.0f));//ステージ開始時の演出


			//BGM
			BaseBGM();
			m_CareerFlag = 0;//初期化
		}
		catch (...) {
			throw;
		}
	}

	void GameStage4::OnUpdate()
	{
		//GetSharedGameObject<StageCollisionManager>(L"StageCollisionManager")->SetCollisionSwhich(false);//デバック用
		auto ptrPlayer = GetSharedGameObject<Player>(L"GamePlayer");
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
			//GetSharedGameObject<Radar>(L"Radar")->MyRemove();//レーダーを消去する

			AddGameObject<EscapeManager>(Vec3(0.0f, 3.0f, -16.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(-9.0f, 0.5f, -17.0f), Vec3(9.0f, 0.5f, -12.0f), Vec3(0.0f, 0.5f, -13.0f), Vec3(0.0f, 0.5f, 0.0f));
			AddGameObject<EscapeManager>(Vec3(0.0f, 3.0f, 18.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(-5.0f, 0.5f, 10.0f), Vec3(5.0f, 0.5f, 15.0f), Vec3(0.0f, 0.5f, 13.0f), Vec3(0.0f, 0.5f, 0.0f));

			m_CareerFlag = 4;
			GetSharedGameObject<StageManager>(L"StageManager")->SetCareerFlag(4);//進行度を更新

			OnDestroy();
			BaseBGM();

		}

	}

}

//end basecross
