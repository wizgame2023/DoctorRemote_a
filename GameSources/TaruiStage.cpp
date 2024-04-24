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
	void TaruiGameStage::CreateViewLight() {
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

	void TaruiGameStage::CreateEnemy()
	{
		auto enemy = AddGameObject<Enemy>();
	}

	void TaruiGameStage::OnCreate() {
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

		}
		catch (...) {
			throw;
		}
	}

}
//end namespace basecross