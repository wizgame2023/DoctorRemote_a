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
			AddGameObject<EnemyPiece>(v[0], v[1], v[2]);
		}

	}
	void O_GameStage::CreateEffect()//エフェクト生成
	{
		auto EffectPtr = AddGameObject<Effect>(L"PlayerEffectGreen", 0.5f, 8, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.1f, 0.1f, 0.1f));
		SetSharedGameObject(L"Effect", EffectPtr);
		auto EffectPtr2 = AddGameObject<EffectBreakWall>(L"PlayerEffectRed", 1.0f, 20, Vec3(0.2f, 0.6f, 0.2f), Vec3(0.4f, 0.4f, 0.4f));//使わない
		SetSharedGameObject(L"RedEffect", EffectPtr2);
		auto EffectPtr3 = AddGameObject<EffectMove>(L"PlayerEffectWhite", 1.5f, 15, 1.0f, Vec3(0.0f, 1.3f, 0.0f), Vec3(0.4f, 0.4f, 0.4f));
		SetSharedGameObject(L"PlayerEffectWhite", EffectPtr3);
		auto EffectPtr4 = AddGameObject<EffectChase>(L"PlayerEffectRed", 1.0f, 15, 1.0f, Vec3(0.5f, 0.8f, 0.5f), Vec3(0.85f, 0.85f, 0.85f));
		SetSharedGameObject(L"EffectChase", EffectPtr4);
		EffectPtr4 = AddGameObject<EffectChase>(L"PlayerEffectGreen", 1.5f, 15, 1.0f, Vec3(0.0f, 0.5f, 0.0f), Vec3(0.8f, 0.8f, 0.8f));
		SetSharedGameObject(L"PlayerEffectRecovery", EffectPtr4);


	}

	void O_GameStage::CreateMap()
	{
		int count;
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
			float stageW= static_cast<float>(stageMap[0].size());
			float stageD= static_cast<float>(stageMap.size());

			for (int r = 0; r < stageMap.size(); r++)
			{
				for (int c = 0; c < stageMap[0].size(); c++)
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
	//void O_GameStage::CreateWall()
	//{	

	//	for (int count = 1; count < 24; count++)
	//	{
	//		switch (count)
	//		{
	//			//外壁1
	//		case 1:
	//			AddGameObject<Wall>(Vec3(75.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 150.0f));
	//			break;
	//		case 2:
	//			AddGameObject<Wall>(Vec3(-75.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 150.0f));
	//			break;
	//		case 3:
	//			AddGameObject<Wall>(Vec3(0.0f, 4.5f, 75.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(150.0f, 10.0f, 0.5f));
	//			break;
	//		case 4:
	//			AddGameObject<Wall>(Vec3(0.0f, 4.5f, -75.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(150.0f, 10.0f, 0.5f));
	//			break;
	//			//外壁2
	//		case 5:
	//			AddGameObject<Wall>(Vec3(70.0f, 4.5f, -70.0f), Vec3(0.0f, XMConvertToRadians(45.0f), 0.0f), Vec3(0.5f, 10.0f, 14.0f));
	//			break;
	//		case 6:
	//			AddGameObject<Wall>(Vec3(70.0f, 4.5f, 70.0f), Vec3(0.0f, XMConvertToRadians(-45.0f), 0.0f), Vec3(0.5f, 10.0f, 14.0f));
	//			break;
	//		case 7:
	//			AddGameObject<Wall>(Vec3(-70.0f, 4.5f, -70.0f), Vec3(0.0f, XMConvertToRadians(45.0f), 0.0f), Vec3(14.0f, 10.0f, 0.5f));
	//			break;
	//		case 8:
	//			AddGameObject<Wall>(Vec3(-70.0f, 4.5f, 70.0f), Vec3(0.0f, XMConvertToRadians(-45.0f), 0.0f), Vec3(14.0f, 10.0f, 0.5f));
	//			break;
	//			//内壁1
	//		case 9:
	//			AddGameObject<Wall>(Vec3(56.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(38.0f, 10.0f, 0.5f));
	//			break;
	//		case 10:
	//			AddGameObject<Wall>(Vec3(-70.25f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(9.5f, 10.0f, 0.5f));
	//			break;
	//		case 11:
	//			AddGameObject<Wall>(Vec3(0.0f, 4.5f, -63.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 24.0f));
	//			break;
	//		case 12:
	//			AddGameObject<Wall>(Vec3(0.0f, 4.5f, 56.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 38.0f));
	//			break;
	//			//内壁2
	//		case 13:
	//			AddGameObject<Wall>(Vec3(20.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 0.5f));
	//			break;
	//		case 14:
	//			AddGameObject<Wall>(Vec3(-22.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(24.0f, 10.0f, 0.5f));
	//			break;
	//		case 15:
	//			AddGameObject<Wall>(Vec3(0.0f, 4.5f, -27.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 36.0f));
	//			break;
	//		case 16:
	//			AddGameObject<Wall>(Vec3(0.0f, 4.5f, 20.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 20.0f));
	//			break;
	//			//内壁3
	//		case 17:
	//			AddGameObject<Wall>(Vec3(69.7f, 4.5f, -9.0f), Vec3(0.0f, XMConvertToRadians(-45.0f), 0.0f), Vec3(15.0f, 10.0f, 0.5f));
	//			break;
	//		case 18:
	//			AddGameObject<Wall>(Vec3(64.8f, 4.5f, -65.0f), Vec3(0.0f, XMConvertToRadians(-135.0f), 0.0f), Vec3(15.0f, 10.0f, 0.5f));
	//			break;
	//			//内壁4
	//		case 19:
	//			AddGameObject<Wall>(Vec3(31.0f, 4.5f, 4.3f), Vec3(0.0f, XMConvertToRadians(-145.0f), 0.0f), Vec3(15.0f, 10.0f, 0.5f));
	//			break;
	//		case 20:
	//			AddGameObject<Wall>(Vec3(35.15f, 4.5f, -5.25f), Vec3(0.0f, XMConvertToRadians(-135.0f), 0.0f), Vec3(15.0f, 10.0f, 0.5f));
	//			break;
	//			//内壁5
	//		case 21:
	//			AddGameObject<Wall>(Vec3(3.6f, 4.5f, -37.3f), Vec3(0.0f, XMConvertToRadians(-65.0f), 0.0f), Vec3(17.0f, 10.0f, 0.5f));
	//			break;
	//		case 22:
	//			AddGameObject<Wall>(Vec3(-6.36f, 4.5f, -47.48f), Vec3(0.0f, XMConvertToRadians(30.0f), 0.0f), Vec3(15.0f, 10.0f, 0.5f));
	//			break;
	//		}
	//	}
	//	for (int remCount = 23; remCount < 28; remCount++)
	//	{
	//		switch (remCount)
	//		{
	//			//内壁5
	//		case 23:
	//			AddGameObject<Wall>(Vec3(-9.65f, 4.5f, -38.6f), Vec3(0.0f, XMConvertToRadians(-60.0f), 0.0f), Vec3(12.0f, 10.0f, 0.5f));
	//			break;
	//			//内壁6
	//		case 24:
	//			AddGameObject<Wall>(Vec3(3.46f, 4.5f, 33.3f), Vec3(0.0f, XMConvertToRadians(-45.0f), 0.0f), Vec3(10.0f, 10.0f, 0.5f));
	//			break;
	//		case 25:
	//			AddGameObject<Wall>(Vec3(-2.78f, 4.5f, 40.0f), Vec3(0.0f, XMConvertToRadians(45.0f), 0.0f), Vec3(8.0f, 10.0f, 0.5f));
	//			break;
	//		case 26:
	//			AddGameObject<Wall>(Vec3(-5.5f, 4.5f, 35.7f), Vec3(0.0f, 0.0, 0.0f), Vec3(0.5f, 10.0f, 14.0f));
	//			break;
	//		case 27:
	//			AddGameObject<Wall>(Vec3(-4.9f, 4.5f, 58.0f), Vec3(0.0f, XMConvertToRadians(-50.0f), 0.0f), Vec3(14.0f, 10.0f, 0.5f));
	//			break;

	//		}
	//	}
	//}
	//void O_GameStage::CreateBreakWall()
	//{

	//	for (int count = 1; count < 20; count++)
	//	{
	//		switch (count)
	//		{
	//		case 1:
	//			AddGameObject<BreakWall>(Vec3(59.0f, 4.0f, -39.0f), Vec3(0.0f, 0.0f, 0.0f) , Vec3(0.5f, 3.0f, 24.0f));
	//			break;
	//		case 2:
	//			AddGameObject<BreakWall>(Vec3(59.0f, 1.0f, -30.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 3.0f, 6.0f));
	//			break;
	//		case 3:
	//			AddGameObject<BreakWall>(Vec3(59.0f, 1.0f, -36.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 3.0f, 6.0f));
	//			break;
	//		case 4:
	//			AddGameObject<BreakWall>(Vec3(59.0f, 1.0f, -42.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 3.0f, 6.0f));
	//			break;
	//		case 5:
	//			AddGameObject<BreakWall>(Vec3(59.0f, 1.0f, -48.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 3.0f, 6.0f));
	//			break;
	//		case 6:
	//			AddGameObject<BreakWall>(Vec3(10.0f, 4.0f, 16.2f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 35.7f));
	//			break;
	//		case 7:
	//			AddGameObject<BreakWall>(Vec3(16.25f, 1.0f, 2.8f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 6.0f));
	//			break;
	//		case 8:
	//			AddGameObject<BreakWall>(Vec3(13.72f, 1.0f, 8.23f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 6.0f));
	//			break;
	//		case 9:
	//			AddGameObject<BreakWall>(Vec3(11.19f, 1.0f,13.66f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 6.0f));
	//			break;
	//		case 10:
	//			AddGameObject<BreakWall>(Vec3(8.66f, 1.0f, 19.09f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 6.0f));
	//			break;
	//		case 11:
	//			AddGameObject<BreakWall>(Vec3(6.13f, 1.0f, 24.52f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 6.0f));
	//			break;
	//		case 12:
	//			AddGameObject<BreakWall>(Vec3(3.69f, 1.0f, 29.73f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 5.5f));
	//			break;
	//		case 13:
	//			AddGameObject<BreakWall>(Vec3(-31.3f, 4.0f, -38.0f), Vec3(0.0f, XMConvertToRadians(20.0f), 0.0f), Vec3(6.0f, 3.0f, 0.5f));
	//			break;
	//		case 14:
	//			AddGameObject<BreakWall>(Vec3(-31.3f, 1.0f, -38.0f), Vec3(0.0f, XMConvertToRadians(20.0f), 0.0f), Vec3(6.0f, 3.0f, 0.5f));
	//			break;
	//		case 15:
	//			AddGameObject<BreakWall>(Vec3(-11.61f, 4.0f, 50.0f), Vec3(0.0f, XMConvertToRadians(40.0f), 0.0f), Vec3(0.5f, 3.0f, 7.0f));
	//			break;
	//		case 16:
	//			AddGameObject<BreakWall>(Vec3(-11.61f, 1.0f, 50.0f), Vec3(0.0f, XMConvertToRadians(40.0f), 0.0f), Vec3(0.5f, 3.0f, 7.0f));
	//			break;

	//		}
	//	}
	//} 
	//void O_GameStage::CreateRecoveryWall()
	//{
	//	for (int count = 0;  count < 4;  count++)
	//	{
	//		switch (count)
	//		{
	//		case 1:
	//			AddGameObject<RecoveryWall>(Vec3(0.5f, 0.5f, -39.0f), Vec3(0.0f, 0.0f, XMConvertToRadians(90.0f)), Vec3(2.0f, 0.5f, 2.0f));
	//			break;
	//		case 2:
	//			AddGameObject<RecoveryWall>(Vec3(30.0f, 0.5f, 74.5f), Vec3(XMConvertToRadians(90.0f), 0.0f, 0.0f), Vec3(2.0f, 0.5f, 2.0f));
	//			break;
	//		case 3:
	//			AddGameObject<RecoveryWall>(Vec3(-7.0f, 0.5f, -60.0f), Vec3(0.0f, 0.0f, XMConvertToRadians(90.0f)), Vec3(2.0f, 0.5f, 2.0f));
	//			break;
	//		}
	//	}
	//}
	//void O_GameStage::CreateBlock()
	//{
	//	for (int count = 0; count < 26; count++)
	//	{
	//		switch (count)
	//		{
	//			//エリア1
	//		case 1:
	//			AddGameObject<Block>(Vec3(45.0f, 2.0f, -61.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 2:
	//			AddGameObject<Block>(Vec3(68.0f, 2.0f, -43.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 3:
	//			AddGameObject<Block>(Vec3(29.0f, 2.0f, -44.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 4:
	//			AddGameObject<Block>(Vec3(27.0f, 2.0f, -17.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//			//エリア2
	//		case 5:
	//			AddGameObject<Block>(Vec3(45.0f, 2.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 6:
	//			AddGameObject<Block>(Vec3(30.0f, 2.0f, 23.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 7:
	//			AddGameObject<Block>(Vec3(50.0f, 2.0f, 50.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 8:
	//			AddGameObject<Block>(Vec3(20.0f, 2.0f, 15.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 9:
	//			AddGameObject<Block>(Vec3(10.0f, 2.0f, 60.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//			//エリア3
	//		case 10:
	//			AddGameObject<Block>(Vec3(-45.0f, 2.0f, -55.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 11:
	//			AddGameObject<Block>(Vec3(-45.0f, 2.0f, -50.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 12:
	//			AddGameObject<Block>(Vec3(-45.0f, 2.0f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 13:
	//			AddGameObject<Block>(Vec3(-40.0f, 2.0f, -55.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 14:
	//			AddGameObject<Block>(Vec3(-35.0f, 2.0f, -55.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 15:
	//			AddGameObject<Block>(Vec3(-33.5f, 2.0f, -50.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 16:
	//			AddGameObject<Block>(Vec3(-28.5f, 2.0f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 17:
	//			AddGameObject<Block>(Vec3(-26.0f, 2.0f, -40.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 18:
	//			AddGameObject<Block>(Vec3(-65.0f, 2.0f, -20.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 19:
	//			AddGameObject<Block>(Vec3(-40.0f, 2.0f, 0.5f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 20:
	//			AddGameObject<Block>(Vec3(-33.5f, 2.0f, -4.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 21:
	//			AddGameObject<Block>(Vec3(-15.0f, 2.0f, -15.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//			//エリア4
	//		case 22:
	//			AddGameObject<Block>(Vec3(-28.0f, 2.0f, 13.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 23:
	//			AddGameObject<Block>(Vec3(-8.0f, 2.0f, 35.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 24:
	//			AddGameObject<Block>(Vec3(-23.0f, 2.5f, 68.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		case 25:
	//			AddGameObject<Block>(Vec3(-57.0f, 2.5f, 25.0f), Vec3(0.0f, 0.0f, 0.0f));
	//			break;
	//		}
	//	}
	//}
	//void O_GameStage::CreateBlockSecond()
	//{
	//	for (int count = 0; count < 12; count++)
	//	{
	//		switch (count)
	//		{
	//		case 1:
	//			AddGameObject<BlockSecond>(Vec3(0.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.5f, 10.0f, 20.5f));
	//			break;
	//		case 2:
	//			AddGameObject<BlockSecond>(Vec3(57.8f, 2.5f, -55.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(10.0f, 10.0f, 10.0f));
	//			break;
	//		case 3:
	//			AddGameObject<BlockSecond>(Vec3(55.5f, 4.5f, -18.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
	//			break;
	//		case 4:
	//			AddGameObject<BlockSecond>(Vec3(15.0f, 4.5f, -60.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
	//			break;
	//		case 5:
	//			AddGameObject<BlockSecond>(Vec3(57.0f, 4.5f, 28.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
	//			break;
	//		case 6:
	//			AddGameObject<BlockSecond>(Vec3(27.0f, 4.5f, 45.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
	//			break;
	//		case 7:
	//			AddGameObject<BlockSecond>(Vec3(-17.0f, 4.5f, -60.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
	//			break;
	//		case 8:
	//			AddGameObject<BlockSecond>(Vec3(-43.0f, 4.5f, -33.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
	//			break;
	//		case 9:
	//			AddGameObject<BlockSecond>(Vec3(-56.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
	//			break;
	//		case 10:
	//			AddGameObject<BlockSecond>(Vec3(-20.0f, 4.5f, 40.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
	//			break;
	//		case 11:
	//			AddGameObject<BlockSecond>(Vec3(-50.5f, 4.5f, 45.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
	//			break;

	//		}
	//	}
	//}

	void O_GameStage::OnCreate() {
		try {
			auto stageManager = AddGameObject<StageManager>();//ステージマネージャーを生成
			SetSharedGameObject(L"StageManager", stageManager);

			//auto data = AddGameObject<Data>();

			//ビューとライトの作成
			CreateViewLight();
			//弾を作成
			//CreateBullet();
			//Playerを追加
			CreatePlayer();
			//敵のかけらを表示
			//CreateEnemyPiece();
			CreateEnemy();
			//AddGameObject<Ground>();//地面を表示
			//レーダーを追加
			CreateRadar();
			//地面を生成
			AddGameObject<Ground>();
			//ゲージを追加
			auto garge = AddGameObject<PieceGarge>(GetSharedGameObject<Player>(L"GamePlayer"));
			SetSharedGameObject(L"Garge", garge);
			CreateMap();
			CreateEffect();
			//CreateWall();
			//CreateBreakWall();
			//CreateRecoveryWall();
			//CreateBlock();
			//CreateBlockSecond();
		}
		catch (...) {
			throw;
		}
	}
	void O_GameStage::OnUpdate()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"GamePlayer");
		auto PlayerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
		AABB CollisionActiveArea(PlayerPos + Vec3(-50.0f, -50.0f, -50.0f), PlayerPos + Vec3(50.0f, 50.0f, 50.0f));
		GetCollisionManager()->SetRootAABB(CollisionActiveArea);
	}

}
//end basecross

