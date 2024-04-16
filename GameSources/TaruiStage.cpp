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
	void T_GameStage::CreateViewLight() {
		// カメラの設定
		auto camera = ObjectFactory::Create<Camera>();
		camera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定
	}

	void T_GameStage::CreateEnemy()
	{
		auto enemy = AddGameObject<Enemy>();
	}

	void T_GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreateEnemy();


			// アプリケーションオブジェクトへの参照を取得しておく
			auto& app = App::GetApp();

			// 各種パスの設定
			auto path = app->GetDataDirWString(); // メディアパスを取得（..\media\）
			auto levelPath = path + L"Levels/"; // ステージマップが保存されているフォルダ


			// 地面
			AddGameObject<Ground>();

			const int MAP_ROWS = 10;
			const int MAP_COLS = 10;
			int stageMap[MAP_ROWS][MAP_COLS];

			// 外部ファイルからマップデータを読み込む
			ifstream ifs(levelPath + L"map001.csv");
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
					Vec3 startPos(-4.5f, 0.0f, +4.5f); // 基準となるオフセット座標
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
		catch (...) {
			throw;
		}
	}

}
//end namespace basecross