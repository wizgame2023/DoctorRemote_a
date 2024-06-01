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
	void GameStage::CreateViewLight() {


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

	void GameStage::CreateEffect()//エフェクト生成
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
	void GameStage::CreatePlayer()//改善すべき点
	{
		//Playerの出現場所を決める
		float deg = -180;
		float rad = XMConvertToRadians(deg);
		shared_ptr<Player> ptrPlayer= AddGameObject<Player>(Vec3(0.0f,0.5f,0.0f),Vec3(0.0f,rad,0.0f));
		SetSharedGameObject(L"GamePlayer", ptrPlayer);//ゲームオブジェクトを生成

	}
	//レーダーを追加する関数
	void GameStage::CreateRadar()
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
	void GameStage::CreateEnemy()
	{
		int randamEnemy = 0;
		randamEnemy = rand() % 4;
		shared_ptr<Enemy> ptrEnemy;
		switch (randamEnemy)
		{
		case 0:
			ptrEnemy = AddGameObject<Enemy>(Vec3(-40.0f, 0.5f, -9.0f), Vec3(-0.0f, 0.0f, 0.0f),Vec3(1.0f,1.0f,1.0f));
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

	//固定の敵の欠片を作成
	void GameStage::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = {
			{//8				
				Vec3(-6.25f,0.1f,24.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.25f,1.25f,1.25f)

			},
			{//9
				Vec3(-4.56f,0.1f,40.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.25f,1.25f,1.25f)

			},
			{//10
				Vec3(-7.25f,0.1f,-45.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.25f,1.25f,1.25f)

			},			
			{//11
				Vec3(27.7f,0.1f,-9.1f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.25f,1.25f,1.25f)
			},
			{//12
				Vec3(31.0f,0.1f,-6.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.25f,1.25f,1.25f)

			},
			{//13
				Vec3(39.0f,0.1f,6.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.25f,1.25f,1.25f)
			},
			{//14
				Vec3(29.0f,0.1f,15.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.25f,1.25f,1.25f)

			},
			{//15
				Vec3(13.0f,0.1f,44.0f),
				Vec3(0.0f,0.0f,0.0f),
				Vec3(1.25f,1.25f,1.25f)

			},
			//{//16
			//	Vec3(10.0f,1.0f,20.0f),
			//	Vec3(0.0f,0.0f,0.0f),
			//	Vec3(1.0f,1.0f,1.0f)

			//}

		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<EnemyPiece>(v[0], v[1], v[2]);
		}
	}

	void GameStage::RandamPiecePosition(Vec3 originPosition)//引数を中心にランダムにかけらが置かれる 消去予定
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

	void GameStage::CreateEnemyPiece2()//ランダムな場所にかけらを生成する
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

	void GameStage::CerateBreakEnemyPiece()//壊れる壁の先にあるかけら
	{
		//右上
		auto Piece1 = AddGameObject<BigPiece>(Vec3(51.0f, 0.2f, 70.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.5f, 1.5f, 1.5f));
		SetSharedGameObject(L"BigPiece1", Piece1);
		//左上
		auto Piece2 = AddGameObject<BigPiece>(Vec3(-10.0f, 0.2f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.5f, 1.5f, 1.5f));
		SetSharedGameObject(L"BigPiece2", Piece2);

		//右下
		auto Piece3 = AddGameObject<BigPiece>(Vec3(52.0f, 0.2f, -44.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.5f, 1.5f, 1.5f));
		SetSharedGameObject(L"BigPiece3", Piece3);

		//左下
		auto Piece4 = AddGameObject<BigPiece>(Vec3(-43.0f, 0.2f, -6.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(1.5f, 1.5f, 1.5f));
		SetSharedGameObject(L"BigPiece4", Piece4);

	}


	void GameStage::CreateMap()
	{
		auto path = App::GetApp()->GetDataDirWString();
		auto levelPath = path + L"Levels/";
		vector<vector<int>> stageMap;

		ifstream ifs(levelPath += L"Levels.csv");
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
					AddGameObject<BreakWall>(startPos + pos, Vec3(0, XMConvertToRadians(45.0f), 0), Vec3(0.5, 10, 4.25));
					break;
				case 7:
					AddGameObject<BreakWall>(startPos + pos, Vec3(0, XMConvertToRadians(-45.0f), 0), Vec3(0.5, 10, 4.25));
					break;
				case 8:
					AddGameObject<Block>(blockStartPos + pos, Vec3(0, 0, 0));
					break;
				case 9:
					AddGameObject<BlockSecond>(startPos + pos, Vec3(0, 0, 0), Vec3(23.0f, 10.0f, 18.0f));
					break;
				case 10:
					AddGameObject<BlockSecond>(startPos + pos, Vec3(0, 0, 0), Vec3(23.0f, 10.0f, 18.0f));
					break;

				}

			}
		}
	}

	void GameStage::CreateMiniMap()
	{
		float Lenght = 225.0f;//ミニマップの直径
		auto miniMap = AddGameObject<Sprite>(Lenght, Lenght, L"MiniMap", Vec3(640.0f - (Lenght / 2.0f)-50.0f, 400.0f - (Lenght / 2.0f)-50.0f, 0.0f), 5);//ミニマップ生成
		AddGameObject<MiniMapPlayer>(Vec3(640.0f - (Lenght / 2.0f)-50.0f, 400.0f - (Lenght / 2.0f)-50.0f, 0.0f), 3.0f, 150.0f, Lenght);//ミニマップ上でPlayerの位置を表示

		Vec3 StartPos = Vec3(640.0f - (Lenght / 2.0f) - 50.0f, 400.0f - (Lenght / 2.0f) - 50.0f, 0.0f);
		float Bairitu = Lenght / 150.0f;//現在のミニマップの倍率(どれくらい引き延ばしているかを表す)

		auto PiecePos = GetSharedGameObject<BigPiece>(L"BigPiece1")->GetComponent<Transform>()->GetPosition();	
		AddGameObject<Sprite>(3.0f, 3.0f, L"MiniMapBigPiece", Vec3(StartPos.x+(PiecePos.x * Bairitu), StartPos.y+(PiecePos.z * Bairitu), 0.0f), 6);//ミニマップ上でBigPieceの位置を表示

		PiecePos = GetSharedGameObject<BigPiece>(L"BigPiece2")->GetComponent<Transform>()->GetPosition();
		AddGameObject<Sprite>(3.0f, 3.0f, L"MiniMapBigPiece", Vec3(StartPos.x + (PiecePos.x * Bairitu), StartPos.y + (PiecePos.z * Bairitu), 0.0f), 6);//ミニマップ上でBigPieceの位置を表示

		PiecePos = GetSharedGameObject<BigPiece>(L"BigPiece3")->GetComponent<Transform>()->GetPosition();
		AddGameObject<Sprite>(3.0f, 3.0f, L"MiniMapBigPiece", Vec3(StartPos.x + (PiecePos.x * Bairitu), StartPos.y + (PiecePos.z * Bairitu), 0.0f), 6);//ミニマップ上でBigPieceの位置を表示

		PiecePos = GetSharedGameObject<BigPiece>(L"BigPiece4")->GetComponent<Transform>()->GetPosition();
		AddGameObject<Sprite>(3.0f, 3.0f, L"MiniMapBigPiece", Vec3(StartPos.x + (PiecePos.x * Bairitu), StartPos.y + (PiecePos.z * Bairitu), 0.0f), 6);//ミニマップ上でBigPieceの位置を表示

		

	}

	//BGMの再生
	void GameStage::PlayBGM()
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(L"ScaryBGM", XAUDIO2_LOOP_INFINITE, 0.5f);
	}
	void GameStage::OnDestroy() 
	{
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameStage::OnCreate() {
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
			//ゲージを追加
			auto garge = AddGameObject<PieceGarge2>();
			SetSharedGameObject(L"Garge", garge);
			auto PGarge = AddGameObject<PlayerGarge>();
			auto stageManager = AddGameObject<StageManager>();//ステージマネージャーを生成
			SetSharedGameObject(L"StageManager", stageManager);
			auto stageCollsionManager = AddGameObject<StageCollisionManager>();//コリジョンマネージャー追加
			SetSharedGameObject(L"StageCollisionManager", stageCollsionManager);

			auto joinManager = AddGameObject<JoinManager>(Vec3(0.0f, 0.5f, 0.0f), Vec3(0.0f, 0.5f, -10.8f));//ステージ開始時の演出


			//BGM
			PlayBGM();
			m_StageFlag = 0;//初期化
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"GamePlayer");
		//CollisionActive(true);
		if (ptrPlayer->GetRadarFlag() && m_StageFlag == 0)
		{
			//敵を生成
			CreateEnemy();
			//レーダーを生成
			CreateRadar();
			m_StageFlag = 1;

			OnDestroy();
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"BossBGM", XAUDIO2_LOOP_INFINITE, 0.5f);
			GetSharedGameObject<StageManager>(L"StageManager")->SetStageFlag(1);//進行度を進める

		}
		//デバック用
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPressedKeyTbl[VK_SPACE]) 
		{

		}
		if (m_StageFlag == 1)
		{
			m_StageFlag = GetSharedGameObject<StageManager>(L"StageManager")->GetStageFlag();//進行度を更新
		}
		if (m_StageFlag == 2)//敵を倒したとき
		{	
			//GetSharedGameObject<StageCollisionManager>(L"StageCollisionManager")->SetCollisionSwhich(false);//デバック用
			AddGameObject<EscapeManager>(Vec3(0.0f, 3.0f, -16.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(-9.0f, 0.5f, -17.0f), Vec3(9.0f, 0.5f, -12.0f), Vec3(0.0f, 0.5f, -13.0f), Vec3(0.0f, 0.5f, 0.0f));
			AddGameObject<EscapeManager>(Vec3(0.0f, 3.0f, 18.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(-5.0f, 0.5f, 10.0f), Vec3(5.0f, 0.5f, 15.0f), Vec3(0.0f, 0.5f, 10.0f), Vec3(0.0f, 0.5f, 0.0f));
			m_StageFlag = 3;

		}

	}

}

//end basecross
