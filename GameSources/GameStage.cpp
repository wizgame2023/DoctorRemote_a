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

	void GameStage::CreateBullet()
	{
		//弾生成　　引数は左から順番に初期位置→大きさ→スピード→角度（rad）→攻撃力 となっています
		auto Bulletptr = AddGameObject<Bullet>(Vec3(-1.0f, 0.5f, 0.0f), Vec3(0.3f, 0.3f, 0.3f), 1.0f, 0.0f, 1);
		Bulletptr->GetSpeed();
		//シェア配列にBulletを追加
		SetSharedGameObject(L"Bullet", Bulletptr);//これでAddしたゲームオブジェクトを取得できる
	}

	//Playerを追加する関数
	void GameStage::CreatePlayer()//改善すべき点
	{
		int randamPlayer = 0;
		randamPlayer = rand() % 3;
		shared_ptr<Player> ptrPlayer;
		randamPlayer = 0;
		//shared_ptr<GameObject> nanasiObject;
		//ランダムにPlayerの出現場所が決まる
		switch (randamPlayer)
		{
		case 0:		
			ptrPlayer = AddGameObject<Player>(Vec3(10.0f,0.5f,-40.0f),Vec3(0.0f,0.0f, 0.0f));
			break;
		case 1:
			ptrPlayer = AddGameObject<Player>(Vec3(-60.0f, 0.5f, 63.0f), Vec3(0.0f, 0.0f, 0.0f));
			break;
		case 2:
			ptrPlayer = AddGameObject<Player>(Vec3(60.0f, 0.5f, 10.0f), Vec3(0.0f, 0.0f, 0.0f));
			break;

		default:
			ptrPlayer = AddGameObject<Player>();
			break;
		}
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

	//敵の欠片を作成
	void GameStage::CreateEnemyPiece() {

		vector<vector<Vec3>> vec = {
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

	void GameStage::RandamPiecePosition(Vec3 originPosition)//引数を中心にランダムにかけらが置かれる
	{
		int randamCount = 0;
		randamCount = rand() % 9 + 1;
		randamCount = 5;

		Vec3 a = Vec3();
		Vec3 b = Vec3(0.5f, 0.5f, 0.5f);
		vector<Vec3> Trans;
		srand(time(0));//ランダムリセット

		for (int i = 0; i < randamCount; i++)
		{

			int x = rand() % 19 + 1;//ランダムに中心点からx座標がどれくらい離れているか決める

			srand(rand() * rand() % 7);

			int z = rand() % 19 + 1;//ランダムに中心点からy座標がどれくらい離れているか決める
			x - 10; z - 10;//これで離れている座標の差にマイナスを入れる

			Vec3 Pos = Vec3(originPosition.x + x, originPosition.y, originPosition.z + z);//これでランダムにピースを置くことができる
			Trans.push_back(Pos);

		}
		for (auto i : Trans)
		{
			AddGameObject<EnemyPiece>(i, a, b);
		}

	}

	void GameStage::CreateEnemyPiece2()
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

	void GameStage::CerateBreakEnemyPiece()//壊れる壁の先にあるかけら
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

	void GameStage::CreateRecoveryWall()
	{
		for (int count = 0; count < 11; count++)
		{
			switch (count)
			{
			case 1:
				AddGameObject<RecoveryWall>(Vec3(2.31f, 0.5f, -34.8f), Vec3(0.0f, 0.0f, XMConvertToRadians(0.0f)), Vec3(1.0f, 1.0f, 1.0f));
				break;
			case 2:
				AddGameObject<RecoveryWall>(Vec3(28.0f, 0.5f, 68.0f), Vec3(XMConvertToRadians(0.0f), 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
				break;
			case 3:
				AddGameObject<RecoveryWall>(Vec3(-3.0f, 0.5f, -72.0f), Vec3(0.0f, 0.0f, XMConvertToRadians(0.0f)), Vec3(1.0f, 1.0f, 1.0f));
				break;
			case 4:
				AddGameObject<RecoveryWall>(Vec3(-71.0f, 0.5f, -2.6f), Vec3(0.0f, 0.0f, XMConvertToRadians(0.0f)), Vec3(1.0f, 1.0f, 1.0f));
				break;
			case 5:
				AddGameObject<RecoveryWall>(Vec3(-68.0f, 0.5f, -2.4f), Vec3(0.0f, 0.0f, XMConvertToRadians(0.0f)), Vec3(1.0f, 1.0f, 1.0f));
				break;
			case 6:
				AddGameObject<RecoveryWall>(Vec3(8.77f, 0.5f, -72.7f), Vec3(0.0f, 0.0f, XMConvertToRadians(0.0f)), Vec3(1.0f, 1.0f, 1.0f));
				break;
			case 7:
				AddGameObject<RecoveryWall>(Vec3(3.0f, 0.5f, -66.0f), Vec3(0.0f, 0.0f, XMConvertToRadians(0.0f)), Vec3(1.0f, 1.0f, 1.0f));
				break;
			case 8:
				AddGameObject<RecoveryWall>(Vec3(-71.0f, 0.5f, 4.8f), Vec3(0.0f, 0.0f, XMConvertToRadians(0.0f)), Vec3(1.0f, 1.0f, 1.0f));
				break;
			case 9:
				AddGameObject<RecoveryWall>(Vec3(71.0f, 0.5f, 34.0f), Vec3(0.0f, 0.0f, XMConvertToRadians(0.0f)), Vec3(1.0f, 1.0f, 1.0f));
				break;
			case 10:
				AddGameObject<RecoveryWall>(Vec3(51.0f, 0.5f, 11.0f), Vec3(0.0f, 0.0f, XMConvertToRadians(0.0f)), Vec3(1.0f, 1.0f, 1.0f));
				break;
			}
		}
	}


	void GameStage::CreateBreakWall()
	{

		for (int count = 1; count < 20; count++)
		{
			switch (count)
			{
			case 1:
				AddGameObject<BreakWall>(Vec3(59.0f, 4.0f, -39.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 3.0f, 24.0f));
				break;
			case 2:
				AddGameObject<BreakWall>(Vec3(59.0f, 1.0f, -30.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 3.0f, 6.0f));
				break;
			case 3:
				AddGameObject<BreakWall>(Vec3(59.0f, 1.0f, -36.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 3.0f, 6.0f));
				break;
			case 4:
				AddGameObject<BreakWall>(Vec3(59.0f, 1.0f, -42.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 3.0f, 6.0f));
				break;
			case 5:
				AddGameObject<BreakWall>(Vec3(59.0f, 1.0f, -48.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 3.0f, 6.0f));
				break;
			case 6:
				AddGameObject<BreakWall>(Vec3(10.0f, 4.0f, 16.2f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 35.7f));
				break;
			case 7:
				AddGameObject<BreakWall>(Vec3(16.25f, 1.0f, 2.8f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 6.0f));
				break;
			case 8:
				AddGameObject<BreakWall>(Vec3(13.72f, 1.0f, 8.23f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 6.0f));
				break;
			case 9:
				AddGameObject<BreakWall>(Vec3(11.19f, 1.0f, 13.66f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 6.0f));
				break;
			case 10:
				AddGameObject<BreakWall>(Vec3(8.66f, 1.0f, 19.09f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 6.0f));
				break;
			case 11:
				AddGameObject<BreakWall>(Vec3(6.13f, 1.0f, 24.52f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 6.0f));
				break;
			case 12:
				AddGameObject<BreakWall>(Vec3(3.69f, 1.0f, 29.73f), Vec3(0.0f, XMConvertToRadians(-25.0f), 0.0f), Vec3(0.5f, 3.0f, 5.5f));
				break;
			case 13:
				AddGameObject<BreakWall>(Vec3(-31.3f, 4.0f, -38.0f), Vec3(0.0f, XMConvertToRadians(20.0f), 0.0f), Vec3(6.0f, 3.0f, 0.5f));
				break;
			case 14:
				AddGameObject<BreakWall>(Vec3(-31.3f, 1.0f, -38.0f), Vec3(0.0f, XMConvertToRadians(20.0f), 0.0f), Vec3(6.0f, 3.0f, 0.5f));
				break;
			case 15:
				AddGameObject<BreakWall>(Vec3(-11.61f, 4.0f, 50.0f), Vec3(0.0f, XMConvertToRadians(40.0f), 0.0f), Vec3(0.5f, 3.0f, 7.0f));
				break;
			case 16:
				AddGameObject<BreakWall>(Vec3(-11.61f, 1.0f, 50.0f), Vec3(0.0f, XMConvertToRadians(40.0f), 0.0f), Vec3(0.5f, 3.0f, 7.0f));
				break;

			}
		}
	}

	void GameStage::CreateBlockSecond()
	{
		for (int count = 0; count < 12; count++)
		{
			switch (count)
			{
			case 1:
				AddGameObject<BlockSecond>(Vec3(0.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(21.0f, 10.0f, 21.0f));
				break;
			case 2:
				AddGameObject<BlockSecond>(Vec3(57.8f, 2.5f, -55.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(12.0f, 10.0f, 12.0f));
				break;
			case 3:
				AddGameObject<BlockSecond>(Vec3(55.5f, 4.5f, -18.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
				break;
			case 4:
				AddGameObject<BlockSecond>(Vec3(15.0f, 4.5f, -60.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
				break;
			case 5:
				AddGameObject<BlockSecond>(Vec3(57.0f, 4.5f, 28.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(24.0f, 10.0f, 24.0f));
				break;
			case 6:
				AddGameObject<BlockSecond>(Vec3(27.0f, 4.5f, 45.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
				break;
			case 7:
				AddGameObject<BlockSecond>(Vec3(-17.0f, 4.5f, -60.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
				break;
			case 8:
				AddGameObject<BlockSecond>(Vec3(-42.0f, 4.5f, -35.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(15.6f, 10.0f, 15.6f));
				break;
			case 9:
				AddGameObject<BlockSecond>(Vec3(-56.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
				break;
			case 10:
				AddGameObject<BlockSecond>(Vec3(-20.0f, 4.5f, 40.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 20.0f));
				break;
			case 11:
				AddGameObject<BlockSecond>(Vec3(-50.5f, 4.5f, 45.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(17.0f, 10.0f, 17.0f));
				break;

			}
		}
	}


	void GameStage::CreateWall()
	{

		for (int count = 1; count < 24; count++)
		{
			switch (count)
			{
				//外壁1
			case 1:
				AddGameObject<Wall>(Vec3(75.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 150.0f));
				break;
			case 2:
				AddGameObject<Wall>(Vec3(-75.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 150.0f));
				break;
			case 3:
				AddGameObject<Wall>(Vec3(0.0f, 4.5f, 75.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(150.0f, 10.0f, 0.5f));
				break;
			case 4:
				AddGameObject<Wall>(Vec3(0.0f, 4.5f, -75.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(150.0f, 10.0f, 0.5f));
				break;
				//外壁2
			case 5:
				AddGameObject<Wall>(Vec3(70.0f, 4.5f, -70.0f), Vec3(0.0f, XMConvertToRadians(45.0f), 0.0f), Vec3(0.5f, 10.0f, 14.0f));
				break;
			case 6:
				AddGameObject<Wall>(Vec3(70.0f, 4.5f, 70.0f), Vec3(0.0f, XMConvertToRadians(-45.0f), 0.0f), Vec3(0.5f, 10.0f, 14.0f));
				break;
			case 7:
				AddGameObject<Wall>(Vec3(-70.0f, 4.5f, -70.0f), Vec3(0.0f, XMConvertToRadians(45.0f), 0.0f), Vec3(14.0f, 10.0f, 0.5f));
				break;
			case 8:
				AddGameObject<Wall>(Vec3(-70.0f, 4.5f, 70.0f), Vec3(0.0f, XMConvertToRadians(-45.0f), 0.0f), Vec3(14.0f, 10.0f, 0.5f));
				break;
				//内壁1
			case 9:
				AddGameObject<Wall>(Vec3(56.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(38.0f, 10.0f, 0.5f));
				break;
			case 10:
				AddGameObject<Wall>(Vec3(-70.25f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(9.5f, 10.0f, 0.5f));
				break;
			case 11:
				AddGameObject<Wall>(Vec3(0.0f, 4.5f, -63.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 24.0f));
				break;
			case 12:
				AddGameObject<Wall>(Vec3(0.0f, 4.5f, 56.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 38.0f));
				break;
				//内壁2
			case 13:
				AddGameObject<Wall>(Vec3(20.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(20.0f, 10.0f, 0.5f));
				break;
			case 14:
				AddGameObject<Wall>(Vec3(-22.0f, 4.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(24.0f, 10.0f, 0.5f));
				break;
			case 15:
				AddGameObject<Wall>(Vec3(0.0f, 4.5f, -27.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 36.0f));
				break;
			case 16:
				AddGameObject<Wall>(Vec3(0.0f, 4.5f, 20.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.5f, 10.0f, 20.0f));
				break;
				//内壁3
			case 17:
				AddGameObject<Wall>(Vec3(69.7f, 4.5f, -9.0f), Vec3(0.0f, XMConvertToRadians(-45.0f), 0.0f), Vec3(15.0f, 10.0f, 0.5f));
				break;
			case 18:
				AddGameObject<Wall>(Vec3(64.8f, 4.5f, -65.0f), Vec3(0.0f, XMConvertToRadians(-135.0f), 0.0f), Vec3(15.0f, 10.0f, 0.5f));
				break;
				//内壁4
			case 19:
				AddGameObject<Wall>(Vec3(31.0f, 4.5f, 4.3f), Vec3(0.0f, XMConvertToRadians(-145.0f), 0.0f), Vec3(15.0f, 10.0f, 0.5f));
				break;
			case 20:
				AddGameObject<Wall>(Vec3(35.15f, 4.5f, -5.25f), Vec3(0.0f, XMConvertToRadians(-135.0f), 0.0f), Vec3(15.0f, 10.0f, 0.5f));
				break;
				//内壁5
			case 21:
				AddGameObject<Wall>(Vec3(3.6f, 4.5f, -37.3f), Vec3(0.0f, XMConvertToRadians(-65.0f), 0.0f), Vec3(17.0f, 10.0f, 0.5f));
				break;
			case 22:
				AddGameObject<Wall>(Vec3(-6.36f, 4.5f, -47.48f), Vec3(0.0f, XMConvertToRadians(30.0f), 0.0f), Vec3(15.0f, 10.0f, 0.5f));
				break;
			}
		}
		for (int remCount = 23; remCount < 28; remCount++)
		{
			switch (remCount)
			{
				//内壁5
			case 23:
				AddGameObject<Wall>(Vec3(-9.65f, 4.5f, -38.6f), Vec3(0.0f, XMConvertToRadians(-60.0f), 0.0f), Vec3(12.0f, 10.0f, 0.5f));
				break;
				//内壁6
			case 24:
				AddGameObject<Wall>(Vec3(3.46f, 4.5f, 33.3f), Vec3(0.0f, XMConvertToRadians(-45.0f), 0.0f), Vec3(10.0f, 10.0f, 0.5f));
				break;
			case 25:
				AddGameObject<Wall>(Vec3(-2.78f, 4.5f, 40.0f), Vec3(0.0f, XMConvertToRadians(45.0f), 0.0f), Vec3(8.0f, 10.0f, 0.5f));
				break;
			case 26:
				AddGameObject<Wall>(Vec3(-5.5f, 4.5f, 35.7f), Vec3(0.0f, 0.0, 0.0f), Vec3(0.5f, 10.0f, 14.0f));
				break;
			case 27:
				AddGameObject<Wall>(Vec3(-4.9f, 4.5f, 58.0f), Vec3(0.0f, XMConvertToRadians(-50.0f), 0.0f), Vec3(14.0f, 10.0f, 0.5f));
				break;

			}
		}
	}

	void GameStage::CreateBlock()
	{
		for (int count = 0; count < 26; count++)
		{
			switch (count)
			{
				//エリア1
			case 1:
				AddGameObject<Block>(Vec3(45.0f, 0.75f, -61.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 2:
				AddGameObject<Block>(Vec3(68.0f, 0.75f, -43.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 3:
				AddGameObject<Block>(Vec3(29.0f, 0.75f, -44.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 4:
				AddGameObject<Block>(Vec3(27.0f, 0.75f, -17.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
				//エリア2
			case 5:
				AddGameObject<Block>(Vec3(45.0f, 0.75f, 10.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 6:
				AddGameObject<Block>(Vec3(30.0f, 0.75f, 23.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 7:
				AddGameObject<Block>(Vec3(50.0f, 0.75f, 50.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 8:
				AddGameObject<Block>(Vec3(20.0f, 0.75f, 15.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 9:
				AddGameObject<Block>(Vec3(10.0f, 0.75f, 60.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
				//エリア3
			case 10:
				AddGameObject<Block>(Vec3(-45.0f, 0.75f, -55.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 11:
				AddGameObject<Block>(Vec3(-45.0f, 0.75f, -50.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 12:
				AddGameObject<Block>(Vec3(-45.0f, 0.75f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 13:
				AddGameObject<Block>(Vec3(-40.0f, 0.75f, -55.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 14:
				AddGameObject<Block>(Vec3(-35.0f, 0.75f, -55.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 15:
				AddGameObject<Block>(Vec3(-33.5f, 0.75f, -50.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 16:
				AddGameObject<Block>(Vec3(-28.5f, 0.75f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 17:
				AddGameObject<Block>(Vec3(-26.0f, 0.75f, -40.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 18:
				AddGameObject<Block>(Vec3(-65.0f, 0.75f, -20.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 19:
				AddGameObject<Block>(Vec3(-45.0f, 0.75f, 0.5f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 20:
				AddGameObject<Block>(Vec3(-33.5f, 0.75f, -4.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 21:
				AddGameObject<Block>(Vec3(-15.0f, 0.75f, -15.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
				//エリア4
			case 22:
				AddGameObject<Block>(Vec3(-28.0f, 0.75f, 13.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 23:
				AddGameObject<Block>(Vec3(-8.0f, 0.75f, 35.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 24:
				AddGameObject<Block>(Vec3(-23.0f, 0.75f, 68.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			case 25:
				//AddGameObject<Block>(Vec3(-57.0f, 0.75f, 25.0f), Vec3(0.0f, 0.0f, 0.0f));
				break;
			}
		}
	}



	void GameStage::OnCreate() {
		try {
			//テクスチャ、モデルの設定データ
			//auto data = AddGameObject<Data>();

			AddGameObject<MyLight>();//光の表現をこれでやる
			AddGameObject<TimeManager>();//時間制限
			//ビューとライトの作成
			CreateViewLight();
			//Playerを追加
			CreatePlayer();
			//敵のかけらを表示
			CreateEnemyPiece();
			CreateEnemyPiece2();//ランダムにかけらが出るようになる
			CerateBreakEnemyPiece();
			CreateRecoveryWall();//治す壁を生成
			//AddGameObject<Ground>();//地面を表示
			//地面を生成
			AddGameObject<Ground>();
			CreateWall();//これでステージの壁を作る
			CreateBreakWall();//壊れる壁の作成
			CreateBlockSecond();
			//ゲージを追加
			auto garge = AddGameObject<PieceGarge2>();
			SetSharedGameObject(L"Garge", garge);
			auto PGarge = AddGameObject<PlayerGarge>();

			CreateBlock();//障害物を生成

			auto stageManager = AddGameObject<StageManager>();//ステージマネージャーを生成
			SetSharedGameObject(L"StageManager", stageManager);


		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate()
	{
		auto ptrPlayer = GetSharedGameObject<Player>(L"GamePlayer");
		if (ptrPlayer->GetRadarFlag() && m_PieceFlag==0)
		{
			//敵を生成
			CreateEnemy();
			//レーダーを生成
			CreateRadar();
			m_PieceFlag = 1;
		}

	}

}

//end basecross
